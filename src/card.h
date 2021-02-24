/**
 * @file card.h
 * @author Harrison Chen (darkray@126.com)
 * @brief Card class representing single card and collection of cards and dealing with conversion between char/int and cards
 * @version 1.0
 * @date 2020-12-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once

#include <array>
#include <memory>
#include <cmath>
#include <bitset>
#include <stdexcept>
#include <cstddef>
#include <iterator>

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
// Generally, it is supposed to act like a iterable kv container
template <size_t CARD_PACKS_N>
class Cards
{
protected:
    template <size_t val>
    constexpr size_t _most_significant_bit() { return val ? 1 + _most_significant_bit(val >> 1) : -1; }

    // bit length needed to represent a type of card
    static constexpr size_t needed_bit_length_ = _most_significant_bit<4 * CARD_PACKS_N>() + 1U;

    using data_type = std::bitset<needed_bit_length_ * kCardTypesPerPack>;

    // mask bits used as guard bits
    static constexpr data_type guard_bits_mask_ = [] {
        data_type b;
        for (size_t i = needed_bit_length_ - 1ULL; i < b.size(); i += needed_bit_length_)
        {
            b.set(i);
        }
        return b;
    }();

    static constexpr data_type one_card_type_mask_ = data_type((1ULL << needed_bit_length_) - 1ULL);

    data_type data_;

    class proxy
    {
        const size_t offset_;
        const data_type *data_ptr_;

    public:
        proxy(const data_type *data_ptr, size_t index) : data_ptr_(data_ptr), offset_(index * needed_bit_length_) {}

        size_t operator=(size_t num)
        {
            if ((num >> (needed_bit_length_ - 1)) > 0)
            {
                throw std::overflow_error("Card num overflowed.");
            }
            auto new_val = data_type(num) << offset_;
            *data_ptr_ &= !(one_card_type_mask_ << offset_);
            *data_ptr_ |= new_val;
            return num;
        }

        operator size_t() const
        {
            return (((*data_ptr_) >> offset_) & one_card_type_mask_).to_ullong();
        }
    };

    struct iterator
    {
        using iterator_category = std::random_access_iterator_tag;
        using iterator_concept = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = std::pair<Card, size_t>;
        using pointer = std::shared_ptr<std::pair<Card, proxy>>;
        using reference = std::pair<Card, proxy>;

        iterator(data_type *data_ptr, size_t index = 0ULL) : data_ptr_(data_ptr), index_(index) {}

        reference operator*() const { return {Card(index_), proxy(data_ptr_, index_)}; }
        pointer operator->() { return std::move(std::make_shared<std::pair<Card, proxy>>(Card(index_), proxy(data_ptr_, index_))); }
        iterator &operator++()
        {
            index_++;
            return *this;
        }
        iterator operator++(int)
        {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        iterator &operator--()
        {
            index_--;
            return *this;
        }
        iterator operator--(int)
        {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }
        friend bool operator==(const iterator &a, const iterator &b) { return a.index_ == b.index_ && a.data_ptr_ == b.data_ptr_; }
        friend bool operator!=(const iterator &a, const iterator &b) { return a.index_ != b.index_ || a.data_ptr_ != b.data_ptr_; }
        iterator operator+(const difference_type &n) const { return iterator(data_ptr_, index_ + n); }
        iterator &operator+=(const difference_type &n)
        {
            index_ += n;
            return *this;
        }
        iterator operator-(const difference_type &n) const { return iterator(data_ptr_, index_ - n); }
        iterator &operator-=(const difference_type &n)
        {
            index_ -= n;
            return *this;
        }
        bool operator<(const iterator &o) const { return index_ < o.index_; }
        bool operator>(const iterator &o) const { return index_ > o.index_; }
        bool operator<=(const iterator &o) const { return index_ <= o.index_; }
        bool operator>=(const iterator &o) const { return index_ >= o.index_; }
        difference_type operator+(const iterator &o) const { return index_ + o.index_; }
        difference_type operator-(const iterator &o) const { return index_ - o.index_; }

    private:
        size_t index_;
        data_type *data_ptr_;
    };

public:
    Cards() = default;

    // @param pattern_list: {{card_value, num}, ...}
    Cards(std::initializer_list<std::pair<Card, int>> card_list)
    {
        data_type data;
        for (const auto &pair : card_list)
        {
            if ((pair.second >> (needed_bit_length_ - 1)) > 0)
            {
                throw std::overflow_error("Card num overflowed.");
            }
            int offset = static_cast<size_t>(pair.first) * needed_bit_length_;
            auto new_val = data_type(pair.second) << offset;
            data |= new_val;
        }
        data_ = std::move(data);
    }
    ~Cards() = default;

    iterator begin() { return iterator(&data_, 0); }
    iterator end() { return iterator(&data_, kCardTypesPerPack); }
};

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

    // get start index of a card in a bitset
    template <size_t CARD_PACKS_N>
    constexpr size_t bitset_begin(Card card)
    {
        if (card != Card::RedJoker) [[likely]]
        {
            return static_cast<size_t>(card) * 4ULL * CARD_PACKS_N;
        }
        else
        {
            return (static_cast<size_t>(Card::RedJoker) * 4ULL - 3ULL) * CARD_PACKS_N;
        }
    }

    // get end index of a dard in a bitset
    template <size_t CARD_PACKS_N>
    constexpr size_t bitset_end(Card card)
    {
        switch (card)
        {
        case Card::BlackJoker:
            return (static_cast<size_t>(Card::RedJoker) * 4ULL - 3ULL) * CARD_PACKS_N;
        case Card::RedJoker:
            return kCardsPerPack * CARD_PACKS_N;
            [[likely]] default : return (static_cast<size_t>(card) + 1ULL) * 4ULL * CARD_PACKS_N;
        }
    }
} // namespace utils
