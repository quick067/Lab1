//Compiler: Microsoft Visual Studio 2022 (MSVC), Standard: C++20
#include <iostream>
#include <string>
#include <limits>
#include "DominoDealer.h"
#include "Statistics.h"
#include <iomanip>

int getUserInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.good() && value >= 0) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "Error happened, please, enter a non-negative integer.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void runExperiment() {
    std::cout << "\n\n--- Experiment ---\n";
    std::cout << "Study of the dependence of the ratio of the mean/median size to the total number of bones on N. \n";
    std::cout << "For every N would be launched 1000 simulations. \n\n";

    std::cout << std::setw(5) << "N" << " | "
        << std::setw(15) << "Bones at all" << " | "
        << std::setw(15) << "Average size" << " | "
        << std::setw(16) << "Median size" << " | "
        << std::setw(20) << "Ratio(Average)" << " | "
        << std::setw(20) << "Ratio(Median)" << " | " << "\n";
    std::cout << std::string(110, '-') << "\n";

    for (int nVal = 0; nVal <= 10; ++nVal)
    {
        DominoDealer dealer(nVal);
        Statistics stats;
        size_t total_dominoes = dealer.getTotalDominoCount();
        const int num_simulations = 10000;

        for (int i = 0; i < num_simulations; ++i) {
            dealer.reset();
            while (!dealer.isFinished()) {
                dealer();
            }
            stats.addResult(dealer.getDealSize());
        }

        double avg = stats.getAverageSize();
        double med = stats.getMedianSize();

        double ratio_avg = avg / static_cast<double>(total_dominoes);
        double ratio_med = med / static_cast<double>(total_dominoes);

        std::cout << std::setw(5) << nVal << " | "
            << std::setw(15) << total_dominoes << " | "
            << std::fixed << std::setprecision(2) << std::setw(15) << avg << " | "
            << std::fixed << std::setprecision(2) << std::setw(16) << med << " | "
            << std::fixed << std::setprecision(4) << std::setw(20) << ratio_avg << " | "
            << std::fixed << std::setprecision(4) << std::setw(20) << ratio_med << "\n";
    }
}

int main() {
    try {
        int n_max = getUserInput("Enter maximum number on a domino bone(N): ");
        int num_deals = getUserInput("Enter the number of deals for the simulation: ");

        DominoDealer dealer(n_max);
        Statistics stats;

        std::cout << "\n...\n";
        for (int i = 0; i < num_deals; ++i) {
            dealer.reset();
            while (true) {
                auto domino = dealer();
                if (!domino.has_value()) {
                    break;
                }
            }
            stats.addResult(dealer.getDealSize());
        }

        stats.calculateAndPrintResult(num_deals);
        runExperiment();

    }
    catch (const std::exception& e) {
        std::cout << "Error happened: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}