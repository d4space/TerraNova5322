#----------------------------------------------------------------
# Bayes unfolding: extra functions
#
#   rdirichl(n, alphas)
#   my.alphas(MC.gen, MC.obs)
#   find.holes(v)
#   reg.alphas(v, ind, g, alpha,.init)
#   my.gamma.par(obs)
#   myfit(x,y, ORDER=1)
#   prob.smooth(evts, ORDER=2)
#   rprior()
#
#  G. D'Agostini, December 2005
#----------------------------------------------------------------

# rdirichl (n, alphas) -------------------------------------------------------
# returns n vectors of Dirichlet random numbers
# This function is an updated 'rdirichlet' of package MCMCpack
# that allows null values of alphas
#
#  IN: n      : numbers of vectors to be generated
#      alphas : vector of Dirichlet parameters
#
# OUT: matrix with n rows and l columns, where l=length(alpha)
# 
rdirichl <- function (n, alphas){
   l <- length(alphas)
   rg <- rgamma(l * n, alphas)
   rg[is.nan(rg)] <- 0
   x <- matrix(rg, ncol = l, byrow = TRUE)
   sm <- x %*% rep(1, l)
   return (x /as.vector(sm))
}
#--------------------------------------------------------------------------

# my.alphas (MC.gen, MC.obs) -----------------------------------------------
# returns customized Dirichlet alpha's
my.alphas <- function(MC.gen, MC.obs) {
  g.reg <- exp(-1)
  # initialize to zero
  alphas <- matrix (rep(0, (nE+1)*nC), nE+1, nC)
  for (i in 1:nC) {
    # set in alpha vector nr of counts
    a.i <- c(MC.obs[,i],  MC.gen[i] - sum(MC.obs[,i]) )
    # if nr counts > 0 add alpha_in=1/(nE+1)
    a.i[a.i > 0] <-  a.i[a.i > 0] + 1/(nE+1)
    # find regions with no counts in the acceptance region
    ind <- find.holes( a.i[1:nE] )
    # regularize all bins, but trash one
    a.i <- c(reg.alphas( a.i[1:nE], ind, g.reg, 1/(nE+1)), a.i[length(a.i)])
    alphas[,i] <- a.i
  }
  return(alphas)
}

# find.holes(v) ------------------------------------------------------------
# to  finds consecutive null elements of a vector v
find.holes <- function(v) {
  ind <- numeric()
  hit <- FALSE
  i1 <- i2 <- 0
  l <- length(v)
  for (i in 1:l) {
    if ( (v[i] || i == l) && i1 ) {
      i2 <- i - 1 + (i == l && !v[i])
      ind[length(ind)+1] <- i1
      ind[length(ind)+1] <- i2
      i1 <- i2 <- 0
    } else if (!v[i] && !i1) {
      i1 <- i
      if (i == l) {
        i2 <- i
        ind[length(ind)+1] <- i1
        ind[length(ind)+1] <- i2
      }
    }
  }
  dim (ind) <- c(2, length(ind)/2)
  return (t(ind))
}
#--------------------------------------------------------------------------

# reg.alphas(v, ind, g, alpha.init) ---------------------------------------
# regularize Dirichlet posterior alphas in effects-bins
# with no MC entries from a given cause
reg.alphas <- function(v, ind, g, alpha.init) {
   l <- nrow(ind)
   m <- length(v)
   if (l == 0) return (v)
   
   r <- rep(0, m)   # regularized bins
   for (i in 1:l) {
     i1 <- ind[i,1]
     i2 <- ind[i,2]
     if (i2 != m) {
       for (j in i2:i1) {
         v[j] <- v[j] + g^(i2-j) * alpha.init
         r[j] = TRUE
       }
     }
     if (i1 != 1) {
       for (j in i1:i2) {
         v[j] <- v[j] + g^(j-i1) * alpha.init
         r[j] = TRUE
       }
     }
   }
   # rescale regularized bins
   sum.alpha.reg <- ( length(v[r==TRUE])/(nE+1) ) /  sum(v[r==TRUE])
   for (j in 1:m) {
     if ( r[j]==TRUE ) {
       v[j] <-  v[j] * sum.alpha.reg
     }
   }
   return(v)
}
#-----------------------------------------------------------------------

