library(Rcpp)
library(tictoc)

points <- 100000
X_1 <- rnorm(points,5,2)
X_2 <- rnorm(points,3,1)
X_3 <- rnorm(points,2,3)

y <- 2*X_1 + 3*X_2 + 0.05*X_3 + rnorm(points,0,3)

X_input <- matrix(c(X_1,X_2,X_3),ncol = 3)


solveLinear <- function(X,b){
  A <- t(X) %*% X
  b_A <- t(X) %*% b
  betas <- solve(A,b_A)
  return(betas)
}

tic("Solving Using R")
solveLinear(X_input,y)
toc()

tic("Solving Using Cpp")
linearSolveCpp(X=X_input,b= as.matrix(y))
toc()
