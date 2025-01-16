/*
 * File: SimulationBuilder.hpp
 * Author: Yumin Wu
 * Date: 01/13/2025
 *
 * Description:
 * This file defines the SimulationBuilder class, which is responsible for constructing and configuring
 * the components required for a Monte Carlo simulation. The class allows users to select and configure
 * the Stochastic Differential Equation (SDE), Finite Difference Method (FDM), Random Number Generator (RNG),
 * and Payoff function. It also handles the initial conditions for the simulation, such as the initial stock price,
 * maturity, number of time steps, and number of simulations. The class provides both direct setter methods
 * and an interactive user configuration method to build the simulation setup.
 */

#ifndef SIMULATIONBUILDER_HPP
#define SIMULATIONBUILDER_HPP

#include <memory>
#include <tuple>
#include <iostream>
#include <stdexcept>
#include "SDE.hpp"
#include "FDM.hpp"
#include "RNG.hpp"
#include "Payoff.hpp"

class SimulationBuilder
{
private:
    std::shared_ptr<SDE> sde;           // Stochastic Differential Equation model
    std::shared_ptr<FDM> fdm;           // Finite Difference Method for numerical integration
    std::shared_ptr<RNG> rng;           // Random Number Generator for simulating Wiener process increments
    std::shared_ptr<Payoff> payoff;     // Payoff function for option pricing
    double S0, T;                       // Initial stock price and maturity
    int N, M;                           // Number of time steps and simulations

    std::shared_ptr<SDE> selectSDE();                           // Helper method to select SDE model
    std::shared_ptr<FDM> selectFDM(std::shared_ptr<SDE> sde);   // Helper method to select FDM scheme
    std::shared_ptr<RNG> selectRNG();                           // Helper method to select RNG
    std::shared_ptr<Payoff> selectPayoff();                     // Helper method to select Payoff function
    double getStrikePrice();                                    // Helper method to get strike price from user
    double getBarrierLevel();                                   // Helper method to get barrier level from user

public:
    SimulationBuilder(); // Constructor

    // Direct setter methods for configuring components
    SimulationBuilder& setSDE(std::shared_ptr<SDE> s);
    SimulationBuilder& setFDM(std::shared_ptr<FDM> f);
    SimulationBuilder& setRNG(std::shared_ptr<RNG> r);
    SimulationBuilder& setPayoff(std::shared_ptr<Payoff> p);
    SimulationBuilder& setInitialCondition(double s0, double t, int n, int m);

    // Interactive user configuration method
    SimulationBuilder& configureFromUser();

    // Build method to finalize and return the simulation configuration
    std::tuple<std::shared_ptr<SDE>, std::shared_ptr<FDM>, std::shared_ptr<RNG>, std::shared_ptr<Payoff>, double, double, int, int> build() const;
};

#endif // SIMULATIONBUILDER_HPP