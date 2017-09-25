//[[Rcpp::export]]
int cpp_sum(int x, int y) {
  return x + y;
}

int c_sum2(int x, int y) {
  return 2*x + 2*y;
}
