#pragma once

#include "Cards.hpp"

#include <compare>

// forward declaration
class Hand;

class Pattern : public Cards {
    friend class Hand;

public:
    using Cards::Cards;
};

// comparison between different type patterns default to unordered
inline std::partial_ordering operator<=>(const Pattern&, const Pattern&) {
    return std::partial_ordering::unordered;
}

// MARK: None
class None : public Pattern {
public:
    None() = default;
};

inline std::partial_ordering operator<=>(const None&, const Pattern&) {
    return std::partial_ordering::less;
}

inline std::partial_ordering operator<=>(const None&, const None&) {
    return std::partial_ordering::equivalent;
}

// MARK: Single
class Single : public Pattern {
public:
    Single(Card card);
    Single(std::vector<Card> cards);

    int power_;
};

inline std::partial_ordering operator<=>(const Single& a, const Single& b) {
    return a.power_ <=> b.power_;
}

// MARK: Double
class Double : public Pattern {
public:
    Double(Card card);
    Double(std::vector<Card> cards);

    int power_;
};

inline std::partial_ordering operator<=>(const Double& a, const Double& b) {
    return a.power_ <=> b.power_;
}

// MARK: Triple
class Triple : public Pattern {
public:
    Triple(Card card);
    Triple(std::vector<Card> cards);

    int power_;
};

inline std::partial_ordering operator<=>(const Triple& a, const Triple& b) {
    return a.power_ <=> b.power_;
}