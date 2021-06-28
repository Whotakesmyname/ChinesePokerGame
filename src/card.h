/**
 * @brief Card class representing single card and collection of cards and dealing with conversion between char/int and cards
 * @date 2020-12-20
 */

#pragma once

#include <array>
#include <memory>
#include <cmath>
#include <bitset>
#include <stdexcept>
#include <cstddef>
#include <iterator>
#include <vector>

#include "utils.h"

// Card class and underlying size_t indicating index in a pack of cards
enum class Card : size_t
{
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

// Cards is a collection of cards iterable in a kv form
template <size_t CARD_PACKS_N>
class Cards
{
public:
    // cards num per card type
    static constexpr size_t cardsn_per_type_ = 4U * CARD_PACKS_N;
    // bit length needed to represent a type of card
    static constexpr size_t needed_bit_length_ = std::bit_width(cardsn_per_type);

    using data_type = std::bitset<needed_bit_length_ * kCardTypesPerPack>;

    Cards() = default;

    Cards(Cards<CARD_PACKS_N>&&) = default;

    // @param pattern_list: {{card_value, num}, ...}
    Cards(std::vector<std::pair<Card, int>> card_list)
    {
        data_type data;
        unsigned short flag = 0U;
        for (const auto &&pair : card_list)
        {
            if (pair.second > cardsn_per_type_)
            {
                throw std::overflow_error("Card num overflowed.");
            }

            if (pair.second > 0) {
                flag |= 1 << static_cast<size_t>(pair.first);
                int offset = static_cast<size_t>(pair.first) * needed_bit_length_;
                data |= data_type(pair.second) << offset;
            }
        }
        data_ = std::move(data);
        card_flag_ = flag;
    }
    ~Cards() = default;

    bool operator==(const Cards<CARD_PACKS_N>& o) const {
        return data_ == o.data_;
    }

    const data_type& get_data() const {
        return data_;
    }

protected:
    static constexpr data_type one_card_type_mask_ = data_type((1ULL << needed_bit_length_) - 1ULL);  // bit mask to extract one card type

    data_type data_;  // cards number aggregation
    unsigned short card_flag_;  // card type existence flag

    // proxy object to handle midifications of a card's number
    class proxy
    {
        const Cards *obj_ptr_;
        const size_t index_;
        const size_t offset_;

    public:
        proxy(const Cards *obj_ptr, size_t index) : obj_ptr_(obj_ptr), index_(index), offset_(index * needed_bit_length_) {}
        proxy(const proxy&) = delete;
        proxy(proxy&&) = default;

        inline operator size_t() const
        {
            return (((obj_ptr_->data_) >> offset_) & one_card_type_mask_).to_ullong();
        }

        inline size_t operator=(size_t num)
        {
            if (num > cardsn_per_type_)
            {
                throw std::overflow_error("Card num overflowed.");
            }

            if (num > 0) {
                obj_ptr_->card_flag_ |= 1U << index_;
                obj_ptr_->data_ &= ~(one_card_type_mask_ << offset_);
                obj_ptr_->data_ |= data_type(num) << offset_;
            } else {
                obj_ptr_->card_flag_ &= ~(1U << index_);
                obj_ptr_->data_ &= ~(one_card_type_mask_ << offset_);
            }
            return num;
        }

        inline size_t operator+=(size_t num)
        {
            size_t old_v = (((obj_ptr_->data_) >> offset_) & one_card_type_mask_).to_ullong();
            size_t new_v = old_v + num;
            return operator=(new_v);
        }

        inline size_t operator-=(size_t num)
        {
            size_t old_v = (((obj_ptr_->data_) >> offset_) & one_card_type_mask_).to_ullong();
            if (old_v < num) {
                throw std::overflow_error("Card num underflowed.")
            }
            size_t new_v = old_v - num;
            return operator=(new_v);
        }
    };
};

// hash definition
namespace std {
    template<size_t CARD_PACKS_N>
    struct hash<Cards<CARD_PACKS_N>> {
        using obj_t = Cards<CARD_PACKS_N>;
        size_t operator()(const obj_t& obj) const noexcept {
            return hash<typename obj_t::data_type>{}(obj.data_);
        }
    };
}

namespace utils
{
    struct illegal_input : public std::runtime_error
    {
        const char ch_ = 0;
        illegal_input(const char ch) : std::runtime_error("Unrecognized input character"), ch_(ch) {}
        const char *what() const noexcept
        {
            return "Unrecognized input character: " + ch_;
        }
    };

    // convert character to Card
    Card char_to_card(char ch)
    {
        switch (ch)
        {
        case '3':
            return Card::Three;
        case '4':
            return Card::Four;
        case '5':
            return Card::Five;
        case '6':
            return Card::Six;
        case '7':
            return Card::Seven;
        case '8':
            return Card::Eight;
        case '9':
            return Card::Nine;
        case 'o':
            return Card::Ten;
        case 'j':
            return Card::J;
        case 'q':
            return Card::Q;
        case 'k':
            return Card::K;
        case 'a':
            return Card::A;
        case '2':
            return Card::Two;
        case 'y':
            return Card::BlackJoker;
        case 'z':
            return Card::RedJoker;
        default:
            throw illegal_input(ch);
        }
    }

    // convert card to string
    const std::string &card_to_string(Card card)
    {
        static std::array<std::string, kCardTypesPerPack> card_names =
            {"3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A", "2", "Black Joker", "Red Joker"};
        return card_names.at(static_cast<size_t>(card));
    }
} // namespace utils
