#include "Cards.hpp"

#include <cassert>

Cards::Cards(std::vector<Card> cards) {
    uint8_t histogram[16] = {0};
    for (const auto card : cards) {
        assert(card >= 0 && card < 16 && card != 13 && "Invalid card input.");
        assert(histogram[card] < 127 && "Card number for a type overflowed.");
        histogram[card]++;
    }
    static_assert(sizeof(histogram) == 16u); // ensure same size as m128i
    cards_ = _mm_loadu_si128((__m128i *)histogram);
}

bool Cards::contains(const Cards& other) const {
    __m128i neq = _mm_cmplt_epi8(cards_, other.cards_);
    return _mm_test_all_zeros(neq, neq);
}