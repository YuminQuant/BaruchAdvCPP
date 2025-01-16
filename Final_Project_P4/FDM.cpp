/*
 * File: FDM.cpp
 * Author: Yumin Wu
 * Date: 01/13/2025
 *
 * Description:
 * This file implements the methods defined in the FDM class hierarchy. It provides the concrete implementations
 * for the Euler, Milstein, and Drift-Adjusted Predictor-Corrector methods for advancing the solution of an SDE.
 * Each method takes the current state of the system (S), time (t), time step (dt), and Wiener process increment (dW)
 * to compute the next state of the system. These methods are essential for numerical simulations in quantitative finance.
 */

#include "FDM.hpp"

EulerMethod::EulerMethod(std::shared_ptr<SDE> sde) : sde(sde)
{
    if (!sde)
    {
        throw std::invalid_argument("SDE pointer is null in EulerMethod constructor.");
    }
}

double EulerMethod::advance(double S, double t, double dt, double dW)
{
    if (dt <= 0)
    {
        throw std::invalid_argument("Time step (dt) must be positive.");
    }
    return S + sde->drift(S, t) * dt + sde->diffusion(S, t) * dW; // Euler method formula
}

MilsteinMethod::MilsteinMethod(std::shared_ptr<SDE> sde) : sde(sde)
{
    if (!sde)
    {
        throw std::invalid_argument("SDE pointer is null in MilsteinMethod constructor.");
    }
}

double MilsteinMethod::advance(double S, double t, double dt, double dW)
{
    if (dt <= 0)
    {
        throw std::invalid_argument("Time step (dt) must be positive.");
    }
    double drift = sde->drift(S, t); // Compute drift term
    double diffusion = sde->diffusion(S, t); // Compute diffusion term
    double diffusionDerivative = (sde->diffusion(S + 1e-5, t) - sde->diffusion(S, t)) / 1e-5; // Approximate derivative of diffusion term

    return S + drift * dt + diffusion * dW + 0.5 * diffusion * diffusionDerivative * (dW * dW - dt); // Milstein method formula
}

DriftAdjustedPredictorCorrector::DriftAdjustedPredictorCorrector(std::shared_ptr<SDE> sde) : sde(sde)
{
    if (!sde)
    {
        throw std::invalid_argument("SDE pointer is null in DriftAdjustedPredictorCorrector constructor.");
    }
}

double DriftAdjustedPredictorCorrector::advance(double S, double t, double dt, double dW)
{
    if (dt <= 0)
    {
        throw std::invalid_argument("Time step (dt) must be positive.");
    }
    double drift = sde->drift(S, t); // Compute drift term
    double diffusion = sde->diffusion(S, t); // Compute diffusion term

    // Predictor step
    double S_predictor = S + drift * dt + diffusion * dW; // Predict the next state

    // Corrector step
    double drift_corrector = sde->drift(S_predictor, t + dt); // Compute drift at predicted state
    double S_corrected = S + 0.5 * (drift + drift_corrector) * dt + diffusion * dW; // Correct the state using average drift

    return S_corrected; // Return the corrected state
}