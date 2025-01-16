/*
 * File: Payoff.hpp
 * Author: Yumin Wu
 * Date: 01/13/2025
 *
 * Description:
 * This file defines the Payoff class hierarchy for calculating the payoff of various financial options.
 * The Payoff class is an abstract base class providing an interface for calculating the payoff of both
 * standard and path-dependent options. Derived classes include EuropeanCall, EuropeanPut, BarrierOption,
 * and AsianOption, each implementing specific payoff calculations for different types of options.
 * These classes are essential for pricing and simulating financial derivatives in quantitative finance.
 */

#ifndef PAYOFF_HPP
#define PAYOFF_HPP

#include <memory>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>

class Payoff
{
public:
    virtual ~Payoff() = default;
    virtual double operator()(double S) const = 0; // Payoff function for standard options (single price)
    virtual double operator()(const std::vector<double>& path) const = 0; // Payoff function for path-dependent options (price path)
};

class EuropeanCall : public Payoff
{
private:
    double K; // Strike price

public:
    EuropeanCall(double K); // Constructor for European Call option
    double operator()(double S) const override; // Payoff for a single price
    double operator()(const std::vector<double>& path) const override; // Payoff for a price path
};

class EuropeanPut : public Payoff
{
private:
    double K; // Strike price

public:
    EuropeanPut(double K); // Constructor for European Put option
    double operator()(double S) const override; // Payoff for a single price
    double operator()(const std::vector<double>& path) const override; // Payoff for a price path
};

class BarrierOption : public Payoff
{
private:
    double K; // Strike price
    double B; // Barrier level
    bool isCall; // True for call option, false for put option
    bool isUp; // True for up barrier, false for down barrier
    bool isIn; // True for in barrier, false for out barrier

public:
    BarrierOption(double K, double B, bool isCall, bool isUp, bool isIn); // Constructor for Barrier option
    double operator()(double S) const override; // Payoff for a single price
    double operator()(const std::vector<double>& path) const override; // Payoff for a price path
};

class AsianOption : public Payoff
{
private:
    double K; // Strike price
    bool isCall; // True for call option, false for put option

public:
    AsianOption(double K, bool isCall); // Constructor for Asian option
    double operator()(double S) const override; // Payoff for a single price (not applicable for Asian options)
    double operator()(const std::vector<double>& path) const override; // Payoff for a price path
};

#endif // PAYOFF_HPP