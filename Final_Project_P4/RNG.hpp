/*
 * File: RNG.hpp
 * Author: Yumin Wu
 * Date: 01/13/2025
 *
 * Description:
 * This file defines the RNG (Random Number Generator) class hierarchy for generating random numbers.
 * The RNG class is an abstract base class providing an interface for generating random numbers.
 * The MersenneTwister class is a derived class that implements the Mersenne Twister algorithm, a widely used
 * pseudorandom number generator known for its high-quality random numbers and long period.
 * This class is particularly useful in simulations, Monte Carlo methods, and other applications requiring
 * high-quality random numbers.
 */

#ifndef RNG_HPP
#define RNG_HPP

#include <memory>
#include <random>

class RNG
{
public:
    virtual ~RNG() = default;
    virtual double generate() = 0; // Generate a random number
};

class MersenneTwister : public RNG
{
private:
    std::mt19937 generator; // Mersenne Twister random number generator
    std::normal_distribution<double> distribution; // Normal distribution with mean 0.0 and standard deviation 1.0

public:
    MersenneTwister(unsigned int seed = std::random_device{}()); // Constructor with optional seed
    double generate() override; // Generate a random number from the normal distribution
};

#endif // RNG_HPP