/*
 * File: SDE.hpp
 * Author: Yumin Wu
 * Date: 01/13/2025
 *
 * Description:
 * This file defines the SDE (Stochastic Differential Equation) class hierarchy for modeling various stochastic processes.
 * The SDE class is an abstract base class providing an interface for the drift and diffusion terms of an SDE.
 * Three derived classes are implemented: GBM (Geometric Brownian Motion), CEV (Constant Elasticity of Variance), and CIR (Cox-Ingersoll-Ross).
 * These classes are commonly used in financial mathematics to model asset prices, interest rates, and other stochastic processes.
 */

#ifndef SDE_HPP
#define SDE_HPP

#include <memory>
#include <cmath>

class SDE
{
public:
    virtual ~SDE() = default;
    virtual double drift(double S, double t) = 0; // Drift term of the SDE
    virtual double diffusion(double S, double t) = 0; // Diffusion term of the SDE
};

class GBM : public SDE
{
private:
    double mu; // Drift coefficient (expected return rate)
    double sigma; // Volatility (standard deviation of returns)

public:
    GBM(double mu, double sigma); // Constructor for Geometric Brownian Motion
    double drift(double S, double t) override; // Compute the drift term
    double diffusion(double S, double t) override; // Compute the diffusion term
};

class CEV : public SDE
{
private:
    double mu; // Drift coefficient
    double sigma; // Volatility
    double gamma; // Elasticity parameter (controls the relationship between price and volatility)

public:
    CEV(double mu, double sigma, double gamma); // Constructor for Constant Elasticity of Variance model
    double drift(double S, double t) override; // Compute the drift term
    double diffusion(double S, double t) override; // Compute the diffusion term
};

class CIR : public SDE
{
private:
    double kappa; // Mean reversion rate (speed of reversion to the long-term mean)
    double theta; // Long-term mean (equilibrium level)
    double sigma; // Volatility

public:
    CIR(double kappa, double theta, double sigma); // Constructor for Cox-Ingersoll-Ross model
    double drift(double S, double t) override; // Compute the drift term
    double diffusion(double S, double t) override; // Compute the diffusion term
};

#endif // SDE_HPP