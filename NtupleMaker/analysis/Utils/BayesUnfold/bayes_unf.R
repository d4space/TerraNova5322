#-------------------------------------------------------------------------
# Bayes unfolding: core functions
#
#    Bayes(prior, pec)
#    fast.unfold(prior, pce, eff, obs)
#    MC.unfold(prior, mc.smear,  obs, N=1000, ZERO_HANDLING=1,
#              HISTORY=FALSE, verbose=TRUE)
#    infer.pec(MC.gen, MC.obs)
#
# Before using this code you should be familiar with
#  NIM A362 (1995) 487
#
#                      G. D'Agostini, December 2005
#
# [The upgrate of the method is described in 
#   arXiv:1010.0632v1 (October 2010)]
#--------------------------------------------------------------------------


#--------------------------------------------------------------------------
# Bayes(priorf, pec) ------------------------------------------------------
#
# Bayes theorem
#  
#  IN: priorf: EITHER a vector of length nC containing priors
#                  OR a the name of a function returning such a vector
#      pec   : P(Ej|Ci), i.e. 'smearing matrix': array nE*nC
#
# OUT: pce   : inverse probabilities, i.e. P(Ci|Ej): array nC*nE 

Bayes <- function(priorf, pec) {
   if ( length(priorf) == 1 ) {
     prior <- priorf()  # priorf is a function that returns priors
   } else {
     prior <- priorf    # priorf is a vector of priors
   }
   pce <- matrix (rep(0, nE*nC), nC, nE)
   for (j in 1:nE) {
      pce[,j] <- pec[j,] * prior / sum(pec[j,] * prior)
   }
   return(pce)
}
#--------------------------------------------------------------------------


# fast.unfold(prior, pec, eff, obs) ---------------------------------------
#
# Assign evts to causes, only using 'expectations'
# (basically the old algorithm, without error evaluation)
#
#  IN: prior: vector of priors for causes, length nC
#      pec  : smearing matrix (size nC*nE)
#      obs  : vector of observations, length nE
#      eff  : vector of obervation efficiencies for each cause, length nC
#
# OUT: object containing unfolded number of events and posterior
#      $err     : TRUE/FALSE, depending if function reports errors
#      $err.msg : error message
#      $xm  : number of unfolded events per each cause, length nC
#      $post: posterior probabilities of causes, length nC

fast.unfold <- function(prior, pec, eff, obs) {
   unf <- NULL
   unf$err     <- FALSE
   unf$err.msg <- ""
   
   if ( length(prior) != nC ) {
     unf$err.msg <- " prior must be a vector of length nC"
   }
   if ( length(eff) != nC ) {
     unf$err.msg <- paste(unf$err.msg, "\n",
                          "eff must be a vector of length nC")
   }
   if ( length(obs) != nE ) {
     unf$err.msg <- paste(unf$err.msg, "\n",
                          "obs must be a vector of length nE")
   }   
   if (is.matrix(pec)) {
     if ( nrow(pec) != nE || ncol(pec) != nC) {
       unf$err.msg <- paste(unf$err.msg, "\n", 
                            sprintf("smearing matrix has bad dimensions: (%d,%d)",
                               nrow(pec), ncol(pec) ) )
       unf$err.msg <- paste(unf$err.msg, sprintf(" -> should be (%d,%d)",
                                                 nE, nC))
     } 
   } else {
     unf$err.msg <- paste(unf$err.msg, "\n",
                          sprintf("second argument (pec) should be a matrix"))
   }
   if(unf$err.msg != "") {
     unf$err <- TRUE
     unf$err.msg <- paste(unf$err.msg, "\n")
     return (unf)
   }
   pce <- Bayes(prior, pec)
   unf$xm <- ( pce %*% obs ) / eff
   unf$post <- unf$xm / sum(unf$xm)
   return (unf)
}
#-----------------------------------------------------------------------

