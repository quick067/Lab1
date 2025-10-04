#include"DominoDealer.h"
#include<stdexcept>
#include<algorithm>
#include<iostream>


std::vector<Domino> generateFullSet(int n) {
	if (n < 0) {
		throw std::invalid_argument("N must be non-negative");
	}
	std::vector<Domino> dominoHand;
	for (int i = 0; i <= n; i++)
	{
		for (int j = i; j <=n; j++)
		{
			dominoHand.push_back({ i, j });
		}
	}
	return dominoHand;
}

DominoDealer::DominoDealer(int n):	
	N(n), dominoSet(generateFullSet(n)), isDealFinished(false) {
	std::random_device rd;
	random_generator.seed(rd());
	reset();
}

std::optional<Domino> DominoDealer::operator()() {
	if (isDealFinished || remainingDominoes.empty()) {
		isDealFinished = true;
		return std::nullopt;
	}

	std::uniform_int_distribution<size_t> dist(0, remainingDominoes.size() - 1);
	size_t randomIndex = dist(random_generator);
	Domino drawnDomino = remainingDominoes[randomIndex];

	remainingDominoes.erase(remainingDominoes.begin() + randomIndex);

	if (chain.empty()) {
		chain.push_back(drawnDomino);
		return drawnDomino;
	}

	int leftEnd = chain.front().p1;
	int rightEnd = chain.back().p2;

	bool possibleToAttachLeft = (drawnDomino.p1 == leftEnd || drawnDomino.p2 == leftEnd);
	bool possibleToAttachRight = (drawnDomino.p1 == rightEnd || drawnDomino.p2 == rightEnd);

	if (!possibleToAttachLeft && !possibleToAttachRight) {
		isDealFinished = true;
		return std::nullopt;
	}

	bool preferLeft = false;
	if (possibleToAttachLeft && possibleToAttachRight) {
		if (drawnDomino.p1 == drawnDomino.p2) {
			preferLeft = true;
		}
		else {
			int leftMatch = (drawnDomino.p1 == leftEnd) ? drawnDomino.p1 : drawnDomino.p2;
			int rightMatch = (drawnDomino.p1 == rightEnd) ? drawnDomino.p1 : drawnDomino.p2;
			if (leftMatch < rightMatch) {
				preferLeft = true;
			}
			else if (rightMatch < leftMatch) {
				preferLeft = false;
			}
			else {
				preferLeft = true;
			}
		}
	}
	else if (possibleToAttachLeft) {
		preferLeft = true;
	}

	if (preferLeft) {
		if (drawnDomino.p1 == leftEnd) {
			chain.push_front({ drawnDomino.p2, drawnDomino.p1 });
		}
		else {
			chain.push_front(drawnDomino);
		}
	}
	else {
		if (drawnDomino.p1 == rightEnd) {
			chain.push_back(drawnDomino);
		}
		else {
			chain.push_back({ drawnDomino.p2, drawnDomino.p1 });
		}
	}
	return drawnDomino;
}
void DominoDealer::reset() {
	remainingDominoes = dominoSet;
	chain.clear();
	isDealFinished = false;
}

bool DominoDealer::isFinished() const {
	return isDealFinished;
}

size_t DominoDealer::getTotalDominoCount() const {
	return dominoSet.size();
}

size_t DominoDealer::getDealSize() const {
	return chain.size();
}