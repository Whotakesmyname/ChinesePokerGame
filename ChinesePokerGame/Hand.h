#pragma once
#include "pch.h"

#include <map>
#include <vector>
#include <shared_mutex>

#include "Pattern.h"


class Hand {
public:
	Hand();
	Hand(const Hand & other);
	Hand(PatternPool* const patternPool);

	std::map<int, int> Cards;  // 手牌

	Hand& Insert(int card);  // 插入新牌
	Hand* Delete(int card, int n) const;  // 删除某几张牌并返回之后的手牌
	Hand* Delete(std::vector<int> card, std::vector<int> n) const;
	Hand* Delete(const Pattern& pattern) const;
	std::vector<Pattern*> getAllSolutions() const;  // 获取所有可能出牌组合
	std::vector<Pattern*> getAllSolutions(const Pattern* pattern) const;  // 获取下一步所有可能出牌组合

	bool IsEmpty() const;

private:
	PatternPool* const patternPool;
	std::vector<Pattern*> getSingles(const Pattern* pattern) const;  // 获取所有单牌组合
	std::vector<Pattern*> getCouples(const Pattern* pattern) const;  // 获取所有对子组合
	std::vector<Pattern*> getTriples(const Pattern* pattern) const;  // 获取所有三不带组合
	std::vector<Pattern*> getBombs(const Pattern* pattern) const;  // 获取所有炸弹组合
	std::vector<Pattern*> getTriple1s(const Pattern* pattern) const;  // 获取所有3带1组合
	std::vector<Pattern*> getTriple2s(const Pattern* pattern) const;  // 获取所有3带2组合
	std::vector<Pattern*> getBomb1s(const Pattern* pattern) const;  // 获取所有炸弹带1组合
	std::vector<Pattern*> getBomb2s(const Pattern* pattern) const;  // 获取所有炸弹带2组合
	std::vector<Pattern*> getSeq1s(const Pattern* pattern) const;  // 获取所有顺子组合
	std::vector<Pattern*> getSeq2s(const Pattern* pattern) const;  // 获取所有连对组合
	std::vector<Pattern*> getPlanes(const Pattern* pattern) const;  // 获取所有飞机组合
	//vector<Pattern*> getPlane1s(const Pattern* pattern) const;  // 获取所有飞机带单组合
	//vector<Pattern*> getPlane2s(const Pattern* pattern) const;  // 获取所有飞机带对组合
	std::vector<Pattern*> getRocket(const Pattern* pattern) const;  // 王炸
	std::vector<Pattern*> getPass(const Pattern* pattern) const;  // 不出

	// 分解长顺子，返回包含自身的所有可能情况
	std::vector<Pattern*> DissolveLongSeq1(Pattern* pattern) const;

	// 分解长连对，返回包含自身的所有可能情况
	std::vector<Pattern*> DissolveLongSeq2(Pattern* pattern) const;

	// 分解长飞机，返回包含自身的所有可能情况
	std::vector<Pattern*> DissolvePlane(Pattern* pattern) const;
};

class HandPool {
public:
	HandPool();
	~HandPool()
	{
		delete this->handPool;
	}
	const Hand* Delete(const Hand*, const Pattern*);
private:
	std::unordered_map<std::vector<uint8_t>, Hand*, container_hash<std::vector<uint8_t>>>* const handPool;
	std::shared_mutex _mutex;
};
