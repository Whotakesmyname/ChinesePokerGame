/**
 * @file chinese_poker_game_solver.cpp
 * @author Harrison Chen (darkray@126.com)
 * @brief A fast Chinese Poker Game solver
 * @version 1.1
 * @date 2020-12-04
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "pattern.h"
#include "hand.h"
#include "pool.h"
#include "utils.h"

// 牌副数, 每副54张
constexpr size_t CARD_PACKS_N = 1;

// a solver instance contains all necessary information to solve a game
class Solver {
    using hand_t = Hand<CARD_PACKS_N>;
    using pattern_t = Pattern<CARD_PACKS_N>;
};

int main(int argc, char const *argv[])
{
    Pattern<CARD_PACKS_N> p;
    return 0;
}
