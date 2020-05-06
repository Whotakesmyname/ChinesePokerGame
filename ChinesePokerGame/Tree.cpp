#include "pch.h"
#include "Tree.h"

#include <iostream>
#include <thread>
#include <future>

Solution::Solution(LumberJack* lumberJack): handPool(new HandPool()), result(nullptr), lumberJack(lumberJack)
{
}

Solution::~Solution()
{
	this->lumberJack->AddTask(this->result);
	delete this->handPool;
}

std::vector<Node*>* Solution::GetNextMoves(Node * node)
{
	std::vector<Node*>* result = new std::vector<Node*>;
	if ((node->layer & 1) == 1) {  // Calc farmer's move
		auto _result = node->farmer->getAllSolutions(node->move);
		for (const Pattern* pattern : _result) {
			const Hand* _nextHand = this->handPool->Delete(node->farmer, pattern);
			Node* _child = new Node{ node->layer + 1, pattern, 0, node->lord, _nextHand, nullptr, node};
			if (_nextHand->IsEmpty()) {  // Lose
				_child->score = -1;
				for (auto _p : *result) {
					delete _p;
				}
				delete result;
				return new std::vector<Node*>{_child};  // 当某一步可以出空，则理性决策必走这步
			}
			result->push_back(_child);
		}
	}
	else {  // Calc lord's move
		auto _result = node->lord->getAllSolutions(node->move);
		for (const Pattern* pattern : _result) {
			const Hand* _nextHand = this->handPool->Delete(node->lord, pattern);
			Node* _child = new Node{ node->layer + 1, pattern, 0, _nextHand, node->farmer, nullptr, node};
			if (_nextHand->IsEmpty()) {  // Win
				_child->score = 1;
				for (auto _p : *result) {
					delete _p;
				}
				delete result;
				return new std::vector<Node*>{_child};
			}
			result->push_back(_child);
		}
	}
	return result;
}

int Solution::GetNodeScore(Node * node)
{
	//std::cout << "Dealing with layer " << node->layer << "...\r" << std::flush;
	if (node->score != 0) return node->score;
	int _score = 0;
	std::vector<Node*>* _children = this->GetNextMoves(node);
	if ((node->layer & 1) == 1) {  // Farmer's turn
		_score = 1;
		// 并行实现第二步（农民步骤）
		if (node->layer == 1) {
			std::vector<std::future<int>> futures;
			for (Node* _child : *_children) {
				futures.emplace_back(std::async(&Solution::GetNodeScore, this, _child));
			}
			for (auto _it = futures.begin(); _it != futures.end();_it++) {
				int _v = (*_it).get();
				if (_v < 0) {
					_score = _v;
					break;
				}
			}
		}
		else {
			for (Node* _child : *_children) {
				int __score = GetNodeScore(_child);
				if (__score < 0) {
					_score = __score;
					break;  // 农民/对方未必做理性决策（事实上在必胜策略下对方应该不做决策)因此不予剪枝
				}
			}
		}
	}
	else
	{
		_score = -1;
		auto it_child = _children->begin();
		while (it_child != _children->end()) {  // 剪枝。只留下最先发现的必胜子树。
			int __score = GetNodeScore(*it_child);
			if (__score > 0) {
				_score = __score;
				it_child++;
				while (it_child != _children->end()) {
					this->lumberJack->AddTask(*it_child);
					it_child = _children->erase(it_child);
				}
				break;
			}
			else {
				this->lumberJack->AddTask(*it_child);
				it_child = _children->erase(it_child);
			}
		}
	}
	node->score = _score;
	delete node->children;  // Maybe needless but whatever, for safety
	node->children = _children;
	return _score;
}

// 计算结果
const Node* Solution::CalcWinnableMoves(Hand * lord, Hand * farmer, Pattern* last_move)
{
	Node* root = new Node{ 0, last_move, 0, lord, farmer, nullptr, nullptr};
	this->GetNodeScore(root);
	this->result = root;
	return root;
}

void Solution::DeleteTree(const Node * root)
{
	if (root->children != nullptr) {
		for (auto node : *root->children) {
			Solution::DeleteTree(node);
		}
	}
	delete root;
}

LumberJack::LumberJack()
{
	std::thread(&LumberJack::Worker, this).detach();
}

void LumberJack::AddTask(const Node * node)
{
	std::unique_lock<std::mutex> mlock(this->mutex_);
	queue_.push(node);
	mlock.unlock();
	cond_.notify_one();
}

const Node * LumberJack::pop()
{
	std::unique_lock<std::mutex> mlock(this->mutex_);
	while (this->queue_.empty())
	{
		cond_.wait(mlock);
	}
	auto node = queue_.front();
	queue_.pop();
	return node;
}

void LumberJack::Worker()
{
	const Node* node = nullptr;
	while(true) {
		node = this->pop();
		this->CutTree(node);
	}
}

void LumberJack::CutTree(const Node * node)
{
	if (node->children != nullptr) {
		for (auto node : *node->children) {
			LumberJack::CutTree(node);
		}
	}
	delete node;
}
