#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <iomanip>

class Timer {
public:
    struct Step {
        std::string name;
        double duration_ms;
    };

    Timer() : start_time_(std::chrono::steady_clock::now()) {}

    void start_step(const std::string& step_name) {
        auto now = std::chrono::steady_clock::now();
        if (!current_step_name_.empty()) {
            auto end_time = now;
            steps_.emplace_back(Step{ current_step_name_, elapsed_ms(start_time_, end_time) });
        }
        current_step_name_ = step_name;
        start_time_ = now;
    }

    void stop() {
        if (!current_step_name_.empty()) {
            auto end_time = std::chrono::steady_clock::now();
            steps_.emplace_back(Step{ current_step_name_, elapsed_ms(start_time_, end_time) });
            current_step_name_.clear();
        }
    }

    void print() const {
        std::cout << "Timing results:\n";
        for (const auto& step : steps_) {
            std::cout << " - " << std::setw(20) << step.name << ": " << std::fixed << std::setprecision(2) << step.duration_ms << " ms\n";
        }
    }

private:
    static double elapsed_ms(const std::chrono::steady_clock::time_point& start,
        const std::chrono::steady_clock::time_point& end) {
        return std::chrono::duration<double, std::milli>(end - start).count();
    }

    std::chrono::steady_clock::time_point start_time_;
    std::string current_step_name_;
    std::vector<Step> steps_;
};
