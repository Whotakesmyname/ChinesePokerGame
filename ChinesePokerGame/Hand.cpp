#include "pch.h"
#include "Hand.h"


#include <assert.h>
#include <numeric>
#include <algorithm>

#include "utils.h"

Hand::Hand() : patternPool(new PatternPool())
{
}

Hand::Hand(const Hand& other) : patternPool(other.patternPool)
{
	this->Cards = std::map<int, int>(other.Cards);
}

Hand::Hand(PatternPool* const patternPool) : patternPool(patternPool)
{
}

Hand& Hand::Insert(int card)
{
	if (this->Cards.find(card) == this->Cards.end()) {
		this->Cards[card] = 1;
	}
	else
	{
		this->Cards[card] ++;
	}
	return *this;
}

Hand* Hand::Delete(int card, int n = 1) const
{
	// WE TRUST CALLER'S ARGU ARE LEGAL
	Hand* _Hand = new Hand(*this);
	_Hand->Cards[card] -= n;
	if (_Hand->Cards[card] == 0) {
		_Hand->Cards.erase(card);
	}
	return _Hand;
}

Hand* Hand::Delete(std::vector<int> card, std::vector<int> n) const
{
	Hand* _hand = new Hand(*this);
	for (int i = 0; i < card.size(); i++) {
		_hand->Cards[card[i]] -= n[i];
		if (_hand->Cards[card[i]] == 0) {
			_hand->Cards.erase(card[i]);
		}
	}
	return _hand;
}

Hand* Hand::Delete(const Pattern& pattern) const
{
	Hand* _hand = new Hand(*this);
	for (int card : pattern.cards) {
		_hand->Cards[card]--;
		if (_hand->Cards[card] == 0) {
			_hand->Cards.erase(card);
		}
	}
	return _hand;
}

