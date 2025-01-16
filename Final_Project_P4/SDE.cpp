/*
 * File: SDE.cpp
 * Author: Yumin Wu
 * Date: 01/13/2025
 *
 * Description:
 * This file implements the methods defined in the SDE class hierarchy. It provides the concrete implementations
 * for the GBM, CEV, and CIR models, which are widely used in financial modeling. Each class computes the drift
 * and diffusion terms of the corresponding stochastic differential equation, which are essential for simulating
 * stochastic processes such as asset prices and interest rates.
 */

#include "SDE.hpp"

GBM::GBM(double mu, double sigma) : mu(mu), sigma(sigma) {}

double GBM::drift(double S, double t)
{
    return mu * S; // Drift term for Geometric Brownian Motion: mu * S
}

double GBM::diffusion(double S, double t)
{
    return sigma * S; // Diffusion term for Geometric Brownian Motion: sigma * S
}

CEV::CEV(double mu, double sigma, double gamma) : mu(mu), sigma(sigma), gamma(gamma) {}

double CEV::drift(double S, double t)
{
    return mu * S; // Drift term for Constant Elasticity of Variance model: mu * S
}

double CEV::diffusion(double S, double t)
{
    return sigma * std::pow(S, gamma); // Diffusion term for CEV model: sigma * S^gamma
}

CIR::CIR(double kappa, double theta, double sigma) : kappa(kappa), theta(theta), sigma(sigma) {}

double CIR::drift(double S, double t)
{
    return kappa * (theta - S); // Drift term for Cox-Ingersoll-Ross model: kappa * (theta - S)
}

double CIR::diffusion(double S, double t)
{
    return sigma * std::sqrt(S); // Diffusion term for CIR model: sigma * sqrt(S)
}