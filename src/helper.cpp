#include "helper.hpp"

#include <random>

uint8_t get_random(uint8_t upper_limit) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, upper_limit - 1);
    return static_cast<uint8_t>(dist(mt));
}