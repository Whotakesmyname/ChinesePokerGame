/**
 * @brief Pools include hand pool and pattern pool for reducing memory usage
 **/


#pragma once

#include <memory>
#include <unordered_map>
#include <mutex>
#include <shared_mutex>
#include <concepts>

#include "card.h"


template<template<size_t> typename T, size_t CARD_PACKS_N>
requires std::derived_from<T<CARD_PACKS_N>, Cards<CARD_PACKS_N>>
class Pool
{
public:
    using obj_t = T<CARD_PACKS_N>;
    using ptr_t = std::shared_ptr<obj_t>;

    Pool() = default;

    ptr_t try_get(typename obj_t::data_type bitset) const {
        {
            std::shared_lock read_lock(mutex_);
            if (auto it = map_.find(bitset); it != map_.end()) {
                return it->second;
            }
        }
        return nullptr;
    }

    ptr_t get_or_create(obj_t&& obj, bool try_get_first = true) {
        // check in read mode first
        if (try_get_first)
        {
            std::shared_lock read_lock(mutex_);
            if (auto it = map_.find(obj.get_data()); it != map_.end()) {
                return it->second;
            }
        }
        // not exist, add
        {
            std::scoped_lock write_lock(mutex_);
            if (auto it = map_.find(obj.get_data()); it == map_.end()) {
                ptr_t ptr(new obj_t(obj));
                map_.insert(std::pair(ptr->get_data(), ptr));
                return ptr;
            } else {
                return it->second;
            }
        }
    }
    
private:
    std::unordered_map<typename obj_t::data_type, ptr_t> map_;
    std::shared_mutex mutex_;
};