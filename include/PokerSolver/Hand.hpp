#pragma once

#include "Cards.hpp"

#include <set>
#include <memory>

// forward declarations
class Pattern;
class Single;
class Hand : public Cards {
    std::set<std::shared_ptr<Single*>> singles_;
    // contains patterns
public:
    using Cards::Cards;

    Hand play_pattern(const Pattern&) const;
};