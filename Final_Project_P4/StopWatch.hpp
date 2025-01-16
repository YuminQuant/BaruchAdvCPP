/*
 * File: StopWatch.hpp
 * Author: Yumin Wu
 * Date: 12/31/2024
 *
 * Description:
 * This file defines the StopWatch class, which provides a simple and high-resolution timer for measuring elapsed time.
 * The class uses the C++11 <chrono> library to track time with high precision. It supports starting, stopping, and resetting
 * the timer, as well as retrieving the elapsed time in seconds. The StopWatch class is designed to be lightweight and
 * easy to use, making it suitable for performance profiling and benchmarking in various applications.
 */
#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <chrono>

class StopWatch
{
private:
    std::chrono::steady_clock::time_point startTime; // The time point when the stopwatch is started
    std::chrono::steady_clock::time_point endTime;   // The time point when the stopwatch is stopped

    // Disable copy constructor and assignment operator to prevent copying
    StopWatch(const StopWatch&) = delete;
    StopWatch& operator=(const StopWatch&) = delete;

public:
    // Constructor to initialize the stopwatch
    StopWatch();

    // Starts the stopwatch
    void StartStopWatch();

    // Stops the stopwatch
    void StopStopWatch();

    // Resets the stopwatch to its initial state
    void Reset();

    // Returns the elapsed time in seconds
    double GetTime() const;
};

#endif // STOPWATCH_HPP