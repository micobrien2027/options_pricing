#ifndef BINOMIAL_TREE_H
#define BINOMIAL_TREE_H

double binomial_tree_call(double S, double K, double r, double T, double sigma, int steps, bool american);
double binomial_tree_put(double S, double K, double r, double T, double sigma, int steps, bool american);

#endif
