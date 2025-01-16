/*
 * File: Payoff.cpp
 * Author: Yumin Wu
 * Date: 01/13/2025
 *
 * Description:
 * This file implements the methods defined in the Payoff class hierarchy. It provides the concrete implementations
 * for calculating the payoff of European options, Barrier options, and Asian options. Each class implements
 * the payoff calculation based on the option type, strike price, and other parameters. These implementations
 * are crucial for pricing financial derivatives and simulating their behavior under different market conditions.
 */

#include "Payoff.hpp"

EuropeanCall::EuropeanCall(double K) : K(K) {}

double EuropeanCall::operator()(double S) const
{
    return std::max(S - K, 0.0); // Payoff for European Call: max(S - K, 0)
}

double EuropeanCall::operator()(const std::vector<double>& path) const
{
    return (*this)(path.back()); // Use the last price in the path for payoff calculation
}

EuropeanPut::EuropeanPut(double K) : K(K) {}

double EuropeanPut::operator()(double S) const
{
    return std::max(K - S, 0.0); // Payoff for European Put: max(K - S, 0)
}

double EuropeanPut::operator()(const std::vector<double>& path) const
{
    return (*this)(path.back()); // Use the last price in the path for payoff calculation
}

BarrierOption::BarrierOption(double K, double B, bool isCall, bool isUp, bool isIn)
    : K(K), B(B), isCall(isCall), isUp(isUp), isIn(isIn)
{
}

double BarrierOption::operator()(double S) const
{
    bool isBarrierHit = (isUp) ? (S >= B) : (S <= B); // Check if the barrier is hit

    if (isIn)
    {
        // In barrier: payoff only if barrier is hit
        if (!isBarrierHit)
            return 0.0;
    }
    else
    {
        // Out barrier: payoff only if barrier is not hit
        if (isBarrierHit)
            return 0.0;
    }

    // Calculate payoff based on call/put
    if (isCall)
        return std::max(S - K, 0.0); // Payoff for Barrier Call: max(S - K, 0)
    else
        return std::max(K - S, 0.0); // Payoff for Barrier Put: max(K - S, 0)
}

double BarrierOption::operator()(const std::vector<double>& path) const
{
    return (*this)(path.back()); // Use the last price in the path for payoff calculation
}

AsianOption::AsianOption(double K, bool isCall) : K(K), isCall(isCall) {}

double AsianOption::operator()(double S) const
{
    // For Asian options, a single price is not meaningful; return 0
    return 0.0;
}

double AsianOption::operator()(const std::vector<double>& path) const
{
    // Calculate the geometric average of the price path
    double logSum = 0.0;
    for (double price : path)
    {
        logSum += std::log(price);
    }
    double geometricAverage = std::exp(logSum / path.size());

    if (isCall)
        return std::max(geometricAverage - K, 0.0); // Payoff for Asian Call: max(average - K, 0)
    else
        return std::max(K - geometricAverage, 0.0); // Payoff for Asian Put: max(K - average, 0)
}