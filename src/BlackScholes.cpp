#include "BlackScholes.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Cumulative distribution function for standard normal distribution
// Uses complementary error function for numerical stability
double norm_cdf(double x) {
    return 0.5 * std::erfc(-x / std::sqrt(2));
}

// Black-Scholes formula for pricing a European call option
double black_scholes_call(double S, double K, double r, double T, double sigma) {
    // d1 and d2 are intermediate calculations used in the formula
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);

    // Call price formula: S*N(d1) - K*e^(-rT)*N(d2)
    return S * norm_cdf(d1) - K * std::exp(-r * T) * norm_cdf(d2);
}

// Black-Scholes formula for pricing a European put option
double black_scholes_put(double S, double K, double r, double T, double sigma) {
    // Same d1 and d2 as in the call formula
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);

    // Put price formula: K*e^(-rT)*N(-d2) - S*N(-d1)
    return K * std::exp(-r * T) * norm_cdf(-d2) - S * norm_cdf(-d1);
}


// Standard normal probability density function
double norm_pdf(double x) {
    return std::exp(-0.5 * x * x) / std::sqrt(2 * M_PI);
}


// Delta (call): ∂Price/∂S = N(d1)
double bs_delta_call(double S, double K, double r, double T, double sigma) {
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    return norm_cdf(d1);
}

// Delta (put): ∂Price/∂S = N(d1) - 1
double bs_delta_put(double S, double K, double r, double T, double sigma) {
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    return norm_cdf(d1) - 1.0;
}

// Gamma: ∂²Price/∂S²
double bs_gamma(double S, double K, double r, double T, double sigma) {
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    return norm_pdf(d1) / (S * sigma * std::sqrt(T));
}

// Vega: ∂Price/∂σ
double bs_vega(double S, double K, double r, double T, double sigma) {
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    return S * norm_pdf(d1) * std::sqrt(T);
}
