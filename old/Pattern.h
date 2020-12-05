#pragma once

#include <vector>
#include <unordered_map>
#include <shared_mutex>

#include "utils.h"


enum class Patterns
{
	Rocket,//王炸
	Single,//单牌
	Couple,//对子
	Triple,//3不带
	Bomb,//炸弹
	Triple1,//3带1
	Triple2,//3带2
	Bomb1,//4带2个单，或者一对
	Bomb2,//4带2对
	Seq1,//顺子
	Seq2,//连对
	Plane,//飞机
	Plane1,//飞机带单
	Plane2,//飞机带对
	None//不出牌
};

class Pattern {
public:
	double power;  // 牌力
	std::vector<int> cards;  // 组成牌
	Patterns type;  // 牌型
	int size;  // 细分牌型（顺子、连对长度）

	Pattern(Patterns type, std::vector<int> cards);
	Pattern(Patterns type, std::vector<int>cards, double power);

	bool operator==(const Pattern& other);
	bool operator>(const Pattern& other);
};

class PatternPool {
public:
	PatternPool();
	Pattern* const GetPattern(Patterns type, std::vector<int> cards);
	Pattern* const GetPattern(Patterns type, std::vector<int> cards, int power);
private:
	std::unordered_map < std::vector<int>, Pattern* const, container_hash<std::vector<int>>>* const patternPool;
	mutable std::shared_mutex _mutex;
};