# MC.unfold (prior, smear,  obs, N=1000, ZERO.HANDLING=1,   ------------
#            HISTORY=FALSE,  VERBOSE=TRUE)                  ------------
#
# Perform unfolding using MC integration over uncertain variables
#
#  IN: prior        : vector of priors (length nC)
#                     or function returning random realizations of such a vector 
#      smear        : can be either
#                         a) smearing matrix, array nE*nC, containing 'pec' needed
#                            by the function 'Bayes'. In this case the smearing
#                            matrix is considered 'exact' (it does not enter
#                            into the uncertainty)
#                     or
#                         b) Dirichlet's alphas got from MC simulation
#                               (see infer.pce)
#                     => Automatic detection: if all elements of smear are <= 1,
#                        then is interpreted as case a; otherwise as b.
#      obs          : vector of observations, length nE.
#      N            : number of drows for MC integration.
#      HISTORY      : all values of true numbers generated in the samplings
#                     are returned in the array x of output object 
#                     (usefull for detailed study of unfolded distribution,
#                      but watch memory usage!)
#      ZERO.HANDLING: how to handle observed zeros:
#                     0: bins with zero counts are not considered
#                     1: Gamma conjugate, with flat prior
#                     2: customized by the user, who has to provide
#                        the final(!) gamma parameters using the function my.gamma.par()
#                        [Note again: FINAL gamma parameters, and not initial ones:
#                          this allows the user whatever he/she might think reasonable!]
#
# OUT: object unf containing several infos:
#                     $err     : TRUE/FALSE, depending if function reports errors
#                     $err.msg : error message
#                     $xm: expected values of true number of events; length nC
#                     $xs: standard deviation of above; length nC
#                     $rho: correlation matrix; array nC*nC
#                     $x (only if HISTORY=TRUE): all MC values; array N*nC
#

