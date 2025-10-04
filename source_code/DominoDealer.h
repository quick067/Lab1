#pragma once
#include<random>
#include<vector>
#include<deque>
#include"Domino.h"
#include<optional>


class DominoDealer {
private:
	std::mt19937 random_generator;
	bool isDealFinished;
	int N;
	std::deque<Domino> chain;
	std::vector<Domino> remainingDominoes;
	const std::vector<Domino> dominoSet;

public:
	DominoDealer(int n);
	std::optional<Domino> operator()();
	void reset();

	bool isFinished() const;
	size_t getTotalDominoCount() const;
	size_t getDealSize() const;
};