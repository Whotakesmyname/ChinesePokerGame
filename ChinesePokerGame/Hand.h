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

	std::map<int, int> Cards;  // ����

	Hand& Insert(int card);  // ��������
	Hand* Delete(int card, int n) const;  // ɾ��ĳ�����Ʋ�����֮�������
	Hand* Delete(std::vector<int> card, std::vector<int> n) const;
	Hand* Delete(const Pattern& pattern) const;
	std::vector<Pattern*> getAllSolutions() const;  // ��ȡ���п��ܳ������
	std::vector<Pattern*> getAllSolutions(const Pattern* pattern) const;  // ��ȡ��һ�����п��ܳ������

	bool IsEmpty() const;

private:
	PatternPool* const patternPool;
	std::vector<Pattern*> getSingles(const Pattern* pattern) const;  // ��ȡ���е������
	std::vector<Pattern*> getCouples(const Pattern* pattern) const;  // ��ȡ���ж������
	std::vector<Pattern*> getTriples(const Pattern* pattern) const;  // ��ȡ�������������
	std::vector<Pattern*> getBombs(const Pattern* pattern) const;  // ��ȡ����ը�����
	std::vector<Pattern*> getTriple1s(const Pattern* pattern) const;  // ��ȡ����3��1���
	std::vector<Pattern*> getTriple2s(const Pattern* pattern) const;  // ��ȡ����3��2���
	std::vector<Pattern*> getBomb1s(const Pattern* pattern) const;  // ��ȡ����ը����1���
	std::vector<Pattern*> getBomb2s(const Pattern* pattern) const;  // ��ȡ����ը����2���
	std::vector<Pattern*> getSeq1s(const Pattern* pattern) const;  // ��ȡ����˳�����
	std::vector<Pattern*> getSeq2s(const Pattern* pattern) const;  // ��ȡ�����������
	std::vector<Pattern*> getPlanes(const Pattern* pattern) const;  // ��ȡ���зɻ����
	//vector<Pattern*> getPlane1s(const Pattern* pattern) const;  // ��ȡ���зɻ��������
	//vector<Pattern*> getPlane2s(const Pattern* pattern) const;  // ��ȡ���зɻ��������
	std::vector<Pattern*> getRocket(const Pattern* pattern) const;  // ��ը
	std::vector<Pattern*> getPass(const Pattern* pattern) const;  // ����

	// �ֽⳤ˳�ӣ����ذ�����������п������
	std::vector<Pattern*> DissolveLongSeq1(Pattern* pattern) const;

	// �ֽⳤ���ԣ����ذ�����������п������
	std::vector<Pattern*> DissolveLongSeq2(Pattern* pattern) const;

	// �ֽⳤ�ɻ������ذ�����������п������
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