std::vector<Pattern*> Hand::getAllSolutions(const Pattern* pattern) const
{
	std::vector<Pattern*> result;
	switch (pattern->type)
	{
	case Patterns::None:
		InsertResultVector<std::vector<Pattern*>>(result, this->getPlanes(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getSeq2s(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getSeq1s(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getTriple2s(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getTriple1s(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getTriples(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getBombs(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getRocket(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getBomb1s(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getBomb2s(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getCouples(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getSingles(pattern));
		break;
	case Patterns::Single:
		InsertResultVector<std::vector<Pattern*>>(result, this->getRocket(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getBombs(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getSingles(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getPass(pattern));
		break;
	case Patterns::Couple:
		InsertResultVector<std::vector<Pattern*>>(result, this->getRocket(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getBombs(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getCouples(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getPass(pattern));
		break;
	case Patterns::Triple:
		InsertResultVector<std::vector<Pattern*>>(result, this->getRocket(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getBombs(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getTriples(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getPass(pattern));
		break;
	case Patterns::Triple1:
		InsertResultVector<std::vector<Pattern*>>(result, this->getRocket(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getBombs(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getTriple1s(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getPass(pattern));
		break;
	case Patterns::Triple2:
		InsertResultVector<std::vector<Pattern*>>(result, this->getRocket(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getBombs(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getTriple2s(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getPass(pattern));
		break;
	case Patterns::Bomb1:
		InsertResultVector<std::vector<Pattern*>>(result, this->getRocket(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getBombs(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getBomb1s(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getPass(pattern));
		break;
	case Patterns::Bomb2:
		InsertResultVector<std::vector<Pattern*>>(result, this->getRocket(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getBombs(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getBomb2s(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getPass(pattern));
		break;
	case Patterns::Seq1:
		InsertResultVector<std::vector<Pattern*>>(result, this->getRocket(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getBombs(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getSeq1s(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getPass(pattern));
		break;
	case Patterns::Seq2:
		InsertResultVector<std::vector<Pattern*>>(result, this->getRocket(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getBombs(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getSeq2s(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getPass(pattern));
		break;
	case Patterns::Plane:
		InsertResultVector<std::vector<Pattern*>>(result, this->getRocket(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getBombs(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getPlanes(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getPass(pattern));
		break;
	case Patterns::Bomb:
		InsertResultVector<std::vector<Pattern*>>(result, this->getRocket(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getBombs(pattern));
		InsertResultVector<std::vector<Pattern*>>(result, this->getPass(pattern));
		break;
	case Patterns::Rocket:
		InsertResultVector<std::vector<Pattern*>>(result, this->getPass(pattern));
		break;
	}
	return result;
}

bool Hand::IsEmpty() const
{
	if (this->Cards.size() == 0) return true;
	return false;
}

std::vector<Pattern*> Hand::getAllSolutions() const
{
	std::vector<Pattern*> result;
	auto pattern = this->patternPool->GetPattern(Patterns::None, std::vector<int>(), 0);
	InsertResultVector<std::vector<Pattern*>>(result, this->getPlanes(pattern));
	InsertResultVector<std::vector<Pattern*>>(result, this->getSeq2s(pattern));
	InsertResultVector<std::vector<Pattern*>>(result, this->getSeq1s(pattern));
	InsertResultVector<std::vector<Pattern*>>(result, this->getTriple2s(pattern));
	InsertResultVector<std::vector<Pattern*>>(result, this->getTriple1s(pattern));
	InsertResultVector<std::vector<Pattern*>>(result, this->getTriples(pattern));
	InsertResultVector<std::vector<Pattern*>>(result, this->getBombs(pattern));
	InsertResultVector<std::vector<Pattern*>>(result, this->getBomb1s(pattern));
	InsertResultVector<std::vector<Pattern*>>(result, this->getBomb2s(pattern));
	InsertResultVector<std::vector<Pattern*>>(result, this->getCouples(pattern));
	InsertResultVector<std::vector<Pattern*>>(result, this->getSingles(pattern));
	return result;
}

std::vector<Pattern*> Hand::getSingles(const Pattern* pattern) const
{
	std::vector<Pattern*> result;
	auto it = this->Cards.begin();
	while (it != this->Cards.end() && it->first <= pattern->power) {
		it++;
	}
	while (it != this->Cards.end()) {
		result.push_back(this->patternPool->GetPattern(Patterns::Single, std::vector<int>{it->first}, it->first));
		it++;
	}
	return result;
}

std::vector<Pattern*> Hand::getCouples(const Pattern* pattern) const
{
	std::vector<Pattern*> result;
	for (auto& kv : this->Cards) {
		if (kv.second >= 2 && kv.first > pattern->power) {
			result.push_back(this->patternPool->GetPattern(Patterns::Couple, std::vector<int>(2, kv.first)));
		}
	}
	return result;
}

std::vector<Pattern*> Hand::getTriples(const Pattern* pattern) const
{
	std::vector<Pattern*> result;
	for (auto& kv : this->Cards) {
		if (kv.second >= 3 && kv.first > pattern->power) {
			result.push_back(this->patternPool->GetPattern(Patterns::Couple, std::vector<int>(3, kv.first)));
		}
	}
	return result;
}

std::vector<Pattern*> Hand::getBombs(const Pattern* pattern) const
{
	std::vector<Pattern*> result;
	for (auto& kv : this->Cards) {
		// when the previous hand is another bomb with a greater than or equal power, this bomb is not legal
		if (kv.second >= 4 && !((pattern->type == Patterns::Bomb) && (kv.first <= pattern->power))) {
			result.push_back(this->patternPool->GetPattern(Patterns::Couple, std::vector<int>(4, kv.first)));
		}
	}
	return result;
}

std::vector<Pattern*> Hand::getTriple1s(const Pattern* pattern) const
{
	std::vector<Pattern*> result;
	for (auto& kv : this->Cards) {
		if (kv.second >= 3 && kv.first > pattern->power) {
			for (auto& _kv : this->Cards) {
				if (_kv.first != kv.first) {
					result.push_back(this->patternPool->GetPattern(Patterns::Triple1, std::vector<int>{kv.first, kv.first, kv.first, _kv.first}, kv.first));
				}
			}
		}
	}
	return result;
}

std::vector<Pattern*> Hand::getTriple2s(const Pattern* pattern) const
{
	std::vector<Pattern*> result;
	for (auto& kv : this->Cards) {
		if (kv.second >= 3 && kv.first > pattern->power) {
			for (auto& _kv : this->Cards) {
				if (_kv.second >= 2 && _kv.first != kv.first) {
					result.push_back(this->patternPool->GetPattern(Patterns::Triple2, std::vector<int>{kv.first, kv.first, kv.first, _kv.first, _kv.first}, kv.first));
				}
			}
		}
	}
	return result;
}

std::vector<Pattern*> Hand::getBomb1s(const Pattern* pattern) const
{
	std::vector<Pattern*> result;
	for (auto& kv4 : this->Cards) {
		if (kv4.second >= 4 && kv4.first > pattern->power) {
			for (auto it1 = this->Cards.cbegin(); it1 != this->Cards.cend(); it1++) {
				if (it1->first == kv4.first) {
					continue;
				}
				for (auto it2 = it1; it2 != this->Cards.cend(); it2++) {
					if (it2->first == kv4.first) {
						continue;
					}
					if (it1 == it2 && it2->second < 2) {
						continue;
					}
					result.push_back(this->patternPool->GetPattern(Patterns::Bomb1, std::vector<int>{kv4.first, kv4.first, kv4.first, kv4.first, it1->first, it2->first}, kv4.first));
				}
			}
		}
	}
	return result;
}

std::vector<Pattern*> Hand::getBomb2s(const Pattern* pattern) const
{
	std::vector<Pattern*> result;
	for (auto& kv4 : this->Cards) {
		if (kv4.second >= 4 && kv4.first > pattern->power) {
			for (auto it1 = this->Cards.cbegin(); it1 != this->Cards.cend(); it1++) {
				if (it1->second < 2) continue;
				if (it1->first == kv4.first) continue;
				for (auto it2 = it1; it2 != this->Cards.cend(); it2++) {
					if (it2->second < 2) continue;
					if (it2->first == kv4.first) continue;
					if (it2 == it1 && it2->second < 4) continue;
					result.push_back(this->patternPool->GetPattern(Patterns::Bomb2, std::vector<int>{kv4.first, kv4.first, kv4.first, kv4.first, it1->first, it1->first, it2->first, it2->first}, kv4.first));
				}
			}
		}
	}
	return result;
}

std::vector<Pattern*> Hand::getSeq1s(const Pattern* pattern) const
{
	std::vector<Pattern*> result;
	int prev = 0;
	int count = 0;
	// 对应顺子牌型时，简化算法
	if (pattern->type == Patterns::Seq1) {
		for (auto it = this->Cards.begin(); it != this->Cards.end(); it++) {
			if (it->first - prev == 1) {
				count++;
			}
			else {
				count = 1;
			}
			if (count >= pattern->size && it->first > pattern->power) {
				std::vector<int> _vec(pattern->size);
				std::iota(_vec.begin(), _vec.end(), it->first - pattern->size + 1);
				result.push_back(this->patternPool->GetPattern(Patterns::Seq1, _vec, it->first));
			}
			prev = it->first;
		}
		return result;
	}

	// 上手PASS时求最长顺子导出全部size顺子
	for (auto& kv : this->Cards) {
		if (kv.first - prev == 1) {
			count++;
			prev = kv.first;
		}
		else {
			if (count >= 5) {
				std::vector<int> vec(count);
				std::iota(vec.begin(), vec.end(), prev - count + 1);
				auto _result = DissolveLongSeq1(this->patternPool->GetPattern(Patterns::Seq1, vec, prev));
				result.insert(result.end(), _result.begin(), _result.end());
				count = 1;
				prev = kv.first;
			}
			else {
				prev = kv.first;
				count = 1;
			}
		}
	}
	if (count >= 5) {
		std::vector<int> vec(count);
		iota(vec.begin(), vec.end(), prev - count + 1);
		auto _result = DissolveLongSeq1(this->patternPool->GetPattern(Patterns::Seq1, vec, prev));
		result.insert(result.end(), _result.begin(), _result.end());
	}
	return result;
}

std::vector<Pattern*> Hand::getSeq2s(const Pattern* pattern) const
{
	std::vector<Pattern*> result;
	int prev = 0;
	int count = 0;
	// 对应连对牌型时，简化算法
	if (pattern->type == Patterns::Seq2) {
		int length = pattern->size >> 1;
		for (auto it = this->Cards.begin(); it != this->Cards.end(); it++) {
			if (it->first - prev == 1 && it->second >= 2) {
				count++;
			}
			else {
				count = 1;
			}
			if (count >= length && it->first > pattern->power&& it->second >= 2) {
				std::vector<int> _vec(pattern->size);
				for (int i = 0; i < length; i++) {
					_vec[2 * i] = prev - length + 1 + i;
					_vec[2 * i + 1] = prev - length + 1 + i;
				}
				result.push_back(this->patternPool->GetPattern(Patterns::Seq2, _vec, it->first));
			}
			prev = it->first;
		}
		return result;
	}

	for (auto& kv : this->Cards) {
		if (((kv.first - prev) == 1) && (kv.second >= 2)) {
			count++;
			prev = kv.first;
		}
		else {
			if (count >= 3) {
				std::vector<int> vec(count * 2);
				for (int i = 0; i < count; i++) {
					vec[2 * i] = prev - count + 1 + i;
					vec[2 * i + 1] = prev - count + 1 + i;
				}
				auto _result = DissolveLongSeq2(this->patternPool->GetPattern(Patterns::Seq2, vec, prev));
				result.insert(result.end(), _result.begin(), _result.end());
				count = 1;
				if (kv.second < 2) continue;
				prev = kv.first;
			}
			else {
				count = 1;
				if (kv.second < 2) continue;
				prev = kv.first;
			}
		}
	}
	if (count >= 3) {
		std::vector<int> vec(count * 2);
		for (int i = 0; i < count; i++) {
			vec[2 * i] = prev - count + 1 + i;
			vec[2 * i + 1] = prev - count + 1 + i;
		}
		auto _result = DissolveLongSeq2(this->patternPool->GetPattern(Patterns::Seq2, vec, prev));
		result.insert(result.end(), _result.begin(), _result.end());
	}
	return result;
}

std::vector<Pattern*> Hand::getPlanes(const Pattern* pattern) const
{
	std::vector<Pattern*> result;
	int prev = 0;
	int count = 0;
	// 对应飞机牌型时，简化算法
	if (pattern->type == Patterns::Plane) {
		int length = pattern->size / 3;
		for (auto it = this->Cards.begin(); it != this->Cards.end(); it++) {
			if (it->first - prev == 1 && it->second >= 3) {
				count++;
			}
			else {
				count = 1;
			}
			if (count >= length && it->first > pattern->power&& it->second >= 3) {
				std::vector<int> _vec(pattern->size);
				for (int i = 0; i < length; i++) {
					_vec[3 * i] = prev - length + 1 + i;
					_vec[3 * i + 1] = prev - length + 1 + i;
					_vec[3 * i + 2] = prev - length + 1 + i;
				}
				result.push_back(this->patternPool->GetPattern(Patterns::Plane, _vec, it->first));
			}
			prev = it->first;
		}
		return result;
	}

	for (auto it = this->Cards.begin(); it != this->Cards.end(); it++) {
		if (((it->first - prev) == 1) && (it->second >= 3)) {
			count++;
			prev = it->first;
		}
		else {
			if (count >= 2) {
				std::vector<int> vec(count * 3);
				for (int i = 0; i < count; i++) {
					vec[3 * i] = prev - count + 1 + i;
					vec[3 * i + 1] = prev - count + 1 + i;
					vec[3 * i + 2] = prev - count + 1 + i;
				}
				auto _result = DissolvePlane(this->patternPool->GetPattern(Patterns::Plane, vec, prev));
				result.insert(result.end(), _result.begin(), _result.end());
				count = 1;
				if (it->second < 3) continue;
				prev = it->first;
			}
			else {
				count = 1;
				if (it->second < 3) continue;
				prev = it->first;
			}
		}
	}
	if (count >= 2) {
		std::vector<int> vec(count * 3);
		for (int i = 0; i < count; i++) {
			vec[3 * i] = prev - count + 1 + i;
			vec[3 * i + 1] = prev - count + 1 + i;
			vec[3 * i + 2] = prev - count + 1 + i;
		}
		auto _result = DissolvePlane(this->patternPool->GetPattern(Patterns::Plane, vec, prev));
		result.insert(result.end(), _result.begin(), _result.end());
	}
	return result;
}

std::vector<Pattern*> Hand::getRocket(const Pattern* pattern) const
{
	if (this->Cards.count(LITTLE_JOKER) > 0 && this->Cards.count(JOKER) > 0) {
		return std::vector<Pattern*>{this->patternPool->GetPattern(Patterns::Rocket, std::vector<int>{LITTLE_JOKER, JOKER}, 99)};
	}
	return std::vector<Pattern*>();
}

std::vector<Pattern*> Hand::getPass(const Pattern* pattern) const
{
	return std::vector<Pattern*>{this->patternPool->GetPattern(Patterns::None, std::vector<int>(), 0)};
}

std::vector<Pattern*> Hand::DissolveLongSeq1(Pattern* pattern) const
{
	assert(pattern->cards.size() >= 5);
	if (!is_sorted(pattern->cards.begin(), pattern->cards.end())) {
		sort(pattern->cards.begin(), pattern->cards.end());
	}
	std::vector<Pattern*> result{ pattern };
	for (int len = 5; len < pattern->cards.size(); len++) {
		for (auto it = pattern->cards.begin(); it + (len - 1) != pattern->cards.end(); it++) {
			result.push_back(this->patternPool->GetPattern(Patterns::Seq1, std::vector<int>(it, it + len), *(it + len - 1)));
		}
	}
	return result;
}

std::vector<Pattern*> Hand::DissolveLongSeq2(Pattern* pattern) const
{
	assert(pattern->cards.size() >= 6);
	if (!is_sorted(pattern->cards.begin(), pattern->cards.end())) {
		sort(pattern->cards.begin(), pattern->cards.end());
	}
	std::vector<Pattern*> result{ pattern };
	for (int len = 6; len < pattern->cards.size(); len += 2) {
		for (auto it = pattern->cards.begin(); it + (len - 1) != pattern->cards.end(); it += 2) {
			result.push_back(this->patternPool->GetPattern(Patterns::Seq2, std::vector<int>(it, it + len), *(it + len - 1)));
		}
	}
	return result;
}

std::vector<Pattern*> Hand::DissolvePlane(Pattern* pattern) const
{
	assert(pattern->cards.size() >= 6);
	if (!is_sorted(pattern->cards.begin(), pattern->cards.end())) {
		sort(pattern->cards.begin(), pattern->cards.end());
	}
	std::vector<Pattern*> result{ pattern };
	for (int len = 6; len < pattern->cards.size(); len += 3) {
		for (auto it = pattern->cards.begin(); it + (len - 1) != pattern->cards.end(); it += 3) {
			result.push_back(this->patternPool->GetPattern(Patterns::Seq2, std::vector<int>(it, it + len), *(it + len - 1)));
		}
	}
	return result;
}

HandPool::HandPool() : handPool(new std::unordered_map<std::vector<uint8_t>, Hand*, container_hash<std::vector<uint8_t>>>())
{
}

const Hand* HandPool::Delete(const Hand* hand, const Pattern* pattern)
{
	Hand* resultHand = nullptr;
	std::vector<uint8_t> key;
	auto it_map = hand->Cards.begin();
	int n = 0;
	auto it_vec = pattern->cards.begin();
	while (it_map != hand->Cards.end()) {
		n = it_map->second;
		while (it_vec != pattern->cards.end() && it_map->first == *it_vec) {
			n--;
			it_vec++;
		}
		assert(n >= 0);
		if (n > 0) {
			// Key为8位整数，高5位表示牌型大小（最大31，实际最大18），低3位表示数量，最大8最小1
			key.push_back((((uint8_t)it_map->first) << 3) + (n - 1));
		}
		it_map++;
	}
	this->_mutex.lock_shared();
	auto it_result = this->handPool->find(key);
	if (it_result != this->handPool->end()) {
		resultHand = it_result->second;
		this->_mutex.unlock_shared();
		return resultHand;
	}
	this->_mutex.unlock_shared();
	resultHand = hand->Delete(*pattern);
	this->_mutex.lock();
	this->handPool->emplace(key, resultHand);
	this->_mutex.unlock();
	return resultHand;
}
