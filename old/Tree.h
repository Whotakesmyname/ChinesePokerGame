#pragma once

#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>

#include "Pattern.h"
#include "Hand.h"


class HandPool;

struct Node
{
	short layer;  // 当前层数，地主第一步为1
	const Pattern* move;  // 上一步牌型
	short score;  // 玩家得分。默认0，玩家赢1，玩家输-1 。
	const Hand* lord;
	const Hand* farmer;
	const std::vector<Node*>* children;
	Node* parent;

	~Node() {
		delete this->children;
	}
};

class LumberJack
{
public:
	LumberJack();
	void AddTask(const Node* node);

private:
	std::mutex mutex_;
	std::condition_variable cond_;
	std::queue<const Node*> queue_;
	const Node* pop();
	void Worker();
	static void CutTree(const Node*);
};

class Solution
{
public:
	Solution(LumberJack* lumberJack);
	~Solution();

	std::vector<Node*>* GetNextMoves(Node* node);

	int GetNodeScore(Node* node);

	const Node* CalcWinnableMoves(Hand* lord, Hand* farmer, Pattern* last_move);

private:
	LumberJack* const lumberJack;
	HandPool* const handPool;
	Node* result;
	static void DeleteTree(const Node* root);

};
