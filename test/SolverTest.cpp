#include <gtest/gtest.h>

#include <unordered_set>

#include "Cards.hpp"
#include "Pattern.hpp"

// mark: Cards
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

// mark: Pattern
TEST(PatternTest, Constructor) {
    EXPECT_NO_THROW({
        Pattern();
        Pattern({A});
        Pattern({A, J, Q});
    });
}

TEST(PatternTest, ComparePatterns) {
    EXPECT_FALSE(Single() < Double());
    EXPECT_FALSE(Single() > Double());
    EXPECT_EQ(Single() <=> Double(), std::partial_ordering::unordered);
}

TEST(PatternTest, CompareNone) {
    EXPECT_TRUE((None() <=> Single()) < 0);
    EXPECT_TRUE((Single() <=> None()) > 0);
    EXPECT_TRUE(None() == None());
}