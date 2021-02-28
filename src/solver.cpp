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
#include "thread_pool.h"

// 牌副数, 每副54张
constexpr size_t CARD_PACKS_N = 1;

// a solver instance contains all necessary information to solve a game
class Solver {
    using hand_t = Hand<CARD_PACKS_N>;
    using pattern_t = Pattern<CARD_PACKS_N>;

    struct Node
    {
        int layer;
        std::shared_ptr<pattern_t> last_move;
        signed char score;
        std::shared_ptr<hand_t> lord_hand;
        std::shared_ptr<hand_t> farmer_hand;
        std::list<std::unique_ptr<Node>> children;
    };
    using NodePtr = std::unique_ptr<Node>;

public:
    Solver(std::vector<Card>&& lord, std::vector<Card>&& farmer) {
        hand_t lord_hand = hand_t()
    }
    
private:
    std::vector<std::pair<Card, int>> parse_cards(std::vector<Card>&& cards) const {
        
    }

    NodePtr root_;
    Pool<Hand, CARD_PACKS_N> hand_pool_;
    Pool<Pattern, CARD_PACKS_N> pattern_pool_;
    inline static ThreadPool thread_pool_ = ThreadPool(std::thread::hardware_concurrency() - 1);
};

int main(int argc, char const *argv[])
{
    Pattern<CARD_PACKS_N> p;
    return 0;
}
