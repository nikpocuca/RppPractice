#include "element_wise.h"
#include <iostream>
#include <RcppArmadillo.h>
#include <stdlib.h> 
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <cmath>
// [[Rcpp::depends(RcppArmadillo)]]

arma::vec element_wise_power(arma::vec x, int p){
  
  for (int i; i < x.size();i++ ){
    x[i] = std::pow(x[i],p);
  }
  return(x);
}