#include <gtest/gtest.h>

#include <unordered_set>

#include "Cards.hpp"

TEST(CardsTest, Constructor) {
    EXPECT_NO_THROW({
        Cards();
        Cards({A});
        Cards({A, J, Q});
        Cards({A, A, A});
    });
}

TEST(CardsTest, ContainsAnother) {
    EXPECT_TRUE(Cards({Three, Three}).contains(Cards{{Three}}));
    EXPECT_TRUE(Cards({Three, Four}).contains(Cards{{Three}}));
    EXPECT_TRUE(Cards({Three, Four}).contains(Cards{{Four}}));
    EXPECT_FALSE(Cards({Three}).contains(Cards{{Three, Three}}));
}

TEST(CardsTest, HashFunction) {
    EXPECT_TRUE(Cards({Three, Four}).hash() == Cards({Four, Three}).hash());
    EXPECT_NO_THROW({
        std::unordered_set<Cards> set;
        set.emplace(std::vector{J, Q, K});
    });
}

TEST(CardsTest, EqualityOp) {
    EXPECT_TRUE(Cards({J, Q, K}) == Cards({K, J, Q}));
    EXPECT_FALSE(Cards({Three, Five}) == Cards({Five, Four}));
}