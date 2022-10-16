#include "Pattern.hpp"

#include <cassert>

Single::Single(Card card): Pattern(card), power_(card) {}

Single::Single(std::vector<Card> cards): Pattern(cards.front()), power_(cards.front()) {
    assert(cards.size() == 1 && "Too many cards for pattern Single.");
}

Double::Double(Card card): Pattern({card, card}), power_(card) {}

Double::Double(std::vector<Card> cards): Pattern(cards), power_(cards.front()) {
    assert(cards.size() == 2 && "Too many or less cards for pattern Double.");
    assert(cards.front() == cards.back() && "Double must have two same cards.");
}