# my.gamma.par (obs) ------------------------------------------------------
# returns customized gamma parameters
my.gamma.par <- function(obs) {
  gamma.par <- NULL
  gamma.c.in  <- rep(1, nE)       # default is c=1
  gamma.r.in  <- rep(0, nE)       #            r=0
  c.max <- 1                                # we want mode at zero
  r.min <- c.max/min(10,min(obs[obs>0])+1)  # expected value of all empty bins should 
                                            # not be too high 
  # c_j sum up to 1 for bins with having 0 events
  gamma.c.in[obs==0] <- c.max/length(obs[obs==0]) # share c.max among bins with zeros
  # r_j set all at the same value
  gamma.r.in[obs==0] <- r.min
  gamma.par$c <- gamma.c.in + obs # c is updated by observed events
  gamma.par$r <- gamma.r.in + 1   # r is updated by 1
  return(gamma.par)
}
#--------------------------------------------------------------------------


# myfit(x,y, ORDER=1) -------------------------------------------
#
# simple least square polynomial fit
#
#  IN: x    : vector of the abscisses
#      y    : vector of ordinates
#      ORDER: order of polynomial (ORDER=1 for a straigth line, etc.)
#
# OUT: vector of length ORDER+1 of coefficients, in increasing order of powers of x

myfit <- function (x,y, ORDER=1) {
  # build 'design' matrix
  X <- matrix(rep(1,length(x)), length(x), 1)  # first column filled with 1 
  for (i in 1:ORDER) X <- cbind(X, x^i)        # all other columns, with powers of x
  # get parameters
  par <- as.vector( chol2inv( chol( crossprod(X) ) ) %*% t(X)  %*% y )
  return (par)
}

# prob.smooth(evts, ORDER=2) ---------------------------------------
#
# simple polynomial smoothing
#
# NOTE: it assumes that the cause-bins are equidistant in some variable ('x').
#       Be carefull before apply it to your problem! (And also think to
#       the proper smoothing matching your physics case!)
#
#  IN: prior: prior to be smoothed before passing it to the Bayes formula
#      ORDER: oder of polynomial (not too high...)
#             If ORDER <0, then the smoothing is done in the log of the prior
#             (it might be also usefull to avoid negative smoothed values)
#
# OUT: vector of smoothed priors probabilities

prob.smooth <- function (prior, ORDER=2) {
   log.smooth <- FALSE
   if (ORDER < 0) {
     log.smooth <- TRUE
     ORDER <- -ORDER
     prior <- log(prior)
   }
   x <-  seq( 1:length(prior) )           # just equidistant bins
   fit.par <- myfit(x, prior, ORDER)
   xp <- rbind(1, x)                      # at least linear
   if (ORDER > 1) {
     for (i in 2:ORDER) {
       xp <- rbind(xp, x^i)
     }
   }
   # values of polynom in the points x
   # (to be interpreted as the center of each bin)
   smoothed <- as.vector(fit.par %*% xp)
   if (log.smooth) smoothed <- exp(smoothed)

   if (any(smoothed <= 0) ) {
     cat ( sprintf("\n *** negative smoothed value!! Change smoothing function!!!\n"))
     cat ( sprintf("\n *** For the moment fixed taking averages of neighbours ..."))
     cat ( sprintf("GOOD LUCK!\n"))
     for (i in 1:nC) {
       if (smoothed[i] <= 0) {
       vneg <- smoothed[i]
         if ((i > 1) && (i < nC)) {
           smoothed[i] <- (smoothed[i-1]+smoothed[i+1])/4   # half the average
         } else if (i == 1) {
           smoothed[i] <- smoothed[i+1]/2
         } else {
           smoothed[i] <- smoothed[i-1]/2
         }
       cat ( sprintf("\n *** value %f in bin %d changed to %f\n",
                     vneg, i, smoothed[i]) )
       }
     }
     return ( smoothed/sum(smoothed) )  # try to fix it...
   } else {
     return ( smoothed/sum(smoothed) )
   }
}
#--------------------------------------------------------------------------


# rprior() ---------------------------------------------------------------
#
# random priors: _to_be_provided_by_the_user_ AND to be used CUM GRANO SALIS!
#
# OUT : a vector of length nC whose elements sum to 1
rprior <- function() {
  return ( rep(1/nC, nC) )   # the default just gives a flat prior
}
#--------------------------------------------------------------------------

