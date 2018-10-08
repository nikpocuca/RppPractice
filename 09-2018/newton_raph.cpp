#include <RcppArmadillo.h>
#include <cmath>   // std::abs
#include <iostream>

// [[Rcpp::depends(RcppArmadillo)]]

using namespace arma;

// [[Rcpp::export]]

double newton_raphson(double x_o) {
  
  double x_pi = x_o;
  double x_p1;
  
  for(;;) {

  x_p1 = x_pi - (pow(x_pi,2))/(2*x_pi);
  
  std::cout << " Iteration: " << x_p1 << " - "  << x_pi << std::endl; 
  
  if ( std::abs(x_p1 - x_pi) < 0.0001) { break;};
  
  x_pi = x_p1;
    
  }
  /*
  do {
    
    //x_p1 = x_pi - (pow(x_pi,3))/(3*(pow(x_pi,2)));
    
    x_p1 = x_pi - (pow(x_pi,2))/(2*x_pi);
    
    x_pi = x_p1;
    
  } while ( std::abs(x_p1 - x_pi) > 0.00001 );
  */
  return(x_p1);
}


