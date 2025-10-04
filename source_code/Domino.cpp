#include "Domino.h"

std::ostream& operator<<(std::ostream& os, const Domino& domino) {
	os << "[" << domino.p1 << "|" << domino.p2 << "]";
	return os;
}