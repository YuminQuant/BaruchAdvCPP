/*
 * File: StopWatch.cpp
 * Author: Yumin Wu
 * Date: 12/31/2024
 *
 * Description:
 * This file implements the StopWatch class, which provides functionality for measuring elapsed time with high precision.
 * The class uses the C++11 <chrono> library to track time and supports starting, stopping, resetting the timer, and
 * retrieving the elapsed time in seconds. The implementation ensures that the timer is lightweight and efficient,
 * making it suitable for performance profiling and benchmarking in various applications.
 */
#include "StopWatch.hpp"

 // Constructor to initialize the stopwatch
StopWatch::StopWatch()
    : startTime(std::chrono::steady_clock::time_point::min()),
    endTime(std::chrono::steady_clock::time_point::min())
{
}

// Starts the stopwatch by recording the current time
void StopWatch::StartStopWatch()
{
    startTime = std::chrono::steady_clock::now();
    endTime = std::chrono::steady_clock::time_point::min(); // Reset end time
}

// Stops the stopwatch by recording the current time
void StopWatch::StopStopWatch()
{
    endTime = std::chrono::steady_clock::now();
}

// Resets the stopwatch to its initial state
void StopWatch::Reset()
{
    startTime = std::chrono::steady_clock::time_point::min();
    endTime = std::chrono::steady_clock::time_point::min();
}

// Returns the elapsed time in seconds
double StopWatch::GetTime() const
{
    // If the stopwatch was not properly started or stopped, return 0
    if (startTime == std::chrono::steady_clock::time_point::min() ||
        endTime == std::chrono::steady_clock::time_point::min())
    {
        return 0.0;
    }
    // Calculate the duration between start and end time
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime);
    return duration.count(); // Return the duration in seconds
}