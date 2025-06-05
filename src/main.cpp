#include <iostream>
#include <fstream>
#include "BlackScholes.h"
#include "BinomialTree.h"
#include "MonteCarlo.h"

int main() {
    double S, K, r, T, sigma;
    int steps, simulations;

    std::cout << "=== Option Pricing Calculator ===\n";
    std::cout << "Enter spot price (S): ";
    std::cin >> S;
    std::cout << "Enter strike price (K): ";
    std::cin >> K;
    std::cout << "Enter risk-free interest rate (r, in decimal): ";
    std::cin >> r;
    std::cout << "Enter time to maturity (T, in years): ";
    std::cin >> T;
    std::cout << "Enter volatility (sigma, in decimal): ";
    std::cin >> sigma;
    std::cout << "Enter number of steps for Binomial Tree: ";
    std::cin >> steps;
    std::cout << "Enter number of simulations for Monte Carlo: ";
    std::cin >> simulations;

    // === Black-Scholes ===
    double bs_call = black_scholes_call(S, K, r, T, sigma);
    double bs_put  = black_scholes_put(S, K, r, T, sigma);

    std::cout << "\n--- Black-Scholes ---\n";
    std::cout << "Call Price: " << bs_call << "\n";
    std::cout << "Put Price:  " << bs_put << "\n";

    // === Binomial Tree ===
    double euro_call_bt = binomial_tree_call(S, K, r, T, sigma, steps, false);
    double euro_put_bt  = binomial_tree_put(S, K, r, T, sigma, steps, false);
    double amer_call_bt = binomial_tree_call(S, K, r, T, sigma, steps, true);
    double amer_put_bt  = binomial_tree_put(S, K, r, T, sigma, steps, true);

    std::cout << "\n--- Binomial Tree ---\n";
    std::cout << "European Call: " << euro_call_bt << "\n";
    std::cout << "European Put:  " << euro_put_bt << "\n";
    std::cout << "American Call: " << amer_call_bt << "\n";
    std::cout << "American Put:  " << amer_put_bt << "\n";

    // === Monte Carlo ===
    auto [mc_call, ci_call] = monte_carlo_call(S, K, r, T, sigma, simulations);
    auto [mc_put, ci_put]   = monte_carlo_put(S, K, r, T, sigma, simulations);

    std::cout << "\n--- Monte Carlo (95% CI) ---\n";
    std::cout << "Call Price: " << mc_call << " ± " << ci_call << "\n";
    std::cout << "Put Price:  " << mc_put << " ± " << ci_put << "\n";

    // === Greeks ===
    double delta_call = bs_delta_call(S, K, r, T, sigma);
    double delta_put  = bs_delta_put(S, K, r, T, sigma);
    double gamma      = bs_gamma(S, K, r, T, sigma);
    double vega       = bs_vega(S, K, r, T, sigma);

    std::cout << "\n--- Greeks (Black-Scholes) ---\n";
    std::cout << "Delta (Call): " << delta_call << "\n";
    std::cout << "Delta (Put):  " << delta_put << "\n";
    std::cout << "Gamma:        " << gamma << "\n";
    std::cout << "Vega:         " << vega << "\n";

    // === Export to CSV ===
    std::ofstream out("output.csv");
    if (!out) {
        std::cerr << "Error: Could not create output.csv\n";
        return 1;
    }

    // Write headers and results
    out << "Model,Type,Price,CI (if applicable)\n";
    out << "Black-Scholes,Call," << bs_call << ",\n";
    out << "Black-Scholes,Put," << bs_put << ",\n";
    out << "Binomial-European,Call," << euro_call_bt << ",\n";
    out << "Binomial-European,Put," << euro_put_bt << ",\n";
    out << "Binomial-American,Call," << amer_call_bt << ",\n";
    out << "Binomial-American,Put," << amer_put_bt << ",\n";
    out << "Monte Carlo,Call," << mc_call << "," << ci_call << "\n";
    out << "Monte Carlo,Put," << mc_put << "," << ci_put << "\n";

    out << "\nGreek,Value\n";
    out << "Delta (Call)," << delta_call << "\n";
    out << "Delta (Put)," << delta_put << "\n";
    out << "Gamma," << gamma << "\n";
    out << "Vega," << vega << "\n";

    out.close();
    std::cout << "\nResults written to output.csv\n";

    return 0;
}
