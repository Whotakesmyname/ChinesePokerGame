/**
 * @file card.h
 * @author Harrison Chen (darkray@126.com)
 * @brief Card class representing single cards and dealing with conversion between char/int and cards
 * @version 1.0
 * @date 2020-12-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <array>
#include <memory>

#include "utils.h"

// Card class and underlying size_t indicating index in a pack of cards
enum class Card: size_t {
    Three = 0,
    Four = 1,
    Five = 2,
    Six = 3,
    Seven = 4,
    Eight = 5,
    Nine = 6,
    Ten = 7,
    J = 8,
    Q = 9,
    K = 10,
    A = 11,
    Two = 12,
    BlackJoker = 13,
    RedJoker = 14
};

namespace utils {
    struct illegal_input: public std::runtime_error {
        const char ch_;
        illegal_input(const char ch):std::runtime_error("Unrecognized input character"), ch_(ch) {}
        const char* what() const noexcept {
            return "Unrecognized input character: " + ch_;
        }
    };

    // convert character to Card
    Card char_to_card(char ch) {
        switch (ch)
        {
        case '3': return Card::Three;
        case '4': return Card::Four;
        case '5': return Card::Five;
        case '6': return Card::Six;
        case '7': return Card::Seven;
        case '8': return Card::Eight;
        case '9': return Card::Nine;
        case 'o': return Card::Ten;
        case 'j': return Card::J;
        case 'q': return Card::Q;
        case 'k': return Card::K;
        case 'a': return Card::A;
        case '2': return Card::Two;
        case 'y': return Card::BlackJoker;
        case 'z': return Card::RedJoker;
        default: throw illegal_input(ch);
        }
    }

    // convert card to string
    const std::string& card_to_string(Card card) {
        static std::array<std::string, kCardTypesPerPack> card_names =
            {"3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A", "2", "Black Joker", "Red Joker"};
        return card_names.at(static_cast<size_t>(card));
    }

    // get start index of a card in a bitset
    template<size_t CARD_PACKS_N>
    constexpr size_t bitset_begin(Card card) {
        if (card != Card::RedJoker) [[likely]] {
            return static_cast<size_t>(card) * 4ULL * CARD_PACKS_N;
        } else {
            return (static_cast<size_t>(Card::RedJoker) * 4ULL - 3ULL) * CARD_PACKS_N;
        }
    }

    // get end index of a dard in a bitset
    template<size_t CARD_PACKS_N>
    constexpr size_t bitset_end(Card card) {
        switch (card)
        {
        case Card::BlackJoker:
            return (static_cast<size_t>(Card::RedJoker) * 4ULL - 3ULL) * CARD_PACKS_N;
        case Card::RedJoker:
            return kCardsPerPack * CARD_PACKS_N;
        [[likely]] default:
            return (static_cast<size_t>(card) + 1ULL) * 4ULL * CARD_PACKS_N;
        }
    }
}
