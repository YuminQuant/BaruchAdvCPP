/*
 * File: SimulationBuilder.cpp
 * Author: Yumin Wu
 * Date: 01/13/2025
 *
 * Description:
 * This file implements the SimulationBuilder class, which is responsible for constructing and configuring
 * the components required for a Monte Carlo simulation. The class provides methods to select and configure
 * the SDE, FDM, RNG, and Payoff components, as well as the initial conditions for the simulation. It also
 * includes an interactive user configuration method that prompts the user to input the necessary parameters
 * and select the desired components. The build method finalizes the configuration and returns a tuple
 * containing all the components and initial conditions needed to run the simulation.
 */

#include "SimulationBuilder.hpp"

SimulationBuilder::SimulationBuilder()
    : S0(0.0), T(0.0), N(0), M(0) // Initialize initial conditions to default values
{
}

SimulationBuilder& SimulationBuilder::setSDE(std::shared_ptr<SDE> s)
{
    if (!s)
    {
        throw std::invalid_argument("SDE pointer is null.");
    }
    sde = s; // Set the SDE model
    return *this;
}

SimulationBuilder& SimulationBuilder::setFDM(std::shared_ptr<FDM> f)
{
    if (!f)
    {
        throw std::invalid_argument("FDM pointer is null.");
    }
    fdm = f; // Set the FDM scheme
    return *this;
}

SimulationBuilder& SimulationBuilder::setRNG(std::shared_ptr<RNG> r)
{
    if (!r)
    {
        throw std::invalid_argument("RNG pointer is null.");
    }
    rng = r; // Set the RNG
    return *this;
}

SimulationBuilder& SimulationBuilder::setPayoff(std::shared_ptr<Payoff> p)
{
    if (!p)
    {
        throw std::invalid_argument("Payoff pointer is null.");
    }
    payoff = p; // Set the Payoff function
    return *this;
}

SimulationBuilder& SimulationBuilder::setInitialCondition(double s0, double t, int n, int m)
{
    if (s0 <= 0 || t <= 0 || n <= 0 || m <= 0)
    {
        throw std::invalid_argument("Initial conditions (S0, T, N, M) must be positive.");
    }
    S0 = s0; // Set initial stock price
    T = t;   // Set maturity
    N = n;   // Set number of time steps
    M = m;   // Set number of simulations
    return *this;
}

std::shared_ptr<SDE> SimulationBuilder::selectSDE()
{
    int choice;
    std::cout << "Select SDE Model:\n";
    std::cout << "1. GBM\n2. CEV\n3. CIR\n";
    std::cin >> choice;

    if (std::cin.fail())
    {
        std::cin.clear(); // Clear error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
        throw std::invalid_argument("Invalid input. Please enter a number.");
    }

    switch (choice)
    {
    case 1:
        return std::make_shared<GBM>(0.05, 0.2); // Create GBM model with default parameters
    case 2:
        return std::make_shared<CEV>(0.05, 0.2, 0.5); // Create CEV model with default parameters
    case 3:
        return std::make_shared<CIR>(0.1, 0.2, 0.3); // Create CIR model with default parameters
    default:
        std::cout << "Invalid choice. Please select again.\n";
        return selectSDE(); // Recursively prompt for valid input
    }
}

std::shared_ptr<FDM> SimulationBuilder::selectFDM(std::shared_ptr<SDE> sde)
{
    if (!sde)
    {
        throw std::invalid_argument("SDE pointer is null in selectFDM.");
    }

    int choice;
    std::cout << "Select FDM Scheme:\n";
    std::cout << "1. EulerMethod\n2. MilsteinMethod\n3. DriftAdjustedPredictorCorrector\n";
    std::cin >> choice;

    if (std::cin.fail())
    {
        std::cin.clear(); // Clear error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
        throw std::invalid_argument("Invalid input. Please enter a number.");
    }

    switch (choice)
    {
    case 1:
        return std::make_shared<EulerMethod>(sde); // Create Euler method
    case 2:
        return std::make_shared<MilsteinMethod>(sde); // Create Milstein method
    case 3:
        return std::make_shared<DriftAdjustedPredictorCorrector>(sde); // Create Drift-Adjusted Predictor-Corrector method
    default:
        std::cout << "Invalid choice. Please select again.\n";
        return selectFDM(sde); // Recursively prompt for valid input
    }
}

std::shared_ptr<RNG> SimulationBuilder::selectRNG()
{
    int choice;
    std::cout << "Select RNG:\n";
    std::cout << "1. MersenneTwister\n";
    std::cin >> choice;

    if (std::cin.fail())
    {
        std::cin.clear(); // Clear error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
        throw std::invalid_argument("Invalid input. Please enter a number.");
    }

    switch (choice)
    {
    case 1:
        return std::make_shared<MersenneTwister>(); // Create Mersenne Twister RNG
    default:
        std::cout << "Invalid choice. Please select again.\n";
        return selectRNG(); // Recursively prompt for valid input
    }
}

