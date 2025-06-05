#include "BinomialTree.h"
#include <cmath>
#include <vector>
#include <algorithm>

// Function to price a European or American call option using the Binomial Tree method
double binomial_tree_call(double S, double K, double r, double T, double sigma, int steps, bool american) {
    double dt = T / steps;                             // Time step size
    double u = std::exp(sigma * std::sqrt(dt));        // Up factor
    double d = 1.0 / u;                                // Down factor (inverse of up)
    double p = (std::exp(r * dt) - d) / (u - d);       // Risk-neutral up probability

    std::vector<double> prices(steps + 1);             // Terminal stock prices
    std::vector<double> values(steps + 1);             // Option values at each node

    // Compute option values at maturity
    for (int i = 0; i <= steps; ++i) {
        prices[i] = S * std::pow(u, steps - i) * std::pow(d, i);       // Stock price at node
        values[i] = std::max(0.0, prices[i] - K);                      // Call payoff: max(S - K, 0)
    }

    // Backward induction through the tree
    for (int step = steps - 1; step >= 0; --step) {
        for (int i = 0; i <= step; ++i) {
            prices[i] = prices[i] / u;                                 // Step back one level in price
            values[i] = std::exp(-r * dt) * (p * values[i] + (1 - p) * values[i + 1]);  // Discounted expected value

            // If American, check early exercise value
            if (american)
                values[i] = std::max(values[i], prices[i] - K);
        }
    }

    return values[0];  // Option value at root node
}

// Function to price a European or American put option using the Binomial Tree method
double binomial_tree_put(double S, double K, double r, double T, double sigma, int steps, bool american) {
    double dt = T / steps;                             // Time step size
    double u = std::exp(sigma * std::sqrt(dt));        // Up factor
    double d = 1.0 / u;                                // Down factor
    double p = (std::exp(r * dt) - d) / (u - d);       // Risk-neutral probability

    std::vector<double> prices(steps + 1);             // Terminal stock prices
    std::vector<double> values(steps + 1);             // Option values at each node

    // Compute option values at maturity
    for (int i = 0; i <= steps; ++i) {
        prices[i] = S * std::pow(u, steps - i) * std::pow(d, i);       // Stock price at node
        values[i] = std::max(0.0, K - prices[i]);                      // Put payoff: max(K - S, 0)
    }

    // Backward induction through the tree
    for (int step = steps - 1; step >= 0; --step) {
        for (int i = 0; i <= step; ++i) {
            prices[i] = prices[i] / u;                                 // Step back one level in price
            values[i] = std::exp(-r * dt) * (p * values[i] + (1 - p) * values[i + 1]);  // Discounted expected value

            // If American, check early exercise value
            if (american)
                values[i] = std::max(values[i], K - prices[i]);
        }
    }

    return values[0];  // Option value at root node
}
