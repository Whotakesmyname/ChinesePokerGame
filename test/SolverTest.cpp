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

    EXPECT_NO_THROW({
        Single{A}; // dkw can't use () here, otherwise it will call default ctor
        Single({A});
    });

    EXPECT_NO_THROW({
        Double{A}; // dkw can't use () here, otherwise it will call default ctor
        Double({A, A});
    });
}

TEST(PatternTest, ComparePatterns) {
    EXPECT_FALSE(Single(Three) < Double(Four));
    EXPECT_FALSE(Single(Four) > Double(Three));
    EXPECT_EQ(Single(Five) <=> Double(Five), std::partial_ordering::unordered);
}

TEST(PatternTest, CompareNone) {
    EXPECT_TRUE((None() <=> Single(A)) < 0);
    EXPECT_TRUE((Single(RedJoker) <=> None()) > 0);
    EXPECT_TRUE(None() == None());
}

TEST(PatternTest, CompareSingle) {
    EXPECT_TRUE((Single(Four) <=> Single(Five)) < 0);
    EXPECT_TRUE((Single(RedJoker) <=> Single(BlackJoker)) > 0);
    EXPECT_TRUE((Single(BlackJoker) <=> Single(Two)) > 0);
    EXPECT_TRUE((Single(Two) <=> Single(Three)) > 0);
    EXPECT_TRUE((Single(Ten) <=> Single(Ten)) == 0);
    EXPECT_TRUE((Single(A) <=> Single({A})) == 0);
}

TEST(PatternTest, CompareDouble) {
    EXPECT_TRUE((Double(Four) <=> Double(Five)) < 0);
    EXPECT_TRUE((Double(RedJoker) <=> Double(BlackJoker)) > 0);
    EXPECT_TRUE((Double(BlackJoker) <=> Double(Two)) > 0);
    EXPECT_TRUE((Double(Two) <=> Double(Three)) > 0);
    EXPECT_TRUE((Double(Ten) <=> Double(Ten)) == 0);
    EXPECT_TRUE((Double(A) <=> Double({A, A})) == 0);
}