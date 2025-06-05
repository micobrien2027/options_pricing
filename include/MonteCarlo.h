#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

#include <utility> // for std::pair

std::pair<double, double> monte_carlo_call(double S, double K, double r, double T, double sigma, int simulations);
std::pair<double, double> monte_carlo_put(double S, double K, double r, double T, double sigma, int simulations);

#endif

