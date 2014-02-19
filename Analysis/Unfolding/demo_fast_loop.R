#--------------------------------------------------------------------------
#  Script to unfold a distribution using iterations + smearing
#
#  - during the iteration 'fast.unfold()' is used (only expectations)
#    in order to save time
#  - it loops over the several true distributions and
#    smearing matreces of the toy models
#
#  To run this script in a R console:
#
#     > source("demo_fast_loop.R")
#
#--------------------------------------------------------------------------

#----- small function to wait an Enter between loops ------------------
give.enter <- function() {
  cat (" >> press Enter to go on\n")
  scan()
  cat("\n")
}
#----------------------------------------------------------------------

# load the code
source("../Utils/unf2_R/simula.R")
source("../Utils/unf2_R/bayes_unf.R")
source("../Utils/unf2_R/bayes_extra.R")


# choose output graphics device. It can be 'eps', 'png' or '' 
plot.out <- 'eps'
plot.out <- 'png'
plot.out <- ''     # default shows plots on the screen


for (sm in 1:2) {    # loop over smearing matrices
  for (df in 0:6) {  # loop over true functions
    # main parameters to play with in this demo:
    n.mc         <- 10000                        # nr of MC events to infer smearing matrix
    n.data       <- 10000                        # nr of generated 'data' events
    n.unf.drows  <- 1000                         # nr of extractions in the MC unfolding 
    smearing     <- sm                           # kind of smearing (1 or 2)
    data.func    <- df                           # kind of true distribution to generate
                                                 # in simulated data in toy model
                                                 # valid values: 0, 1, ...,6
    n.iter       <- 20                           # number of iterations
    smooth.order <- 2                            # order of polinomial smoothing


    # MC events
    mc.func   <- 0                            # true distribution to be used in MC
                                              # O = flat; other options: 1, 2, .., 6
    mc.before  <- extract(n.mc, mc.func)      # extract true distribution
    mc.matr  <- apply.smearing(mc.before, smearing, MC=TRUE)  # smearing

    # Analyse MC events to infer smearing matrix
    mc.smear <- infer.pec(mc.before, mc.matr, ZERO.HANDLING = 2)
    #mc.smear <- infer.pec(mc.before, mc.matr)

    #------------ some printouts ---------------------------------
    cat ( sprintf("\n1) MC evaluation of smearing -----------------------------------\n") )
    cat ( sprintf("   Generated \n") )
    print(mc.before)
    cat ( sprintf("   Reconstructed in the various bins\n" ) )
    print(mc.matr)
    cat ( sprintf("   smearing matrix (expected values; last row is the inefficiency)\n" ) )
    print(mc.smear$E.pec)
    #--------------------------------------------------------------

    # Simulated experiment
    gen <-  extract(n.data, data.func)     # obviously, this makes no sense in real life
    obs <- apply.smearing( gen, smearing)  # <== THIS is WHAT THE EXPERIMENT GIVES

    #------------ some printouts ---------------------------------
    cat ( sprintf("\n2) Simulated data --------------------------------------------- \n" ))
    cat( sprintf( "   Generated:\n" ) )
    print(gen)
    cat ( sprintf("\n\n   Observed:\n" ) )
    print(obs)
    #--------------------------------------------------------------


    # Unfolding ##########################################################################
    cat ( sprintf("\n\n3) Unfolding ------------------------------------------------\n" ) )

    prior0 <-  rep(1/nC, nC) # uniform prior   (Note: nC and nE are defined in simula.R)
    prior <- prior0
    intermediate <- NULL
    for (iter in 1:n.iter) {
      cat ( sprintf("\n\n  Iterative unfolding. Iteration %d of %d:\n", iter, n.iter) )
      if (iter < n.iter) {
        unfolded <- fast.unfold (prior, mc.smear$pec, mc.smear$eff, obs)
        intermediate <- c(intermediate, unfolded$xm)
        prior <- as.vector ( prob.smooth (unfolded$post, ORDER=smooth.order) )
      } else {
        unfolded <- MC.unfold (prior, mc.smear$alpha, obs, N=1000)
      }
      #print (prior)
    }

    #---------- print some results and compare with true distribution -------------
    cat ( sprintf("\n\n   Observed:\n" ) )
    print(obs)
    result <- data.frame( generated=gen, estimated=unfolded$xm , sigma=unfolded$xs )
    print.data.frame(result)
    #------------------------------------------------------------------------------

    # A simple plot to summarize --------------------------------------------------
    
    if(plot.out == 'eps') {
      filename <-  sprintf("demo3_last_loop_sm%d_df%d.eps",sm, df)
      postscript(file=filename,horizontal=FALSE,height=6,onefile=FALSE)
    } else if (plot.out == 'png') {
      filename <-  sprintf("demo3_last_loop_sm%d_df%d.png",sm, df)
      png(file=filename, bg="white", width=1024, height=768)
    }
    x <- 1:nC
    y <- 1:nE
    max.c <- max(obs,gen,unfolded$xm)*1.05
    plot(y, obs, ylim=c(0,max.c), type='l', col='red', lwd=2, xlab="", ylab="")
    lines(x, gen, lwd=2)
    dim(intermediate) <- c(nC, length(intermediate)/nC)
    intermediate = t(intermediate)
    if (n.iter > 1) {
      lines(x,intermediate[1,] , col='cyan' )
    }
    if (n.iter > 2) {
      for (i in 2:nrow(intermediate)) {
        lines(x,intermediate[i,], col='yellow', lty='dashed')
      }
    }
    lines(x, unfolded$xm, col='blue', lwd=2 )         # final
    for (i in 1:nC) {                                   
      segments(x[i],unfolded$xm[i]+unfolded$xs[i],     # error bars
               x[i], unfolded$xm[i]-unfolded$xs[i], col='blue', lwd=2)
    }
    legend("topright", c("generated","observed","unf. step 1","intermed.", "unf. final"),
           lty=1, col=c("black","red","cyan","yellow","blue"))

    
    if ( plot.out != '' ) dev.off()

    #-------- endo of loop --- wait 'Enter' 
    cat ( sprintf("\n\n This has been a run with smearing %d and data.func %d \n",
                  sm, df) )
    if ( plot.out == '' ) {
      cat ( sprintf(" Inspect the output, give a look to the plot, then ... \n"))
      give.enter()
    }
  }
} # end loops
