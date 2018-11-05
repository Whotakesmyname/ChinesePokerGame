// ChinesePokerGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"

#ifndef NDEBUG
#define NDEBUG
#endif // !NDEBUG


#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <chrono>
#include <ctype.h>

#include "Pattern.h"
#include "Hand.h"
#include "utils.h"
#include "Tree.h"


std::unordered_map<char, int> Cards = {
	{'3', 3},
	{'4', 4},
	{'5', 5},
	{'6', 6},
	{'7', 7},
	{'8', 8},
	{'9', 9},
	{'O', 10},  // 10 使用O代替
	{'J', 11},
	{'Q', 12},
	{'K', 13},
	{'A', 14},
	{'2', 16},
	{'Y', 17},  // 小王
	{'Z', 18}   // 大王
};


Hand* GetInputHand(PatternPool* const patternPool) {
	std::string line;
	std::getline(std::cin, line);
	std::istringstream iss(line);
	char buffer = 0;
	Hand* newhand = new Hand(patternPool);
	while (iss >> buffer) {
		buffer = toupper(buffer);
		auto it = Cards.find(buffer);
		if (it != Cards.end()) {
			newhand->Insert(it->second);
		}
	}
	return newhand;
}

std::vector<int> GetInputVector() {
	std::string line;
	std::getline(std::cin, line);
	std::istringstream iss(line);
	char buffer = 0;
	std::vector<int> result;
	while (iss >> buffer) {
		buffer = toupper(buffer);
		auto it = Cards.find(buffer);
		if (it != Cards.end()) {
			result.push_back(it->second);
		}
	}
	std::sort(result.begin(), result.end());
	return result;
}

int main()
{
	// Create int2Card unordered map
	std::unordered_map<int, char> int2Card;
	for (auto const& kv : Cards) {
		int2Card[kv.second] = kv.first;
	}
	LumberJack* lumberJack = new LumberJack();

Start:
	{
		PatternPool* const patternPool = new PatternPool();
		Hand* lord;
		Hand* farmer;
		std::cin.clear();
		std::cin.sync();
		std::cout << "======================\n双人对战斗地主残局。地主先出。\n"
			<< "【Warning】暂不支持飞机带翅膀。\n"
			<< "请输入地主手牌，如OJQKAE(10、J、Q、K、A)\n"
			<< "【Info】10使用英文字母O代替，小王Y，大王Z；回车结束输入：" << std::endl;
		lord = GetInputHand(patternPool);

		std::cout << "请输入农民手牌，如OJQKAE(10、J、Q、K、A)\n"
			<< "【Info】10使用英文字母O代替，小王Y，大王Z；回车结束输入：" << std::endl;
		farmer = GetInputHand(patternPool);

		std::cout << "计算中...\n";
		auto t1 = std::chrono::steady_clock::now();
		Solution solution(lumberJack);
		const Node* root = solution.CalcWinnableMoves(lord, farmer);
		auto t2 = std::chrono::steady_clock::now();
		std::cout << "【Info】计算完成！共花费"
			<< double(std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den
			<< "秒\n";

		if (root->score == -1) {
			std::cout << "【Info】地主无必胜策略\n";
			goto Start;
		}

		std::vector<char> _charvec;
		for (int _v : root->children->at(0)->move->cards) {
			_charvec.push_back(int2Card[_v]);
		}
		std::cout << "【Info】地主必胜\n"
			<< "请出" << _charvec << "\n";
		_charvec.clear();

		const Node* node = root->children->at(0);
		while (node->children != nullptr) {
			std::cout << "请输入对方出牌：";
			std::vector<int> _draw = GetInputVector();
			for (auto child : *node->children) {
				if (child->move->cards == _draw) {
					node = child->children->at(0);
					// Turn int to char for human reading
					for (int _v : node->move->cards) {
						_charvec.push_back(int2Card[_v]);
					}
					std::cout << "请出" << _charvec << "\n";
					_charvec.clear();
					goto for_break;
				}
			}
			std::cout << "【Error】对方无法这样出，请重新输入。\n";
		for_break:
			continue;
		}
		std::cout << "【Info】正在清理上一局生成的对抗决策树等内存数据，请稍等...\n";
		delete patternPool;
	}
	goto Start;  // Repeat solution
	return 0;
}