# dimensionality
nC <- 12
nE <- 12

n.iter       <- 5                           # number of iterations
#n.iter       <- 20                           # number of iterations
smooth.order <- 4                            # order of polinomial smoothing

# choose output graphics device. It can be 'eps', 'png' or '' 
plot.out <- 'eps'
plot.out <- 'png'
plot.out <- ''     # default shows plots on the screen

source("../Utils/Unfold/responseMtrx.R")
source("../Utils/Unfold/bayes_unf.R")
source("../Utils/Unfold/bayes_extra.R")
mc.before  <- return1Dvector("WpToEleNu/pstFsrDist.txt", nC) # extract true distribution
mc.matr <- returnMtrix("WpToEleNu/responseDist.txt",nC,nE)
#mc.matr <- returnMtrix("WpToEleNuNoTypeI/responseDist.txt",nC,nE)
obs <- return1Dvector("WpToEleNu/simulDist.txt",nc)

# Analyse MC events to infer smearing matrix
mc.smear <- infer.pec(mc.before, mc.matr, ZERO.HANDLING = 2)
#-------- some printouts ---------------------------------
cat ( sprintf("\n1) MC evaluation of smearing ---------------------------\n") )
cat ( sprintf("   Generated \n") )
print(mc.before)
cat ( sprintf("   Reconstructed in the various bins\n" ) )
print(mc.matr)
cat ( sprintf("   smearing matrix (expected values; last row is the inefficiency)\n" ) )
print(mc.smear$E.pec)
cat ( sprintf("   observed evets \n" ) )
print(obs)
#-------------------------------------------------------------
# Unfolding ##################################################
cat ( sprintf("\n\n3) Unfolding --------------------------------------\n" ) )
prior0 <-  rep(1/nC, nC)#uniform prior (Note: nC and nE are defined in simula.R)
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
#-------- print some results and compare with true distribution -------------
cat ( sprintf("\n\n   Observed:\n" ) )
print(obs)
result <- data.frame( generated=mc.before, estimated=unfolded$xm , sigma=unfolded$xs )
print.data.frame(result)
#---------------------------------------------------------------------------

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
    max.c <- max(obs,mc.before,unfolded$xm)*1.05
    plot(y, obs, ylim=c(0,max.c), type='l', col='red', lwd=2, xlab="", ylab="")
    lines(x, mc.before, lwd=2)
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
