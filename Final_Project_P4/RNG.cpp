/*
 * File: RNG.cpp
 * Author: Yumin Wu
 * Date: 01/13/2025
 *
 * Description:
 * This file implements the methods defined in the RNG class hierarchy. It provides the concrete implementation
 * for the MersenneTwister class, which generates random numbers using the Mersenne Twister algorithm.
 * The generate() method returns a random number from a standard normal distribution (mean 0.0, standard deviation 1.0).
 * This implementation is essential for simulations and stochastic processes where high-quality random numbers are required.
 */

#include "RNG.hpp"

MersenneTwister::MersenneTwister(unsigned int seed)
    : generator(seed), distribution(0.0, 1.0) // Initialize the generator with the seed and set up the normal distribution
{
}

double MersenneTwister::generate()
{
    return distribution(generator); // Generate and return a random number from the normal distribution
}