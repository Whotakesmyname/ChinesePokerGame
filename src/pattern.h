/**
 * @brief pattern class represents a legal combination of cards
 * @version 2.0
 * @date 2020-12-04
 */

#pragma once

#include <cmath>
#include <vector>
#include <tuple>
#include <compare>
#include <algorithm>
#include <unordered_set>

#include "card.h"
#include "utils.h"

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

/**
 * @brief class represents card patterns
 * 
 * @tparam CARD_PACKS_N numbers of packs of card used. The total card number is 52 * CARD-PACKS_N
 */
template <size_t CARD_PACKS_N>
class Pattern : public Cards<CARD_PACKS_N>
{
private:
    Patterns type_;
    uint32_t power_;
public:
    std::unordered_set<const Pattern* const> larger_patterns_;  // patterns of the opponent larger than this pattern

public:
    // Construct an empty pattern referring to None
    Pattern() : Cards<CARD_PACKS_N>(), type_(Patterns::None), power_(0) {}

    // Copy constructor
    Pattern(const Pattern &) = default;

    // Move constructor
    Pattern(Pattern&&) = default;

    // assignment operator
    Pattern& operator=(const Pattern&) = default;

    // move assignment operator
    Pattern& operator=(Pattern&&) = default;

    // Construct a pattern with detailed configuration with designated type without checking
    // @param pattern_list: {{card_value, num}, ...}
    Pattern(Patterns pattern_type, std::vector<std::pair<Card, int>> pattern_list) : Cards<CARD_PACKS_N>(pattern_list), type_(pattern_type)
    {
        // sort first
        std::sort(pattern_list.begin(), pattern_list.end());
        // decide power
        switch (pattern_type)
        {
        case Patterns::None:
            [[fallthrough]];
        case Patterns::Rocket:
            power_ = 0;
            break;
        case Patterns::Single:
            [[fallthrough]];
        case Patterns::Couple:
            [[fallthrough]];
        case Patterns::Triple:
            [[fallthrough]];
        case Patterns::Bomb:
            // greater when 1st. larger size 2nd. larger value
            power_ = static_cast<uint32_t>((pattern_list.begin()->second << 16) | static_cast<size_t>(pattern_list.begin()->first));
            break;
        case Patterns::Triple1:
            [[fallthrough]];
        case Patterns::Triple2:
            [[fallthrough]];
        case Patterns::Bomb1:
            [[fallthrough]];
        case Patterns::Bomb2:
        {
            int max_freq = 0;
            for (const auto &pair : pattern_list)
            {
                if (pair.second > max_freq)
                {
                    power_ = static_cast<uint32_t>(static_cast<size_t>(pair.first));
                }
            }
            break;
        }
        case Patterns::Seq1:
            [[fallthrough]];
        case Patterns::Seq2:
            // the power number of a sequence is made up by two parts: power & size
            // | power [2, 11] | size [5, 13] |
            // |    2 bytes    |    2 bytes   | <- lowest(righthand) 4 bytes
            {
                size_t largest_card = 0ULL;
                size_t candidate_largest_card = 0ULL;
                for (const auto &pair : pattern_list)
                {
                    if (static_cast<size_t>(pair.first) > largest_card)
                    {
                        if (candidate_largest_card == 0ULL && (pair.first == Card::A || pair.first == Card::Two))
                        {
                            candidate_largest_card = largest_card;
                        }
                        largest_card = static_cast<size_t>(pair.first);
                    }
                }
                if (Card(largest_card) == Card::Two)
                {
                    // special sequences with large card used as small card, e.g. A2345, 23456
                    largest_card = candidate_largest_card;
                }
                power_ = static_cast<uint32_t>((largest_card << 16) | pattern_list.size());
                break;
            }
        case Patterns::Plane:
            [[fallthrough]];
        case Patterns::Plane1:
            [[fallthrough]];
        case Patterns::Plane2:
            {
                uint32_t power = 0U;
                for (const auto& pair : pattern_list) {
                    if (pair.second == 3) {
                        uint32_t t_power = static_cast<uint32_t>(static_cast<size_t>(pair.first));
                        if (t_power > power) {
                            power = t_power;
                        }
                    }
                }
                power_ = power;
                break;
            }
        }
    }

    ~Pattern() = default;

    // compare function
    // partial ordering because patterns are not always comparable
    std::partial_ordering operator<=>(const Pattern& o) const
    {
        if (type_ == o.type_) {
            if (type_ == Patterns::Seq1 || type_ == Patterns::Seq2) {
                constexpr uint32_t lowest_2_bytes_mask = (1U << 16) - 1U;
                if ((power_ & lowest_2_bytes_mask) != (o.power_ & lowest_2_bytes_mask)) {
                    return std::partial_ordering::unordered;
                }
            }
            return power_ <=> o.power_;
        }
        if (type_ == Patterns::Rocket || o.type_ == Patterns::None) {
            return std::partial_ordering::greater;
        }
        if (o.type_ == Patterns::Rocket || type_ == Patterns::None) {
            return std::partial_ordering::less;
        }
        if (type_ == Patterns::Bomb) {
            return std::partial_ordering::greater;
        }
        if (o.type_ == Patterns::Bomb) {
            return std::partial_ordering::less;
        }
        return std::partial_ordering::unordered;
    }

    bool operator==(const Pattern& o) const {
        return (type_ == o.type_ && power_ == o.power_) ? true : false;
    }
};

// hash definition
namespace std {
    template<size_t CARD_PACKS_N>
    struct hash<Pattern<CARD_PACKS_N>> {
        using obj_t = Pattern<CARD_PACKS_N>;
        size_t operator()(const obj_t& obj) const noexcept {
            return hash<typename obj_t::data_type>{}(obj.data_);
        }
    };
}
