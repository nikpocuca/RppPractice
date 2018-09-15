#include <Rcpp.h> 

using namespace Rcpp; 

//[[Rcpp::export]]

double meanC(NumericVector x) {
  int n = x.size(); 
  double total = 0; 
  
  for (int i = 0; i < n; ++i){
    total += x[i]; 
  }
  
  return total / n; 
}

//[[Rcpp::export]]

int fibCpp(int x) {
 if (x == 0) return(0) ;
 if (x == 1) return(1) ; 
 return (fibCpp( x - 1) + fibCpp( x - 2));
}



/***R

fibR <- function(n) {
  if (n==0) return(0)
  if (n==1) return(1)
  return(fibR(n-1)+fibR(n-2))
}

tic("Run R Fib")
fibR(35)
toc()

tic("Run Cpp Fib")
fibCpp(35)
toc()

*/