MC.unfold <- function (prior, smear, obs, N=1000, ZERO.HANDLING=1,
                       HISTORY=FALSE, VERBOSE=TRUE) {
  
   # 1) inits ---------------------------------------------------------
   unf <- NULL
   unf$err     <- FALSE
   unf$err.msg <- ""

   # 1.1) check input parameters
   if ( length(prior) != nC ) {
     unf$err.msg <- " prior must be a vector of length nC"
   }
   if ( length(obs) != nE ) {
     unf$err.msg <- paste(unf$err.msg, "\n",
                          "obs must be a vector of length nE")
   }    
   if (is.matrix(smear)) {
     if ( any(smear > 1) ) {
       if ( nrow(smear) != (nE+1) || ncol(smear) != nC) {
         unf$err.msg <- paste(unf$err.msg, "\n", 
                              sprintf("matrix of alphas has bad dimensions: (%d,%d)",
                                      nrow(smear), ncol(smear) ) )
         unf$err.msg <- paste(unf$err.msg, sprintf(" -> should be (%d+1,%d)",
                                                   nE, nC))
       }
     } else {
       if ( nrow(smear) != nE || ncol(smear) != nC) {
         unf$err.msg <- paste(unf$err.msg, "\n", 
                              sprintf("smearing matrix has bad dimensions: (%d,%d)",
                                      nrow(smear), ncol(smear) ) )
         unf$err.msg <- paste(unf$err.msg, sprintf(" -> should be (%d+1,%d)",
                                                   nE, nC))
       }
     }
   } else {
     unf$err.msg <- paste(unf$err.msg, "\n",
                          sprintf("second argument (smear) should be a matrix"))
   }
   if (all(c(0,1,2) != ZERO.HANDLING)) {
     unf$err.msg <- paste(unf$err.msg, "\n",
                          sprintf("value of ZERO.HANDLING (%d) not alloewd",
                                  ZERO.HANDLING))
   }

   if(unf$err.msg != "") {
     unf$err <- TRUE
     unf$err.msg <- paste(unf$err.msg, "\n")
     return (unf)
   }
       
   # 1.2) setup variables

   if (HISTORY) unf$x <- NULL
   pec <-  matrix ( rep(0, nE*nC), c(nE, nC) )   # empty matrix
   eff <- rep (0, nC)                            # empty vector
   # 'x' stands for nr of events attributed to each cause
   sx   <- rep(0, nC)                            # sums of x for each cause
   sxij <- matrix ( rep(0, nC*nC), c(nC, nC) )   # sums of products
   if ( any(smear > 1) ) {
     # smear contains Dirichlet's parameters: pec and eff will be sampled
     if(VERBOSE) cat( sprintf("\nP(E_j|C_i) will be sampled using Dirichlet\n"))
   } else {
     # smear contains transition probabilities: pec and eff are 'exact'
     if(VERBOSE) print ( "fixed P(E_j|C_i) used" )

     for (i in 1:nC) {
       pec[,i] <- smear[,i]
       eff[i] <- sum( pec[,i] )
     }
   }
   
   # set gamma parameters
   if (ZERO.HANDLING < 2) {
     gamma.c.in  <- rep(1, nE)       # default is c=1
     gamma.r.in  <- rep(0, nE)       #            r=0
     gamma.c.fin <- gamma.c.in + obs # c is updated by observed events
     gamma.r.fin <- gamma.r.in + 1   # r is updated by 1
   } else if (ZERO.HANDLING == 2) {
     gamma.par <- my.gamma.par(obs)
     gamma.c.fin <- gamma.par$c
     gamma.r.fin <- gamma.par$r
   }
   
   if (VERBOSE) {
     cat(sprintf("\n Start sampling (%d trials) - please wait \n",
                            as.integer(N)))
     n10 <- as.integer(N/10)  # one tenth of N, used for printouts
     perc <- 0
   }

   # 2) sampling loop ---------------------------------------
   for (n in 1:N) { 
     if ( VERBOSE && ( (n %% n10) == 0 ) ) {
       perc <- perc + 10
       cat(sprintf("%.0f%%  ", perc) ) # prints percentage sampled, every 10%
     }
     # 2.1) choose smearing matrix according to MC transition matrix
     if ( any(smear > 1) ) {
       # smear contains Dirichlet's parameters: extract pec and calculate eff
       for (i in 1:nC) {
         rdir <- rdirichl(1, smear[,i])
         if ( is.null(rdir) || any(is.nan(rdir))) {
           cat(sprintf("\n *** BAD INPUT in rdirichl -> Check code\n"))
           return()
         }
         pec[,i] <- rdir[1:nE]
         eff[i] <- 1 - rdir[nE+1]
       }
     } # else, pec[,] and eff[] have been initialazed above

     # 2.2) get P(Ci|Ej) using Bayes theorem
     pce <- Bayes(prior, pec)

     
     # 2.3) assign events to causes using multinomial
     evc <- rep(0, nC)
     for (j in 1:nE) {
       if ( (ZERO.HANDLING == 0) && (obs[j] == 0) ) {
         evcj = rep(0, nC)
       } else {         
         lambda <- rgamma(1, gamma.c.fin[j], gamma.r.fin[j])
         n.mult <- round(lambda)       # round the value to clostest integer>0 ...
         if (n.mult < 1) n.mult <- 1   # ... to use it in multinomial;
         # scale factor to take into account Poisson fluctuation on obs[j]
         scale <- lambda / n.mult
         evcj = as.vector( rmultinom(1, n.mult, pce[,j]) ) * scale
       }
       evc <- evc + evcj
     }

     # 2.4) take into account for efficiency
     evc <- evc/eff

     # 2.5) store values for summaries and, if requested, for full history of sampling
     sx    <- sx + evc
     sxij <- sxij + evc %*% t(evc)
     if (HISTORY) {               
       unf$x <- c(unf$x, evc)
     }
   } # end of sampling loop
   
   if (VERBOSE) cat ( sprintf("   Sampling done!\n\n") )
   # 3) quantities to be returned
   unf$xm   <- sx/N                            # averages
   unf$post <-  unf$xm / sum(unf$xm)           # estimeted posterior (from averages)
   covx     <- sxij/N  - unf$xm %*% t(unf$xm)  # covariances
   unf$xs   <- sqrt( diag(covx) )              # standard deviations
   unf$rho  <- covx / ( unf$xs %*% t(unf$xs) ) # correlation coefficients
   if (HISTORY) {
      dim(unf$x) <- c(nC, N)
      unf$x <- t(unf$x)                        # all sampled values
   }
   return(unf)
}


# infer.pec(MC.gen, MC.obs, ZERO.HANDLING=0) --------------------------------------
#
# get smearing probabilities from MC
#
#  IN: MC.gen        : nr of MC events generated for each cause; length nC
#      MC.obs        : array of observed events for each cause; array nE*nC
#      ZERO.HANDLING : how to handle zero counts in MC.obs: it might be
#                      0: initial alphas to zero 
#                         ( -> zero count taken as zero transition probability )
#                      1: all initial Dirichlet alphas=1
#                     -1: all initial  Dirichlet alphas=1/nE
#                      2: customized by the user, who has to provide a matrix
#                         of final(!) alphas using the function my.alphas()
#                         [Note again: FINAL alphas, and not initial ones: this
#                          allows the user whatever he/she might think reasonable,
#                          including to smooth MC.obs]
#
# OUT: object containing:
#        $err     : TRUE/FALSE, depending if function reports errors
#        $err.msg : error message
#        $alpha: Dirichlet's parameters, array (nE+1)*nC
#                [note: Dirichlet distribution is the priors conjugate
#                of the multinomial distribution; the dimension of the array is
#                (nE+1)*nC, and not nE*nC, because also the 'inefficience bin'
#                has to be taken into account].
#        $E.pec, S.pec: expected values and standard deviation of the
#                transition probabilities (i.e. smearing matrix)
#                described by the Dirichlet distribution: array (nE+1)*nC
#        $pec: expected smearing matrix only from causes to _observed_ events;
#                array nE*nC
#        $eff: expected values of efficiencies for each cause; length nC


