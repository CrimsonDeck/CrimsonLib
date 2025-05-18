#ifndef CrimsonLib
#define CrimsonLib

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <limits>


// print function


void print() {
    std::cout << std::endl;
}

template <typename T, typename... Args>
void print(const T& first, const Args&... rest) {
    std::cout << first;
    print(rest...);
}


// read function


template <typename T>
void read(T& value) {
    std::cin >> value;
}


// forever function


inline void forever(const std::function<void()>& action) {
    while (true) {
        action();
    }
}


// wait function


void wait(int seconds) {
    if (seconds == 0) {
        std::this_thread::sleep_for(std::chrono::hours(std::numeric_limits<int>::max()));
    } else if (seconds > 0) {
        std::this_thread::sleep_for(std::chrono::seconds(seconds));
    }
}


// timers


class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
    std::string name;

public:

    Timer(const std::string& timerName = "") : name(timerName) {
        start();
    }

    void start() {
        start_time = std::chrono::high_resolution_clock::now();
        end_time = start_time;
    }

    void stop() {
        end_time = std::chrono::high_resolution_clock::now();
    }

    // Get the elapsed time in nanoseconds
    long long elapsed_nanoseconds() const {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
    }

    // Get the elapsed time in microseconds
    long long elapsed_microseconds() const {
        return std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    }

    long long elapsed_milliseconds() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    }

    double elapsed_seconds() const {
        std::chrono::duration<double> elapsed = end_time - start_time;
        return elapsed.count();
    }

    void printElapsedTime(const std::string& message = "") const {
        auto duration = end_time - start_time;
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        std::cout << (name.empty() ? "" : name + ": ") << message << milliseconds << " ms" << std::endl;
    }

    ~Timer() {
        stop();
        if (!name.empty()) {
            printElapsedTime("Timer '" + name + "' finished in: ");
        }
    }
};



#endif
