#include <iostream>
#include <RcppArmadillo.h>
#include <stdlib.h> 
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <cmath>
#include <Rcpp.h>
#include "element_wise.h"
// [[Rcpp::depends(RcppArmadillo)]]

using namespace std; 
using namespace arma;
using namespace Rcpp; 

//[[Rcpp::export]]
arma::mat linearSolveCpp(arma::mat X, arma::mat b){
  arma::mat A = X.t() * X;
  arma::mat b_A = X.t() * b;
  arma::mat betas = solve(A,b_A); 
  return(betas); 
}


//[[Rcpp::export]]
void labelEMCpp(arma::vec X) {
  
  arma::mat pi_o(2,X.size());
  
  double mu_init_1 = 2; 
  double mu_init_2 = -2; 
  double sig_init_1 = 1; 
  double sig_init_2 = 1; 
  
  double pi_1 = 0.5; 
  double pi_2 = 1 - pi_1; 
  
  arma::vec pxA = arma::vec(X.size()); 
  arma::vec pxB = arma::vec(X.size());
  
  double muA = mu_init_1; 
  double muB = mu_init_2; 
  double sig_1 = sig_init_1;
  double sig_2 = sig_init_2; 
  
  double var_1;
  double var_2;
  
  arma:vec log_lik = arma::vec(2); 
  
  log_lik[0] = 0;
  
  for (int i; i < X.size(); i++ ){
    pxA[i] = R::dnorm(X[i],muA,sig_1,FALSE); 
    pxB[i] = R::dnorm(X[i],muB,sig_2,FALSE);
  }
  
  log_lik[1] = -log(prod((pi_1 * pxA + pi_2 * pxB)));
  
  double diff = abs(log_lik[1] - log_lik[0]); 
    
  int count = 0; 
  
  do {  
    
    // E -Step 
    for (int i; i < X.size(); i++ ){
      pxA[i] = R::dnorm(X[i],muA,sig_1,FALSE); 
      pxB[i] = R::dnorm(X[i],muB,sig_2,FALSE);
    }
    
    arma::vec num_1 = pi_1 * pxA; 
    arma::vec num_2 = pi_2 * pxB; 
    arma::vec denom = (num_1 + num_2); 
    
    arma::vec zi_1 = num_1 / denom;
    arma::vec zi_2 = 1 - zi_1; 
    
    // M Step 
    pi_1 = mean(zi_1); 
    pi_2 = 1 - pi_1;
    
    // Calculate New means
    muA = sum(zi_1.t() * X) / sum(zi_1);   
    muB = sum(zi_2.t() * X)/ sum(zi_2); 
    
    
    // Calculate New SD
    var_1 = sum(zi_1.t() * element_wise_power((X-muA),2)) / sum(zi_1);
    var_2 = sum(zi_2.t() * element_wise_power((X-muB),2)) / sum(zi_2);
    
    sig_1 =  std::sqrt((double)var_1);
    sig_2 = std::sqrt((double)var_2);
    
    log_lik[0] = log_lik[1];
    
    log_lik[1] = -log(prod((pi_1 * pxA + pi_2 * pxB)));
    
      
    diff = abs(log_lik[1] - log_lik[0]); 
    
    cout << "*";
    
    ++count;  
      
  } while (count < 100);  
  
  cout << "\n" << endl;
  cout << "Mean A is " << muA << endl;
  cout << "Mean B is " <<  muB << endl;
  cout << "Sig A is "<< sig_1 << endl;
  cout << "Sig B is " << sig_2 << endl;

}


/***R
test <- c(rnorm(10000,10,1),rnorm(10000,-3,1))
labelEMCpp(X = test)
# it works !
*/