#pragma once

#include <immintrin.h>
#include <vector>

#include "Card.hpp"

/**
 * Cards are represented as a 128-bit integer. With 8 bits for each type of card,
 * we have 16 slots enough to hold 15 card types.
 *  
 * #0 - #12 slots are used for 3, 4, ..., Q, K, A, 2; #14 & #15 slot are used for Black Joker and Red Joker respectively.
 * #13 slot is reserved for convenience.
 */
class Cards {
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
};