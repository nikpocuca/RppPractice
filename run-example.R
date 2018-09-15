# Load library
library(Rcpp)

# source file with functions

sourceCpp("example.cpp")

# Run functions as per usual in R, 

factorc(4)

# now you can make cpp functions that are much faster than R. 


