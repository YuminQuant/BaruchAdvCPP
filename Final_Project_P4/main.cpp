/*
 * File: main.cpp
 * Author: Yumin Wu
 * Date: 01/13/2025
 *
 * Description:
 * This file serves as the entry point for the Monte Carlo simulation program. It tests various configurations
 * of the simulation, including different option types, FDM (Finite Difference Method) schemes, and SDE (Stochastic Differential Equation) models.
 * The program uses the SimulationBuilder and MCMediator classes to configure and run the simulations, and it measures the execution time
 * using the StopWatch class. The main function calls three test functions: testDifferentOptions, testDifferentFDM, and testDifferentSDE,
 * which demonstrate the flexibility and capabilities of the simulation framework.
 */

#include <iostream>
#include <memory>
#include <stdexcept>
#include "SimulationBuilder.hpp"
#include "MCMediator.hpp"
#include "StopWatch.hpp"  // Include StopWatch header for timing

 // Forward declarations of test functions
void testDifferentOptions(); // Test different option types
void testDifferentFDM();     // Test different FDM schemes
void testDifferentSDE();     // Test different SDE models

// Global variables for simulation parameters
double S0 = 100.0;  // Initial stock price
double K = 100.0;   // Strike price
double T = 1.0;     // Maturity (time to expiration)
double r = 0.05;    // Risk-free interest rate
double sigma = 0.2; // Volatility
double B = 110.0;   // Barrier level for barrier options
int N = 500;        // Number of time steps
int M = 100000;      // Number of simulations

int main()
{
    try
    {
        // Call test functions to demonstrate different simulation configurations
        testDifferentOptions(); // Test different option types
        testDifferentFDM();     // Test different FDM schemes
        testDifferentSDE();     // Test different SDE models
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl; // Handle any exceptions
        return 1;
    }
    return 0;
}

// Test different option types
void testDifferentOptions()
{
    std::cout << "Testing different option types..." << std::endl;

    StopWatch stopWatch;                                        // Timer for measuring execution time

    // Price European Call using user input
    auto builder1 = std::make_shared<SimulationBuilder>();
    builder1->configureFromUser();                              // Configure simulation using user input
    auto mediator1 = std::make_shared<MCMediator>(builder1);    // Create mediator
    stopWatch.StartStopWatch();                                 // Start timer
    double price1 = mediator1->runSimulation();                 // Run simulation
    stopWatch.StopStopWatch();                                  // Stop timer
    std::cout << "European Call Price (User Input): " << price1 << std::endl;
    std::cout << "Time taken: " << stopWatch.GetTime() << " seconds" << std::endl;
    std::cout << std::endl;

    // Price Asian Put using predefined parameters
    stopWatch.Reset();                                          // Reset timer
    stopWatch.StartStopWatch();                                 // Start timer
    auto builder2 = std::make_shared<SimulationBuilder>();
    builder2->setInitialCondition(S0, T, N, M)                  // Set initial conditions
        .setSDE(std::make_shared<GBM>(r, sigma))                // Set GBM SDE
        .setFDM(std::make_shared<EulerMethod>(std::make_shared<GBM>(r, sigma))) // Set Euler FDM
        .setRNG(std::make_shared<MersenneTwister>())            // Set Mersenne Twister RNG
        .setPayoff(std::make_shared<AsianOption>(K, false));    // Set Asian Put payoff
    auto mediator2 = std::make_shared<MCMediator>(builder2);    // Create mediator
    double price2 = mediator2->runSimulation();                 // Run simulation
    stopWatch.StopStopWatch();                                  // Stop timer
    std::cout << "Asian Put Price: " << price2 << std::endl;
    std::cout << "Time taken: " << stopWatch.GetTime() << " seconds" << std::endl;
    std::cout << std::endl;

    // Price Down-and-In Call using predefined parameters
    stopWatch.Reset();                                          // Reset timer
    stopWatch.StartStopWatch();                                 // Start timer
    auto builder3 = std::make_shared<SimulationBuilder>();
    builder3->setInitialCondition(S0, T, N, M)                  // Set initial conditions
        .setSDE(std::make_shared<GBM>(r, sigma))                // Set GBM SDE
        .setFDM(std::make_shared<EulerMethod>(std::make_shared<GBM>(r, sigma))) // Set Euler FDM
        .setRNG(std::make_shared<MersenneTwister>())                            // Set Mersenne Twister RNG
        .setPayoff(std::make_shared<BarrierOption>(K, B, true, false, true));   // Set Down-and-In Call payoff
    auto mediator3 = std::make_shared<MCMediator>(builder3);                    // Create mediator
    double price3 = mediator3->runSimulation();                                 // Run simulation
    stopWatch.StopStopWatch();                                                  // Stop timer
    std::cout << "Down and In Call Price: " << price3 << std::endl;
    std::cout << "Time taken: " << stopWatch.GetTime() << " seconds" << std::endl;
    std::cout << std::endl;

    // Price Up-and-Out Put using predefined parameters
    stopWatch.Reset();                                                          // Reset timer
    stopWatch.StartStopWatch();                                                 // Start timer
    auto builder4 = std::make_shared<SimulationBuilder>();
    builder4->setInitialCondition(S0, T, N, M)                                  // Set initial conditions
        .setSDE(std::make_shared<GBM>(r, sigma))                                // Set GBM SDE
        .setFDM(std::make_shared<EulerMethod>(std::make_shared<GBM>(r, sigma))) // Set Euler FDM
        .setRNG(std::make_shared<MersenneTwister>())                            // Set Mersenne Twister RNG
        .setPayoff(std::make_shared<BarrierOption>(K, B, false, true, false));  // Set Up-and-Out Put payoff
    auto mediator4 = std::make_shared<MCMediator>(builder4);                    // Create mediator
    double price4 = mediator4->runSimulation();                                 // Run simulation
    stopWatch.StopStopWatch();                                                  // Stop timer
    std::cout << "Up and Out Put Price: " << price4 << std::endl;
    std::cout << "Time taken: " << stopWatch.GetTime() << " seconds" << std::endl;
    std::cout << std::endl;
}

