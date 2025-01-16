/*
 * File: MCSolver.cpp
 * Author: Yumin Wu
 * Date: 01/13/2025
 *
 * Description:
 * This file implements the MCSolver class, which performs Monte Carlo simulations to solve stochastic differential equations (SDEs)
 * and compute option prices. The solver uses numerical methods (FDM) to advance the solution of the SDE, random number generation (RNG)
 * to simulate Wiener process increments, and payoff functions to calculate the option value based on the simulated price paths.
 * The class supports both standard options (e.g., European options) and path-dependent options (e.g., Asian options).
 */

#include "MCSolver.hpp"

MCSolver::MCSolver(const std::tuple<std::shared_ptr<SDE>, std::shared_ptr<FDM>, std::shared_ptr<RNG>, std::shared_ptr<Payoff>, double, double, int, int>& config)
    : sde(std::get<0>(config)), // Initialize SDE
    fdm(std::get<1>(config)), // Initialize FDM
    rng(std::get<2>(config)), // Initialize RNG
    payoff(std::get<3>(config)), // Initialize Payoff
    S0(std::get<4>(config)), // Initial stock price
    T(std::get<5>(config)), // Maturity
    N(std::get<6>(config)), // Number of time steps
    M(std::get<7>(config)) // Number of simulations
{
    // Validate input parameters
    if (!sde || !fdm || !rng || !payoff)
    {
        throw std::invalid_argument("One or more components (SDE, FDM, RNG, Payoff) are null.");
    }
    if (S0 <= 0 || T <= 0 || N <= 0 || M <= 0)
    {
        throw std::invalid_argument("Initial conditions (S0, T, N, M) must be positive.");
    }
}

double MCSolver::solve()
{
    double dt = T / N; // Time step size
    if (dt <= 0)
    {
        throw std::runtime_error("Time step (dt) must be positive.");
    }

    double sum = 0.0; // Accumulator for payoff values
    for (int i = 0; i < M; ++i) // Loop over Monte Carlo simulations
    {
        double S = S0; // Initialize asset price
        std::vector<double> path(N + 1); // Store the price path for path-dependent options
        path[0] = S0; // Set initial price

        for (int j = 0; j < N; ++j) // Loop over time steps
        {
            double dW = std::sqrt(dt) * rng->generate(); // Generate Wiener process increment
            S = fdm->advance(S, j * dt, dt, dW); // Advance the solution using FDM
            if (S < 0)
            {
                throw std::runtime_error("Negative asset price encountered during simulation.");
            }
            path[j + 1] = S; // Store the price at the current time step
        }

        // Calculate payoff based on the option type
        if (auto asianPayoff = std::dynamic_pointer_cast<AsianOption>(payoff))
        {
            sum += (*payoff)(path); // Use the entire price path for Asian options
        }
        else
        {
            sum += (*payoff)(S); // Use the final price for standard options
        }
    }

    return sum / M; // Return the average payoff (option price)
}