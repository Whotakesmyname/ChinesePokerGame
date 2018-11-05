#include "pch.h"
#include "Pattern.h"

#include <algorithm>


Pattern::Pattern(Patterns type, std::vector<int> cards) {
	this->cards = cards;
	this->type = type;
	this->size = cards.size();
	this->power = 0;
	switch (type)
	{
	case Patterns::Rocket:
		this->power = 1;
		break;
	case Patterns::Single:
		this->power = cards[0];
		break;
	case Patterns::Couple:
		this->power = cards[0];
		break;
	case Patterns::Triple:
		this->power = cards[0];
		break;
	case Patterns::Bomb:
		this->power = cards[0];
		break;
	case Patterns::Triple1:
		this->power = MostFreq(cards);
		break;
	case Patterns::Triple2:
		this->power = MostFreq(cards);
		break;
	case Patterns::Bomb1:
		this->power = MostFreq(cards);
		break;
	case Patterns::Bomb2:
		this->power = MostFreq(cards);
		break;
	case Patterns::Seq1:
		nth_element(cards.begin(), cards.end() - 1, cards.end());
		this->power = cards.back();
		break;
	case Patterns::Seq2:
		nth_element(cards.begin(), cards.end() - 1, cards.end());
		this->power = cards.back();
		break;
	case Patterns::Plane:
		this->power = getPlanePower(cards);
		break;
	case Patterns::Plane1:
		this->power = getPlanePower(cards);
		break;
	case Patterns::Plane2:
		this->power = getPlanePower(cards);
		break;
	case Patterns::None:
		this->power = 0;
		break;
	}
}

Pattern::Pattern(Patterns type, std::vector<int> cards, double power)
{
	this->cards = cards;
	this->type = type;
	this->power = power;
	this->size = cards.size();
}

bool Pattern::operator==(const Pattern& other)
{
	return (this->type == other.type) && (this->size == other.size) && (this->power == other.power);
}

bool Pattern::operator>(const Pattern & other)
{
	if (this->type == other.type && this->size == other.size) return this->power > other.power;
	if (this->type == Patterns::Rocket) return true;
	if (this->type == Patterns::Bomb) return true;
	return false;
}

PatternPool::PatternPool() : patternPool{ new std::unordered_map < std::vector<int>, Pattern* const, container_hash<std::vector<int>>>() }
{
}

Pattern *const PatternPool::GetPattern(Patterns type, std::vector<int> cards)
{
	Pattern* _pattern=nullptr;
	std::sort(cards.begin(), cards.end());
	this->_mutex.lock_shared();
	auto it = this->patternPool->find(cards);
	if (it == this->patternPool->end()) {
		this->_mutex.unlock_shared();
		_pattern = new Pattern(type, cards);
		this->_mutex.lock();
		this->patternPool->emplace(cards, _pattern);
		this->_mutex.unlock();
		return _pattern;
	}
	_pattern = it->second;
	this->_mutex.unlock_shared();
	return _pattern;
}

Pattern *const PatternPool::GetPattern(Patterns type, std::vector<int> cards, int power)
{
	Pattern* _pattern = nullptr;
	std::sort(cards.begin(), cards.end());
	this->_mutex.lock_shared();
	auto it = this->patternPool->find(cards);
	if (it == this->patternPool->end()) {
		this->_mutex.unlock_shared();
		_pattern = new Pattern(type, cards, power);
		this->_mutex.lock();
		this->patternPool->emplace(cards, _pattern);
		this->_mutex.unlock();
		return _pattern;
	}
	_pattern = it->second;
	this->_mutex.unlock_shared();
	return _pattern;
}

