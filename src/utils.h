/**
 * @brief Utilities
 * @version 1.0
 * @date 2020-12-20
 */

#pragma once

constexpr unsigned int kCardsPerPack = 54UL;
constexpr unsigned int kCardTypesPerPack = 15UL;

namespace utils {
    template <size_t val>
    constexpr size_t most_significant_bit() { return val ? 1 + most_significant_bit<(val >> 1)>() : -1; }
}