#include "Hand.hpp"

#include "Pattern.hpp"

#include <cassert>

Hand Hand::play_pattern(const Pattern& pattern) const {
    assert(contains(pattern) && "We don't have this pattern to play.");

    Hand new_hand(*this);
    new_hand.cards_ = _mm_sub_epi8(new_hand.cards_, pattern.cards_);
    // TODO: delete invalid patterns
}