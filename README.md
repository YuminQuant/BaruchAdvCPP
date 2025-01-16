# BaruchAdvCPP
Final Project of the QuantNet/Baruch Pre-MFE Advanced CPP course (Advanced C++ and Modern Designs)

# 🚀 Monte Carlo Option Pricing Simulation

Welcome to the **Monte Carlo Option Pricing Simulation** framework! This project is designed to provide a flexible and efficient tool for pricing financial derivatives using Monte Carlo simulations. Whether you're working on European options, Asian options, or Barrier options, this framework has you covered.

## 🌟 Features

- **📈 Stochastic Differential Equations (SDEs)**: Supports Geometric Brownian Motion (GBM), Constant Elasticity of Variance (CEV), and Cox-Ingersoll-Ross (CIR) models.
- **🧮 Finite Difference Methods (FDM)**: Implements Euler, Milstein, and Drift-Adjusted Predictor-Corrector methods for solving SDEs.
- **🎲 Random Number Generation (RNG)**: Uses the Mersenne Twister algorithm for high-quality random number generation.
- **💰 Payoff Calculations**: Supports European, Asian, and Barrier options with customizable strike prices and barrier levels.
- **🛠️ Interactive Configuration**: Provides an interactive interface for setting up simulations.
- **⏱️ High-Precision Timing**: Includes a `StopWatch` class for measuring execution time.

## 🏗️ Project Structure

The project is organized into the following files:

- **StopWatch.cpp/hpp**: High-precision timer for measuring elapsed time.
- **FDM.cpp/hpp**: Finite Difference Method (FDM) class hierarchy for solving SDEs.
- **MCMediator.cpp/hpp**: Mediator between the simulation builder and the Monte Carlo solver.
- **MCSolver.cpp/hpp**: Monte Carlo solver for simulating asset price paths and computing option prices.
- **Payoff.cpp/hpp**: Payoff calculations for various option types.
- **RNG.cpp/hpp**: Random number generator using the Mersenne Twister algorithm.
- **SDE.cpp/hpp**: Stochastic Differential Equation (SDE) class hierarchy for modeling asset prices.
- **SimulationBuilder.cpp/hpp**: Builder pattern for configuring and setting up Monte Carlo simulations.
- **main.cpp**: Entry point of the program, containing test functions.

## 🚀 Getting Started

### Prerequisites

- A C++ compiler with support for C++11/14 (e.g., GCC, Clang, or MSVC).

## 🚧 Areas for Improvement

We are continuously working to enhance the framework. Here are some of the improvements we are considering:

1. **Performance Optimization**:  
   We are exploring the possibility of moving away from Object-Oriented Programming (OOP) for certain components (e.g., Random Number Generators - RNG) and adopting universal function wrappers. This change could significantly improve performance, as OOP (especially with virtual functions) can be slower in some cases.

2. **Concurrency for Monte Carlo Simulations**:  
   Monte Carlo simulations are an excellent candidate for concurrency. We are investigating:  
   - **1)** How to better separate asynchronous functionality from the core design. The design should function independently and then seamlessly integrate into a generic concurrent wrapper.  
   - **2)** How to maximize efficiency using multi-threading (optimizing the number of threads), but only after resolving the first point.  

3. **Code Presentation**:  
   It would be more beneficial to present the code in the context of test cases rather than a user-friendly pricing interface. This approach would make it easier for developers to understand and extend the framework.

Stay tuned for updates as we work on these improvements! 🛠️

## 📧 Contact

For any inquiries or support, please reach out to us at [devinwym1022@outlook.com](mailto:devinwym1022@outlook.com).

## ⚠️ Copyright
Please do not plagiarize and claim this as your own work. Kindly adhere to the QuantNet/Baruch Pre-MFE Grading Policy. Respect for intellectual property and academic integrity is paramount. Thank you for your understanding and cooperation. 🙏
