#include <RcppArmadillo.h>

using namespace arma; 
// [[Rcpp::depends(RcppArmadillo)]]



// [[Rcpp::export]]
void EM_Test(){
  
  uword d = 5;       // dimensionality
  uword N = 10000;   // number of samples (vectors)
  
  mat data(d, N, fill::zeros);
  
  vec mean1 = linspace<vec>(1,d,d);
  vec mean2 = mean1 + 2;
  uword i = 0;
  
  while(i < N)
  {
    if(i < N)  { data.col(i) = mean1 + randn<vec>(d); ++i; }
    if(i < N)  { data.col(i) = mean1 + randn<vec>(d); ++i; }
    if(i < N)  { data.col(i) = mean2 + randn<vec>(d); ++i; }
  }
  
  // model the data as a diagonal GMM with 2 Gaussians
  gmm_diag model;
  bool status = model.learn(data, 2, maha_dist, random_subset, 10, 5, 1e-10, true);
  if(status == false)  { cout << "learning failed" << endl; }
  
  model.means.print("means:");
  double overall_likelihood = model.avg_log_p(data);
  rowvec     set_likelihood = model.log_p( data.cols(0,9) );
  double  scalar_likelihood = model.log_p( data.col(0)    );
  
  uword   gaus_id  = model.assign( data.col(0),    eucl_dist );
  urowvec gaus_ids = model.assign( data.cols(0,9), prob_dist );
  urowvec histogram1 = model.raw_hist (data, prob_dist);
  rowvec histogram2 = model.norm_hist(data, eucl_dist);
  
  model.save("my_model.gmm");
  
  mat modified_dcovs = 2 * model.dcovs;
  model.set_dcovs(modified_dcovs); 
  
}


// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically 
// run after the compilation.
//

/*** R
EM_Test()
*/
