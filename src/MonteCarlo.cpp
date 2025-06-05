#include "MonteCarlo.h"
#include <cmath>
#include <random>
#include <vector>

// Monte Carlo simulation for European call with 95% confidence interval
std::pair<double, double> monte_carlo_call(double S, double K, double r, double T, double sigma, int simulations) {
    std::mt19937 gen(std::random_device{}());
    std::normal_distribution<> dist(0.0, 1.0);

    std::vector<double> payoffs(simulations);

    // Simulate payoffs
    for (int i = 0; i < simulations; ++i) {
        double Z = dist(gen);
        double ST = S * std::exp((r - 0.5 * sigma * sigma) * T + sigma * std::sqrt(T) * Z);
        payoffs[i] = std::exp(-r * T) * std::max(ST - K, 0.0);  // Discounted payoff
    }

    // Compute mean
    double sum = 0.0;
    for (double p : payoffs) sum += p;
    double mean = sum / simulations;

    // Compute standard deviation
    double sq_sum = 0.0;
    for (double p : payoffs) sq_sum += (p - mean) * (p - mean);
    double stddev = std::sqrt(sq_sum / (simulations - 1));

    // 95% confidence interval half-width
    double ci = 1.96 * stddev / std::sqrt(simulations);

    return {mean, ci};
}

// Same for put option
std::pair<double, double> monte_carlo_put(double S, double K, double r, double T, double sigma, int simulations) {
    std::mt19937 gen(std::random_device{}());
    std::normal_distribution<> dist(0.0, 1.0);

    std::vector<double> payoffs(simulations);

    for (int i = 0; i < simulations; ++i) {
        double Z = dist(gen);
        double ST = S * std::exp((r - 0.5 * sigma * sigma) * T + sigma * std::sqrt(T) * Z);
        payoffs[i] = std::exp(-r * T) * std::max(K - ST, 0.0);
    }

    double sum = 0.0;
    for (double p : payoffs) sum += p;
    double mean = sum / simulations;

    double sq_sum = 0.0;
    for (double p : payoffs) sq_sum += (p - mean) * (p - mean);
    double stddev = std::sqrt(sq_sum / (simulations - 1));

    double ci = 1.96 * stddev / std::sqrt(simulations);

    return {mean, ci};
}