// Test different FDM methods
void testDifferentFDM()
{
    std::cout << "Testing different FDM methods..." << std::endl;

    StopWatch stopWatch;                                    // Timer for measuring execution time

    // Price European Call using Euler method
    stopWatch.StartStopWatch();                             // Start timer
    auto builder1 = std::make_shared<SimulationBuilder>();
    builder1->setInitialCondition(S0, T, N, M)              // Set initial conditions
        .setSDE(std::make_shared<GBM>(r, sigma))            // Set GBM SDE
        .setFDM(std::make_shared<EulerMethod>(std::make_shared<GBM>(r, sigma))) // Set Euler FDM
        .setRNG(std::make_shared<MersenneTwister>())        // Set Mersenne Twister RNG
        .setPayoff(std::make_shared<EuropeanCall>(K));      // Set European Call payoff
    auto mediator1 = std::make_shared<MCMediator>(builder1); // Create mediator
    double price1 = mediator1->runSimulation();             // Run simulation
    stopWatch.StopStopWatch();                              // Stop timer
    std::cout << "European Call Price (Euler Method): " << price1 << std::endl;
    std::cout << "Time taken: " << stopWatch.GetTime() << " seconds" << std::endl;
    std::cout << std::endl;

    // Price European Call using Milstein method
    stopWatch.Reset(); // Reset timer
    stopWatch.StartStopWatch(); // Start timer
    auto builder2 = std::make_shared<SimulationBuilder>();
    builder2->setInitialCondition(S0, T, N, M)              // Set initial conditions
        .setSDE(std::make_shared<GBM>(r, sigma))            // Set GBM SDE
        .setFDM(std::make_shared<MilsteinMethod>(std::make_shared<GBM>(r, sigma))) // Set Milstein FDM
        .setRNG(std::make_shared<MersenneTwister>())        // Set Mersenne Twister RNG
        .setPayoff(std::make_shared<EuropeanCall>(K));      // Set European Call payoff
    auto mediator2 = std::make_shared<MCMediator>(builder2); // Create mediator
    double price2 = mediator2->runSimulation();             // Run simulation
    stopWatch.StopStopWatch();                              // Stop timer
    std::cout << "European Call Price (Milstein Method): " << price2 << std::endl;
    std::cout << "Time taken: " << stopWatch.GetTime() << " seconds" << std::endl;
    std::cout << std::endl;
}

