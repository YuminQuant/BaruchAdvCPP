/*
 * File: MCMediator.cpp
 * Author: Yumin Wu
 * Date: 01/13/2025
 *
 * Description:
 * This file implements the MCMediator class, which acts as a bridge between the SimulationBuilder and the MCSolver.
 * The MCMediator class constructs the MCSolver using the configuration provided by the SimulationBuilder and then
 * runs the Monte Carlo simulation to compute the option price. This class provides a simple and clean interface
 * for setting up and executing Monte Carlo simulations in financial derivative pricing.
 */

#include "MCMediator.hpp"
#include <tuple>

MCMediator::MCMediator(std::shared_ptr<SimulationBuilder> builder)
{
    auto config = builder->build(); // Get the simulation configuration from the builder
    solver = std::make_shared<MCSolver>(config); // Initialize the Monte Carlo solver with the configuration
}

double MCMediator::runSimulation()
{
    return solver->solve(); // Run the simulation and return the computed option price
}