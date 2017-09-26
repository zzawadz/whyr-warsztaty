#include <RcppArmadillo.h>
//[[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::plugins(cpp11)]]



// [[Rcpp::export]]
arma::vec mvrnorm2(arma::mat sigma) {
  
  arma::vec result(sigma.n_cols);
  
  for(size_t i = 0; i < sigma.n_cols; i++) {
    result.at(i) = ::Rf_rnorm(0.0, 1.0);
  }
  
  return chol(sigma).t() * result;
}

// [[Rcpp::export]]
Rcpp::List cgibbs(arma::mat y, arma::mat x, arma::mat xx, arma::mat beta, double df, int n = 1000) {

  arma::mat result(n, x.n_cols);
  std::vector<double> tau_vec;

  for(int i = 0; i < n; i++) {

    double sb  = arma::accu(arma::square(y - x * beta));
    double tau = R::rgamma(df/2.0, sb / 2.0);
    arma::vec beta_tmp = mvrnorm2(1/tau*xx) + beta;
    result.row(i) = beta_tmp.t();
    tau_vec.push_back(tau);
    
  }

  return Rcpp::List::create(Rcpp::Named("beta") = result,
                            Rcpp::Named("tau") = tau_vec);
}

