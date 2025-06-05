# 🧠 Options Pricing in C++

This project implements several numerical and analytical methods for pricing European and American options in C++. It includes:

- Black-Scholes Model (closed-form)
- Binomial Tree (American + European support)
- Monte Carlo Simulation (with confidence intervals)
- Calculation of Greeks (Delta, Gamma, Vega)
- CSV Export of results

---

## Why This Project?

In quantitative finance and derivatives trading, it’s critical to understand **how different pricing methods work** and their trade-offs. This project:

- Shows how **analytical**, **discrete**, and **stochastic** models compare
- Demonstrates **numerical convergence** and **Monte Carlo uncertainty**
- Calculates **Greeks**, essential for hedging and risk management
- Outputs results in **human-readable and machine-readable formats** (terminal + CSV)

---

## Features

| Method         | Use Case                                | Supports American? | Fast? | Exact? |
|----------------|------------------------------------------|---------------------|-------|--------|
| Black-Scholes  | Closed-form for European options         | ❌                  | ✅    | ✅     |
| Binomial Tree  | Step-wise tree for all vanilla options   | ✅                  | ⚠️    | Approx |
| Monte Carlo    | Simulation for European/exotic options   | ❌ (here)           | ⚠️    | Approx |
| Greeks         | Sensitivities for risk hedging           | ❌ (via BSM only)   | ✅    | ✅     |

---

## How to Build

### Requirements
- C++17 or higher
- Make (or build manually)

### Build with Makefile

```bash
make
