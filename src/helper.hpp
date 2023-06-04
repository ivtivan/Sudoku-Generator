#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <random>

uint8_t get_random(uint8_t upper_limit) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1, upper_limit);
    return static_cast<uint8_t>(dist(mt));
}

#endif