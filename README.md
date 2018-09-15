# Introduction to Rcpp/RcppArmadillo



## Installation
With R installed and added to path,

Run: 

install.packages("Rcpp")
install.packages("RcppArmadillo")

## Sourcing 

To source files in an R script you need to set up your cpp file like in example.cpp 

Basics:

At the top of the .cpp file you must have,
#include <RcppArmadillo.h>  or #include <Rcpp.h> but not both. You can only have one. 


One line proceeding after for Armadillo you must have 

// [[Rcpp::depends(RcppArmadillo)]]


Above the function definition you must have 

// [[Rcpp::export]]
/*  function definition */ 


To source file see run-example.R 

summary, you are using Rcpp and the function sourceCpp("<filename>") in line. 
