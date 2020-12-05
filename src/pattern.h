/**
 * @file Pattern.h
 * @brief pattern class represents a pattern of cards
 * @version 2.0
 * @date 2020-12-04
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <bitset>
#include <initializer_list>
#include <tuple>
#include <compare>

enum class Patterns
{
    None,    //不出牌
    Rocket,  //王炸
    Single,  //单牌
    Couple,  //对子
    Triple,  //3不带
    Triple1, //3带1
    Triple2, //3带2
    Bomb,    //炸弹
    Bomb1,   //4带2个单，或者一对
    Bomb2,   //4带2对
    Seq1,    //顺子
    Seq2,    //连对
    Plane,   //飞机
    Plane1,  //飞机带单
    Plane2   //飞机带对
};

constexpr unsigned int kCardsPerPack = 54UL;

/**
 * @brief class represents card patterns
 * 
 * @tparam CARD_PACKS_N 
 */
template <size_t CARD_PACKS_N>
class Pattern
{
private:
    // use bitset representing cards in such a way that
    // index 0 1 2 3 4 5 6 7... card_i
    // card  3 3 3 3 4 4 4 4... value(card_i) = (card_i / (4 * CARD_PACKS_N)) + 3
    std::bitset<CARD_PACKS_N * kCardsPerPack> pattern_;
    Patterns type_;

public:
    // Construct an empty pattern referring to None
    Pattern(): type_(Patterns::None){}

    // Copy constructor
    Pattern(const Pattern&) = default;

    // Construct a pattern with detailed configuration with designated type without checking
    Pattern(Patterns, std::initializer_list<std::pair<int, int>>);
    
    ~Pattern() = default;

    std::partial_ordering operator<=>(const Pattern&) const;
};