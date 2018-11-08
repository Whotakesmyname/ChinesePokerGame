#pragma once
#include "pch.h"

#include <vector>
#include <boost/functional/hash.hpp>


static const int LITTLE_JOKER = 18;
static const int JOKER = 19;

int MostFreq(std::vector<int> list);

// 得到飞机的牌力；list必须sort过。
int getPlanePower(std::vector<int> list);

template <typename Container> // we can make this generic for any container
class container_hash {
public:
	std::size_t operator()(Container const& c) const {
		return boost::hash_range(c.begin(), c.end());
	}
};

// Helper function for concating results
template<typename T>
inline void InsertResultVector(T &target, T source)
{
	target.insert(target.end(), source.begin(), source.end());
};

template<typename T>
std::ostream & operator<<(std::ostream & os, std::vector<T> vec)
{
	os << "{";
	if (vec.size() != 0)
	{
		std::copy(vec.begin(), vec.end() - 1, std::ostream_iterator<T>(os, " "));
		os << vec.back();
	}
	os << "}";
	return os;
}

// Get bigger number
inline int Max(int a, int b) {
	if (a > b)return a;
	return b;
}