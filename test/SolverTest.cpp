#include <gtest/gtest.h>

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