std::shared_ptr<Payoff> SimulationBuilder::selectPayoff()
{
    int choice;
    std::cout << "Select Payoff Type:\n";
    std::cout << "1. European Call\n";
    std::cout << "2. European Put\n";
    std::cout << "3. Asian Call\n";
    std::cout << "4. Asian Put\n";
    std::cout << "5. Up-and-In Call\n";
    std::cout << "6. Up-and-In Put\n";
    std::cout << "7. Up-and-Out Call\n";
    std::cout << "8. Up-and-Out Put\n";
    std::cout << "9. Down-and-In Call\n";
    std::cout << "10. Down-and-In Put\n";
    std::cout << "11. Down-and-Out Call\n";
    std::cout << "12. Down-and-Out Put\n";
    std::cin >> choice;

    if (std::cin.fail())
    {
        std::cin.clear(); // Clear error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
        throw std::invalid_argument("Invalid input. Please enter a number.");
    }

    double K = getStrikePrice(); // Get strike price from user
    double B = 0.0; // Barrier level (only used for barrier options)
    bool isCall = false; // Flag for call/put
    bool isUp = false; // Flag for up/down barrier
    bool isIn = false; // Flag for in/out barrier

    switch (choice)
    {
    case 1:
        return std::make_shared<EuropeanCall>(K); // Create European Call payoff
    case 2:
        return std::make_shared<EuropeanPut>(K); // Create European Put payoff
    case 3:
        return std::make_shared<AsianOption>(K, true); // Create Asian Call payoff
    case 4:
        return std::make_shared<AsianOption>(K, false); // Create Asian Put payoff
    case 5:
        B = getBarrierLevel(); // Get barrier level for barrier options
        isCall = true;
        isUp = true;
        isIn = true;
        return std::make_shared<BarrierOption>(K, B, isCall, isUp, isIn); // Create Up-and-In Call payoff
    case 6:
        B = getBarrierLevel();
        isCall = false;
        isUp = true;
        isIn = true;
        return std::make_shared<BarrierOption>(K, B, isCall, isUp, isIn); // Create Up-and-In Put payoff
    case 7:
        B = getBarrierLevel();
        isCall = true;
        isUp = true;
        isIn = false;
        return std::make_shared<BarrierOption>(K, B, isCall, isUp, isIn); // Create Up-and-Out Call payoff
    case 8:
        B = getBarrierLevel();
        isCall = false;
        isUp = true;
        isIn = false;
        return std::make_shared<BarrierOption>(K, B, isCall, isUp, isIn); // Create Up-and-Out Put payoff
    case 9:
        B = getBarrierLevel();
        isCall = true;
        isUp = false;
        isIn = true;
        return std::make_shared<BarrierOption>(K, B, isCall, isUp, isIn); // Create Down-and-In Call payoff
    case 10:
        B = getBarrierLevel();
        isCall = false;
        isUp = false;
        isIn = true;
        return std::make_shared<BarrierOption>(K, B, isCall, isUp, isIn); // Create Down-and-In Put payoff
    case 11:
        B = getBarrierLevel();
        isCall = true;
        isUp = false;
        isIn = false;
        return std::make_shared<BarrierOption>(K, B, isCall, isUp, isIn); // Create Down-and-Out Call payoff
    case 12:
        B = getBarrierLevel();
        isCall = false;
        isUp = false;
        isIn = false;
        return std::make_shared<BarrierOption>(K, B, isCall, isUp, isIn); // Create Down-and-Out Put payoff
    default:
        std::cout << "Invalid choice. Please select again.\n";
        return selectPayoff(); // Recursively prompt for valid input
    }
}

double SimulationBuilder::getStrikePrice()
{
    double K;
    std::cout << "Enter strike price (K): ";
    std::cin >> K;

    if (std::cin.fail() || K <= 0)
    {
        std::cin.clear(); // Clear error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
        throw std::invalid_argument("Invalid strike price. Please enter a positive number.");
    }

    return K; // Return the strike price
}

double SimulationBuilder::getBarrierLevel()
{
    double B;
    std::cout << "Enter barrier level (B): ";
    std::cin >> B;

    if (std::cin.fail() || B <= 0)
    {
        std::cin.clear(); // Clear error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
        throw std::invalid_argument("Invalid barrier level. Please enter a positive number.");
    }

    return B; // Return the barrier level
}

SimulationBuilder& SimulationBuilder::configureFromUser()
{
    try
    {
        // Prompt for initial conditions
        std::cout << "Enter initial stock price (S0): ";
        std::cin >> S0;
        std::cout << "Enter maturity (T): ";
        std::cin >> T;
        std::cout << "Enter number of time steps (N): ";
        std::cin >> N;
        std::cout << "Enter number of simulations (M): ";
        std::cin >> M;

        if (S0 <= 0 || T <= 0 || N <= 0 || M <= 0)
        {
            throw std::invalid_argument("Initial conditions (S0, T, N, M) must be positive.");
        }

        // Select components
        sde = selectSDE(); // Select SDE model
        fdm = selectFDM(sde); // Select FDM scheme
        rng = selectRNG(); // Select RNG
        payoff = selectPayoff(); // Select Payoff function
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error during configuration: " << e.what() << std::endl;
        throw; // Re-throw the exception
    }

    return *this; // Return the configured builder
}

std::tuple<std::shared_ptr<SDE>, std::shared_ptr<FDM>, std::shared_ptr<RNG>, std::shared_ptr<Payoff>, double, double, int, int> SimulationBuilder::build() const
{
    if (!sde || !fdm || !rng || !payoff)
    {
        throw std::runtime_error("One or more components (SDE, FDM, RNG, Payoff) are not set.");
    }
    if (S0 <= 0 || T <= 0 || N <= 0 || M <= 0)
    {
        throw std::runtime_error("Initial conditions (S0, T, N, M) must be positive.");
    }
    return std::make_tuple(sde, fdm, rng, payoff, S0, T, N, M); // Return the simulation configuration
}