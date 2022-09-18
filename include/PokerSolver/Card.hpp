#pragma once

#include <stdint.h>

// Use unscoped enum for implicit conversion
enum Card {
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    J,
    Q,
    K,
    A,
    Two,
    BlackJoker = 14,
    RedJoker,
};