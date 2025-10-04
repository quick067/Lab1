#pragma once

#include <vector> 
#include <cstddef>


class Statistics {
private:
    std::vector<size_t> dealSizes;
public:
    void addResult(size_t dealSize);
    void calculateAndPrintResult(size_t dealSize) const;

    double getAverageSize() const;
    double getMedianSize();
};