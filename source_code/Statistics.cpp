#include "Statistics.h"
#include <iostream>
#include <map>
#include <numeric>
#include <algorithm>
#include <iomanip>

void Statistics::addResult(size_t dealSize) {
    dealSizes.push_back(dealSize);
}

double Statistics::getAverageSize() const {
    if (dealSizes.empty()) {
        return 0.0;
    }
    double sum = std::accumulate(dealSizes.begin(), dealSizes.end(), 0.0);
    return sum / dealSizes.size();
}

double Statistics::getMedianSize() {
    if (dealSizes.empty()) {
        return 0.0;
    }
    std::sort(dealSizes.begin(), dealSizes.end());
    size_t n = dealSizes.size();
    if (n % 2 != 0) {
        return static_cast<double>(dealSizes[n / 2]);
    }
    return static_cast<double>(dealSizes[(n - 1) / 2] + dealSizes[n / 2]) / 2.0;
}

void Statistics::calculateAndPrintResult(size_t totalDeals) const {
    if (dealSizes.empty()) {
        std::cout << "No distribution has carried out!" << std::endl;
        return;
    }

    std::map<size_t, size_t> frequencies;
    for (size_t size : dealSizes) {
        frequencies[size]++;
    }

    std::cout << "\n--- Statistics for " << totalDeals << " distributions ---\n";
    std::cout << "Distribution size | Quantity | Percent\n";
    for (const auto& pair : frequencies) {
        double percentage = (static_cast<double>(pair.second) / totalDeals) * 100.0;
        std::cout << std::setw(15) << std::left << pair.first
            << " | " << std::setw(9) << std::left << pair.second
            << " | " << std::fixed << std::setprecision(2) << percentage << "%\n";
    }

    auto mostFrequent = std::max_element(frequencies.begin(), frequencies.end(),
        [](const auto& a, const auto& b) {
            return a.second < b.second;
        });

    std::cout << "\n> Size that happend the most time: " << mostFrequent->first
        << " (" << mostFrequent->second << " times)\n";

    double average = getAverageSize();
    std::cout << "> Average size of distribution: " << std::fixed << std::setprecision(2) << average << "\n";

    std::vector<size_t> sortedSizes = dealSizes;
    std::sort(sortedSizes.begin(), sortedSizes.end());
    double median;
    size_t n = sortedSizes.size();
    if (n % 2 != 0) {
        median = static_cast<double>(sortedSizes[n / 2]);
    }
    else {
        median = static_cast<double>(sortedSizes[(n - 1) / 2] + sortedSizes[n / 2]) / 2.0;
    }

    std::cout << "> Median size of distribution: " << std::fixed << std::setprecision(2) << median << "\n";

}