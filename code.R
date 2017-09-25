getGibbsStats = function(fit, burn = 1000, n = 1000)
{
  sigma2 = summary(fit)$sigma^2
  X = model.matrix(fit)
  invXX = solve(t(X)%*%X)
  df = fit$df.residual
  coeff = fit$coefficients
  
  y <- model.frame(fit)[[1]]
  beta_hat = coeff
    
  sb = 0
  beta = beta_hat
  tau = 1/sigma2
  
  ntotal = burn + n
  parameters = matrix(nrow = ntotal, ncol = length(coeff))
  tau_res = NULL
  
  for(i in 1:ntotal) {
    # tau
    sb  = sum((y-X %*% beta)^2)
    tau = rgamma(1, df/2, 0.5*sb);
    # beta
    beta = mvrnorm(1, beta_hat, 1/tau*invXX)
    parameters[i,] = beta
    tau_res <- c(tau_res, tau)
  }
  
  return(list(parameters = parameters, tau = tau_res))
}

########################################

c_getGibbsStats = function(fit, burn = 1000, n = 1000)
{
  sigma2 = summary(fit)$sigma^2
  X = model.matrix(fit)
  invXX = solve(t(X)%*%X)
  df = fit$df.residual
  coeff = fit$coefficients
  
  y <- model.frame(fit)[[1]]
  beta = coeff
  
  cgibbs(y = as.matrix(y), x = X, xx = invXX, beta = as.matrix(beta), df = df, n = burn + n)
}
