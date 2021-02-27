/**
 * @brief Hand class represents a hand of cards, providing methods resolve all patterns included
 * @date 2021-2-20
 */

#pragma once

#include <functional>
#include <list>
#include <vector>
#include <memory>
#include <cassert>

#include "card.h"
#include "pattern.h"
#include "pool.h"

template <size_t CARD_PACKS_N>
class Hand : public Cards<CARD_PACKS_N>
{
	using PatternPool = Pool<Pattern, CARD_PACKS_N>;
	using PatternPoolPtr = std::shared_ptr<PatternPool>;
	using HandPool = Pool<Hand, CARD_PACKS_N>;
	using HandPoolPtr = std::shared_ptr<HandPool>;

public:
	Hand() : Cards<CARD_PACKS_N>() {}

	Hand(typename Cards<CARD_PACKS_N>::data_type bitset, const PatternPoolPtr &pattern_pool_ptr, const HandPoolPtr &hand_pool_ptr) : Cards<CARD_PACKS_N>(std::move(bitset)), pattern_pool_wptr_(pattern_pool_ptr), hand_pool_wptr_(hand_pool_ptr)
	{
		get_all_patterns();
	}

	Hand(std::vector<std::pair<Card, int>> cards, const PatternPoolPtr &pattern_pool_ptr, const HandPoolPtr &hand_pool_ptr) : Cards<CARD_PACKS_N>(std::move(cards)), pattern_pool_wptr_(pattern_pool_ptr), hand_pool_wptr_(hand_pool_ptr)
	{
		get_all_patterns();
	}

	Hand(const Hand<CARD_PACKS_N>&) = default;

	Hand(Hand<CARD_PACKS_N> &&) = default;

	// get the hand after delete one pattern
	std::shared_ptr<Hand<CARD_PACKS_N>> delete_pattern(const Pattern<CARD_PACKS_N> &pattern_to_delete) const
	{
		auto new_bitset = this->data_ - pattern_to_delete.get_data();
		auto hand_pool_ptr = hand_pool_wptr_.lock();
		assert(hand_pool_ptr);

		// query pool
		if (auto hand_ptr = hand_pool_ptr->try_get(new_bitset)) {
			return hand_ptr;
		}

		//TODO: validate patterns
		return hand_pool_ptr->get_or_create(Hand<CARD_PACKS_N>(new_bitset, pattern_pool_wptr_, hand_pool_ptr));
	}

private:
	// get all included patterns
	int get_all_patterns()
	{
		// ensure pattern pool exists
		auto pool_ptr = pattern_pool_wptr_.lock();
		assert(pool_ptr);
		int count = 0;
		count += get_singles(pool_ptr);
		count += get_couples(pool_ptr);
		count += get_triples(pool_ptr);
		return count;
	}

	// 获取所有单牌组合
	int get_singles(const PatternPoolPtr &pool_ptr)
	{
		int count = 0;
		for (auto it = this->begin(); it != this->end(); ++it)
		{
			if (it->second > 0)
			{
				patterns_.emplace_front(pool_ptr->get_or_create(Pattern<CARD_PACKS_N>({*it})));
				++count;
			}
		}
		return count;
	}

	// 获取所有对子组合
	int get_couples(const PatternPoolPtr &pool_ptr)
	{
		int count = 0;
		for (auto it = this->begin(); it != this->end(); ++it)
		{
			if (it->second > 1)
			{
				patterns_.emplace_front(pool_ptr->get_or_create(Pattern<CARD_PACKS_N>({*it})));
				++count;
			}
		}
		return count;
	}

	// 获取所有三不带组合
	int get_triples(const PatternPoolPtr &pool_ptr)
	{
		int count = 0;
		for (auto it = this->begin(); it != this->end(); ++it)
		{
			if (it->second > 2)
			{
				patterns_.emplace_front(pool_ptr->get_or_create(Pattern<CARD_PACKS_N>({*it})));
				++count;
			}
		}
		return count;
	}
	// int getBombs(const MakeSharedPatternFunc &call_back);	   // 获取所有炸弹组合
	// int getTriple1s(const MakeSharedPatternFunc &call_back); // 获取所有3带1组合
	// int getTriple2s(const MakeSharedPatternFunc &call_back); // 获取所有3带2组合
	// int getBomb1s(const MakeSharedPatternFunc &call_back);   // 获取所有炸弹带1组合
	// int getBomb2s(const MakeSharedPatternFunc &call_back);   // 获取所有炸弹带2组合
	// int getSeq1s(const MakeSharedPatternFunc &call_back);	   // 获取所有顺子组合
	// int getSeq2s(const MakeSharedPatternFunc &call_back);	   // 获取所有连对组合
	// int getPlanes(const MakeSharedPatternFunc &call_back);   // 获取所有飞机组合
	// //vector<Pattern*> getPlane1s(const PatternNotifyFunc& call_back) const;  // 获取所有飞机带单组合
	// //vector<Pattern*> getPlane2s(const PatternNotifyFunc& call_back) const;  // 获取所有飞机带对组合
	// int getRocket(const MakeSharedPatternFunc &call_back); // 王炸
	// int getPass(const MakeSharedPatternFunc &call_back);	 // 不出

	// // 分解长顺子，返回包含自身的所有可能情况
	// int DissolveLongSeq1(const MakeSharedPatternFunc &call_back);

	// // 分解长连对，返回包含自身的所有可能情况
	// int DissolveLongSeq2(const MakeSharedPatternFunc &call_back);

	// // 分解长飞机，返回包含自身的所有可能情况
	// int DissolvePlane(const MakeSharedPatternFunc &call_back);

	std::weak_ptr<PatternPool> pattern_pool_wptr_;
	std::weak_ptr<HandPool> hand_pool_wptr_;
	std::list<std::shared_ptr<Pattern<CARD_PACKS_N>>> patterns_;
};