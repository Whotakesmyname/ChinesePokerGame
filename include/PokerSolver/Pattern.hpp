#pragma once

#include "Cards.hpp"

#include <compare>

class Pattern : public Cards {
public:
    using Cards::Cards;
};

// comparison between different type patterns default to unordered
inline std::partial_ordering operator<=>(const Pattern&, const Pattern&) {
    return std::partial_ordering::unordered;
}

// mark: None
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

// mark: Single
class Single : public Pattern {

};

// mark: Double
class Double : public Pattern {

};