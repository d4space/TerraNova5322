returnMtrix <- function(responseTable, nC, nE)
{
  obsi <- matrix(rep(0,nC*nE), nC, nE)
  table = read.table(responseTable)
  for ( i in 1:nC )for(j in 1:nE )
  {
    obsi[i,j] = table[i,j]
  }
  return (obsi)
}
return1Dvector <- function(Table, nC)
{
#obsi <- c(rep(0,nC))
  obsi <- scan( Table)
#table = read.table(Table)
#  obsi <- c(table)
#table = read.table(Table)
#  for ( i in 1:nC )
#  {
#    obsi[i] = table[i]
#  }
  return (obsi)
}
