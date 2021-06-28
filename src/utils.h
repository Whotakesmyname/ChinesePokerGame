/**
 * @brief Utilities
 * @version 1.0
 * @date 2020-12-20
 */

#pragma once

#include <bitset>
#include <bit>

constexpr unsigned int kCardsPerPack = 54UL;
constexpr unsigned int kCardTypesPerPack = 15UL;
constexpr size_t kPoolSize = 256UL;

namespace utils {
    template <size_t val>
    constexpr size_t most_significant_bit() { return val ? 1 + most_significant_bit<(val >> 1)>() : -1; }

    template<size_t N>
    size_t countr_zero(std::bitset<N> bitset) {
        size_t count = 0UL;
        for (size_t i = 0UL; i < bitset.size(); ++i) {
            if (bitset.test(i)) {
                return count;
            }
            ++count;
        }
        return count;
    }
}