#include "pch.h"
#include <assert.h>

#include <algorithm>
#include "utils.h"


int MostFreq(std::vector<int> list) {
	int count = 0;
	int temp = list[0];
	for (int v : list) {
		if (count == 0) {
			temp = v;
			count++;
		}
		else if (temp == v) {
			count++;
		}
		else
		{
			count--;
		}
	}
	return temp;
}


int getPlanePower(std::vector<int> list) {
	if (!is_sorted(list.begin(), list.end())) {
		sort(list.begin(), list.end());
	}
	int result = 0;
	int temp = list[0];
	int count = 0;
	for (int v : list) {
		if (temp == v) {
			count++;
		}
		else if (count >= 3 && temp > result)
		{
			result = temp;
			temp = v;
		}
		else
		{
			temp = v;
		}
	}
	return result;
}