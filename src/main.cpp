#include <iostream>
#include "BlackScholes.h"

int main() {
    double S = 100.0;     // Spot price
    double K = 100.0;     // Strike price
    double r = 0.05;      // Risk-free rate
    double T = 1.0;       // Time to maturity
    double sigma = 0.2;   // Volatility

    double call = black_scholes_call(S, K, r, T, sigma);
    double put = black_scholes_put(S, K, r, T, sigma);

    std::cout << "Call Price: " << call << std::endl;
    std::cout << "Put Price: " << put << std::endl;

    return 0;
}

