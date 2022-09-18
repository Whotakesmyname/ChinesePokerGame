#include "Cards.hpp"

#include <cassert>

Cards::Cards(std::vector<Card> cards) {
    uint8_t histogram[16] = {0};
    for (const auto card : cards) {
        assert(card >= 0 && card < 16 && card != 13 && "Invalid card input.");
        assert(histogram[card] < 127 && "Card number for a type overflowed.");
        histogram[card]++;
    }
    cards_ = _mm_loadu_epi8(histogram);
}

bool Cards::contains(const Cards& other) const {
    return !_mm_movemask_epi8(_mm_cmplt_epi8(cards_, other.cards_));
}