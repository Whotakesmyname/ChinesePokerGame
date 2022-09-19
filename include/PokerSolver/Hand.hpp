#pragma once

#include "Pattern.hpp"

#include <set>
#include <memory>

class Hand : public Cards {
    std::set<std::shared_ptr<Single*>> singles_;
    // contains patterns
public:
    using Cards::Cards;
};