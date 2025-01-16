/*
 * File: FDM.hpp
 * Author: Yumin Wu
 * Date: 01/13/2025
 *
 * Description:
 * This file defines the FDM (Finite Difference Method) class hierarchy for solving Stochastic Differential Equations (SDEs).
 * The FDM class is an abstract base class providing an interface for advancing the solution of an SDE.
 * Three derived classes are implemented: EulerMethod, MilsteinMethod, and DriftAdjustedPredictorCorrector, each providing
 * a specific numerical method for advancing the solution. These methods are commonly used in financial mathematics
 * for simulating asset price paths under stochastic models.
 */

#ifndef FDM_HPP
#define FDM_HPP

#include <memory>
#include <stdexcept>
#include "SDE.hpp"

class FDM
{
public:
    virtual ~FDM() = default;
    virtual double advance(double S, double t, double dt, double dW) = 0; // Advance the solution
};

class EulerMethod : public FDM
{
private:
    std::shared_ptr<SDE> sde; // Shared pointer to the SDE object

public:
    EulerMethod(std::shared_ptr<SDE> sde);
    double advance(double S, double t, double dt, double dW) override; // Implement Euler method
};

class MilsteinMethod : public FDM
{
private:
    std::shared_ptr<SDE> sde; // Shared pointer to the SDE object

public:
    MilsteinMethod(std::shared_ptr<SDE> sde);
    double advance(double S, double t, double dt, double dW) override; // Implement Milstein method
};

class DriftAdjustedPredictorCorrector : public FDM
{
private:
    std::shared_ptr<SDE> sde; // Shared pointer to the SDE object

public:
    DriftAdjustedPredictorCorrector(std::shared_ptr<SDE> sde);
    double advance(double S, double t, double dt, double dW) override; // Implement predictor-corrector method
};

#endif // FDM_HPP