#pragma once
#include "pch.h"

#include <vector>
#include <unordered_map>
#include <shared_mutex>

#include "utils.h"


enum class Patterns
{
	Rocket,//��ը
	Single,//����
	Couple,//����
	Triple,//3����
	Bomb,//ը��
	Triple1,//3��1
	Triple2,//3��2
	Bomb1,//4��2����������һ��
	Bomb2,//4��2��
	Seq1,//˳��
	Seq2,//����
	Plane,//�ɻ�
	Plane1,//�ɻ�����
	Plane2,//�ɻ�����
	None//������
};

class Pattern {
public:
	double power;  // ����
	std::vector<int> cards;  // �����
	Patterns type;  // ����
	int size;  // ϸ�����ͣ�˳�ӡ����Գ��ȣ�

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