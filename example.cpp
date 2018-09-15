#include <RcppArmadillo.h>
  
// [[Rcpp::depends(RcppArmadillo)]]

// [[Rcpp::export]]

int factorc(int x) {
	if(x == 1) {  return 1; }
	if(x <= 1) {  return 1; }
	else {	
	return x*factorc(x-1); 	
	}
}




