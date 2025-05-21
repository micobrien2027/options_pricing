#ifndef BLACKSCHOLES_H
#define BLACKSCHOLES_H

double norm_cdf(double x);
double black_scholes_call(double S, double K, double r, double T, double sigma);
double black_scholes_put(double S, double K, double r, double T, double sigma);

#endif