infer.pec <- function (MC.gen, MC.obs, ZERO.HANDLING=0) {

   dirchl <- NULL
   dirchl$err     <- FALSE
   dirchl$err.msg <- ""
   
   # check input parameters
   if ( length(MC.gen) != nC ) {
     dirchl$err.msg <- " first argument (MC.gen) must be a vector of length nC"
   }
   if (is.matrix(MC.obs)) {
     if ( nrow(MC.obs) != nE || ncol(MC.obs) != nC) {
       dirchl$err.msg <- paste(dirchl$err.msg, "\n", 
                            sprintf("MC.obs has bad dimensions: (%d,%d)",
                                     nrow(MC.obs), ncol(MC.obs) ) )
       dirchl$err.msg <- paste(dirchl$err.msg, sprintf(" -> should be (%d,%d)",
                                                  nE, nC))
     }
   } else {
     dirchl$err.msg <- paste(dirchl$err.msg, "\n",
                          sprintf("second argument (MC.obs) should be a matrix"))
   }
   if (all(c(0,1,-1,2) != ZERO.HANDLING)) {
     dirchl$err.msg <- paste(dirchl$err.msg, "\n",
                          sprintf("value of ZERO.HANDLING (%d) not alloewd",
                                  ZERO.HANDLING))
   }

   if(dirchl$err.msg != "") {
     dirchl$err <- TRUE
     dirchl$err.msg <- paste(dirchl$err.msg, "\n")
     return (dirchl)
   } 
   
   pec <-  matrix (rep(0, nE*nC), nE, nC)         # Empty P(Ej|Ci)
   E.pec <- matrix (rep(0, (nE+1)*nC), nE+1, nC)  # Sets empty matrices for expected values
   S.pec <- matrix (rep(0, (nE+1)*nC), nE+1, nC)  # ... and sigmas
   eff <- rep(0, nC)                              # Empty efficiency vector

   if ( abs(ZERO.HANDLING) < 2 ) {
     # set initial values of alpha's, unless ZERO.HANDLING) == 2
     if ( ZERO.HANDLING == 0 ||  ZERO.HANDLING == 1) {
       # Note the dimensions (nE+1)*nC) of the following matrices, to take
       # into account also for the 'inefficiency bin' ('trash bin' in the paper)
       alpha.in <- ZERO.HANDLING
     } else if ( ZERO.HANDLING == -1) {
       alpha.in <- 1/nE
     }
     alpha   <- matrix (rep(alpha.in, (nE+1)*nC), nE+1, nC)
     # update initial alpha's with observed numbers
     for (i in 1:nC) { 
       alpha[,i] <-  alpha[,i] + c( MC.obs[,i], MC.gen[i]-sum(MC.obs[,i]) )
     }
   } else if (ZERO.HANDLING == 2) {
     # customized alphas provided by user function
     alpha <- my.alphas(MC.gen, MC.obs)
   }
   
   # calculate exptected values, etc
   for (i in 1:nC) {
     sa <- sum(alpha[,i])
     E.pec[,i] <- alpha[,i]/sa
     S.pec[,i] <- sqrt( alpha[,i]*(sa-alpha[,i])/(sa^2*(sa+1)) )
     pec[,i] <- E.pec[1:nE, i]                       # best estimate of P(Ej|Ci)
     eff[i]  <- 1 - E.pec[nE+1, i]                   # best estimate of efficiency
   }
   dirchl$alpha <- alpha
   dirchl$E.pec <- E.pec
   dirchl$S.pec <- S.pec
   dirchl$pec   <- pec
   dirchl$eff   <- eff

   return(dirchl)
}
#--------------------------------------------------------------------------