// Test different SDE models
void testDifferentSDE()
{
    std::cout << "Testing different SDE methods..." << std::endl;

    StopWatch stopWatch;                                    // Timer for measuring execution time

    // Price Asian Put using GBM SDE
    stopWatch.StartStopWatch(); // Start timer
    auto builder1 = std::make_shared<SimulationBuilder>();
    builder1->setInitialCondition(S0, T, N, M)               // Set initial conditions
        .setSDE(std::make_shared<GBM>(r, sigma))             // Set GBM SDE
        .setFDM(std::make_shared<EulerMethod>(std::make_shared<GBM>(r, sigma))) // Set Euler FDM
        .setRNG(std::make_shared<MersenneTwister>())         // Set Mersenne Twister RNG
        .setPayoff(std::make_shared<AsianOption>(K, false)); // Set Asian Put payoff
    auto mediator1 = std::make_shared<MCMediator>(builder1); // Create mediator
    double price1 = mediator1->runSimulation();              // Run simulation
    stopWatch.StopStopWatch();                               // Stop timer
    std::cout << "Asian Put Price (GBM): " << price1 << std::endl;
    std::cout << "Time taken: " << stopWatch.GetTime() << " seconds" << std::endl;
    std::cout << std::endl;

    // Price Asian Put using CIR SDE
    stopWatch.Reset();                                      // Reset timer
    stopWatch.StartStopWatch();                             // Start timer
    auto builder2 = std::make_shared<SimulationBuilder>();
    builder2->setInitialCondition(S0, T, N, M)              // Set initial conditions
        .setSDE(std::make_shared<CIR>(0.1, 0.2, 0.3))       // Set CIR SDE
        .setFDM(std::make_shared<EulerMethod>(std::make_shared<CIR>(0.1, 0.2, 0.3))) // Set Euler FDM
        .setRNG(std::make_shared<MersenneTwister>())        // Set Mersenne Twister RNG
        .setPayoff(std::make_shared<AsianOption>(K, false)); // Set Asian Put payoff
    auto mediator2 = std::make_shared<MCMediator>(builder2); // Create mediator
    double price2 = mediator2->runSimulation();             // Run simulation
    stopWatch.StopStopWatch();                              // Stop timer
    std::cout << "Asian Put Price (CIR): " << price2 << std::endl;
    std::cout << "Time taken: " << stopWatch.GetTime() << " seconds" << std::endl;
    std::cout << std::endl;

    // Price Asian Put using CEV SDE
    stopWatch.Reset();                                      // Reset timer
    stopWatch.StartStopWatch();                             // Start timer
    auto builder3 = std::make_shared<SimulationBuilder>();
    builder3->setInitialCondition(S0, T, N, M)              // Set initial conditions
        .setSDE(std::make_shared<CEV>(r, sigma, 0.5))       // Set CEV SDE
        .setFDM(std::make_shared<EulerMethod>(std::make_shared<CEV>(r, sigma, 0.5))) // Set Euler FDM
        .setRNG(std::make_shared<MersenneTwister>())        // Set Mersenne Twister RNG
        .setPayoff(std::make_shared<AsianOption>(K, false)); // Set Asian Put payoff
    auto mediator3 = std::make_shared<MCMediator>(builder3); // Create mediator
    double price3 = mediator3->runSimulation();             // Run simulation
    stopWatch.StopStopWatch();                              // Stop timer
    std::cout << "Asian Put Price (CEV): " << price3 << std::endl;
    std::cout << "Time taken: " << stopWatch.GetTime() << " seconds" << std::endl;
    std::cout << std::endl;
}