/*
 * File: MCMediator.hpp
 * Author: Yumin Wu
 * Date: 01/13/2025
 *
 * Description:
 * This file defines the MCMediator class, which acts as an intermediary between the simulation builder and the Monte Carlo solver.
 * The MCMediator class is responsible for constructing the Monte Carlo solver using a configuration provided by the SimulationBuilder
 * and running the simulation to compute the option price. This class simplifies the interaction between the builder and the solver,
 * providing a clean interface for running Monte Carlo simulations.
 */

#ifndef MCMEDIATOR_HPP
#define MCMEDIATOR_HPP

#include <memory>
#include "SimulationBuilder.hpp"
#include "MCSolver.hpp"

class MCMediator
{
private:
    std::shared_ptr<MCSolver> solver; // Monte Carlo solver for option pricing

public:
    MCMediator(std::shared_ptr<SimulationBuilder> builder); // Constructor
    double runSimulation(); // Run the Monte Carlo simulation and return the option price
};

#endif // MCMEDIATOR_HPP