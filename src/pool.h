/**
 * @brief Pools include hand pool and pattern pool for reducing memory usage
 **/


#pragma once

#include <memory>
#include <unordered_map>
#include <mutex>
#include <shared_mutex>
#include <concepts>
#include <utility>

#include "card.h"


template<template<size_t> typename T, size_t CARD_PACKS_N>
requires std::derived_from<T<CARD_PACKS_N>, Cards<CARD_PACKS_N>>
class Pool
{
public:
    using obj_t = T<CARD_PACKS_N>;
    using ptr_t = std::unique_ptr<obj_t>;

    Pool() {
        object_pool_.reserve(kPoolSize);
    }

    template<typename ...Args>
    obj_t* get_or_create(Args&& ...args) {
        obj_t tmp = obj_t(std::forward<Args>(args)...);
        auto it = map_.find(tmp.get_data());
        if (it != map_.end()) {
            return it->second;
        } else {
            obj_t& ele = object_pool_.emplace_back(std::move(tmp));
            map_.emplace(ele.get_data(), &ele);
            return &ele;
        }
    }

    void reset() {
        map_.clear();
        object_pool_ = std::vector<obj_t>();  //TODO: there is excessive deallocation & reallocation
        object_pool_.reserve(kPoolSize);
    }
    
private:
    std::vector<obj_t> object_pool_;
    std::unordered_map<typename obj_t::data_type, obj_t *const> map_;
};