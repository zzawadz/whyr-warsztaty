library(MASS)
system.time(res <- getGibbsStats(fit = fit))

x <- matrix(rnorm(10000), ncol = 20)
y <- rnorm(nrow(x))

fit <- lm(y ~ x)

profvis::profvis({
  getGibbsStats(fit = fit, burn = 1000, n = 20000)
})

microbenchmark::microbenchmark(getGibbsStats(fit = fit), c_getGibbsStats(fit))



system.time(getGibbsStats(fit = fit))
system.time(c_getGibbsStats(fit = fit))
system.time(getGibbsStatsRen(fit = fit))

getGibbsStatsRen(fit)
