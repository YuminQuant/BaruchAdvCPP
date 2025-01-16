/*
 * File: MCSolver.hpp
 * Author: Yumin Wu
 * Date: 01/13/2025
 *
 * Description:
 * This file defines the MCSolver (Monte Carlo Solver) class, which is used to simulate and solve stochastic differential equations (SDEs)
 * using the Monte Carlo method. The class integrates components for stochastic modeling (SDE), numerical methods (FDM), random number
 * generation (RNG), and payoff calculations (Payoff) to simulate asset price paths and compute option prices.
 * The solver is designed to handle both standard and path-dependent options, making it a versatile tool for financial derivative pricing.
 */

#ifndef MCSOLVER_HPP
#define MCSOLVER_HPP

#include <memory>
#include <tuple>
#include <stdexcept>
#include "SDE.hpp"
#include "FDM.hpp"
#include "RNG.hpp"
#include "Payoff.hpp"

class MCSolver
{
private:
    std::shared_ptr<SDE> sde; // Stochastic Differential Equation model
    std::shared_ptr<FDM> fdm; // Finite Difference Method for numerical integration
    std::shared_ptr<RNG> rng; // Random Number Generator for simulating Wiener process increments
    std::shared_ptr<Payoff> payoff; // Payoff function for option pricing
    double S0; // Initial stock price
    double T;  // Maturity (time to expiration)
    int N;     // Number of time steps
    int M;     // Number of Monte Carlo simulations

public:
    MCSolver(const std::tuple<std::shared_ptr<SDE>, std::shared_ptr<FDM>, std::shared_ptr<RNG>, std::shared_ptr<Payoff>, double, double, int, int>& config); // Constructor
    double solve(); // Solve the SDE and compute the option price
};

#endif // MCSOLVER_HPP