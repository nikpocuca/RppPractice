#include <Rcpp.h>
#include <iostream>
using namespace Rcpp;


// [[Rcpp::export]]
List em_norm(NumericVector x, int n) {

  // Initialize pi. 
  

  int size_x = x.size(); 
  
  NumericVector x_p1 = x + 1; 
  
  return List::create(size_x, x_p1); 
}

