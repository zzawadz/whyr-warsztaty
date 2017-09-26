#include <Rcpp.h>

// [[Rcpp::export]]
double maxmax(Rcpp::NumericVector x) {
  return Rcpp::algorithm::max(x.begin(), x.end());
}


// [[Rcpp::export(rng=false)]]
double maxmaxNoRng(Rcpp::NumericVector x) {
  return Rcpp::algorithm::max(x.begin(), x.end());
}


// [[Rcpp::export]]
Rcpp::List createList() {
  
  Rcpp::NumericVector x;
  Rcpp::NumericMatrix y;
  
  return Rcpp::List::create(Rcpp::Named("x") = x,
                            Rcpp::Named("y") = y);
}


// [[Rcpp::export]]
Rcpp::NumericVector callRFunctionGlobal(Rcpp::NumericVector x, std::string fName) {
  
  Rcpp::Environment env = Rcpp::Environment::global_env();
  Rcpp::Function fnc = env[fName];
  return fnc(x);
}

// [[Rcpp::export]]
Rcpp::NumericVector callRFunctionFromPackage(Rcpp::NumericVector x) {
  // Obtain environment containing function
  Rcpp::Environment base("package:stats"); 
  // Make function callable from C++
  Rcpp::Function sdR = base["sd"];
  
  return sdR(x);
}


/*** R
x = rnorm(10000)
microbenchmark::microbenchmark(maxmax(x), maxmaxNoRng(x))

myFnc <- function(x) {
  print("Jestem tu")
  sd(x)
}

callRFunctionFromPackage(x)
callRFunctionGlobal(x, fName = "myFnc")

*/

