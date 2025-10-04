#pragma once

#include <iostream>

struct Domino {
	int p1;
	int p2;

	bool operator== (const Domino& other) const {
		return (p1 == other.p1 && p2 == other.p2) || (p1 == other.p2 && p2 == other.p1);
	}
};

std::ostream& operator<<(std::ostream& os, const Domino& domino);