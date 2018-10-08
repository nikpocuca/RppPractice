#include <RcppArmadillo.h>

// [[Rcpp::depends(RcppArmadillo)]]

using namespace arma;

// [[Rcpp::export]]

arma::vec gen_randoms(int a){
	
	vec values = arma::randi<vec>(a,arma::distr_param(1,10));

	return(values);

}


