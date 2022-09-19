#pragma once

#include <immintrin.h>
#include <vector>
#include <concepts>
#include <functional>

#include "Card.hpp"

/**
 * Cards are represented as a 128-bit integer. With 8 bits for each type of card,
 * we have 16 slots enough to hold 15 card types.
 *  
 * #0 - #12 slots are used for 3, 4, ..., Q, K, A, 2; #14 & #15 slot are used for Black Joker and Red Joker respectively.
 * #13 slot is reserved for convenience.
 */
class Cards {
    friend bool operator==(const Cards&, const Cards&);

protected:
    // a collection of cards
    __m128i cards_;

public:
    Cards() = default;
    Cards(const Cards&) = default;
    Cards(Cards&&) = default;
    Cards(std::vector<Card> cards); // init with a vector of cards

    /**
     * @brief Check if contains another collection of cards
     * 
     * @param other another Cards instance
     * @return contains or not 
     */
    bool contains(const Cards& other) const;

    /**
     * @brief hash function combines 4 lower bits of each byte
     * 
     * @return std::size_t hash result
     */
    std::size_t hash() const noexcept;
};

namespace std {
// add hash function for Cards and its derived classes
template<typename T>
requires derived_from<T, Cards>
struct hash<T> {
    size_t operator()(const T& cards) const noexcept {
        return cards.hash();
    }
};
}

// add equality compare function for convenience for simd type
inline bool operator==(const Cards& lhs, const Cards& rhs) {
    __m128i neq = _mm_xor_si128(lhs.cards_, rhs.cards_);
    return _mm_test_all_zeros(neq, neq);
}