#include "State.hpp"

void State::reset() {
    t_ = 0;
    round_ = 0;
    elapsed_time_ = 0;
}

void State::resetRestart(const double &delta_t, const int &step) {
    t_ = delta_t * step;
    round_ = step;
    elapsed_time_ = 0;
}

double State::getT() const {
    return t_;
}

int State::getRound() const {
    return round_;
}

void State::nextRound(double delta_t) {
    t_ += delta_t;
    round_++;
}

void State::recordStartTime() {
    start_time_point_ = std::chrono::steady_clock::now();
    start_time_point_system_ = std::chrono::system_clock::now();

    time_stamp = std::chrono::system_clock::to_time_t(start_time_point_system_);
    std::cout << std::ctime(&time_stamp) << std::endl;
}

void State::measureElapsedTime() {
    std::chrono::steady_clock::time_point current_time_point = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_duration = current_time_point - start_time_point_;
    // elapsed_time_ = elapsed_seconds_duration.count();
    elapsed_time_ = std::chrono::duration_cast<std::chrono::seconds>(elapsed_seconds_duration).count();
}

double State::getElapsedTime() const {
    return elapsed_time_;
}

void State::setElapsedTime(double elapsed_time) {
    elapsed_time_ = elapsed_time;
}
