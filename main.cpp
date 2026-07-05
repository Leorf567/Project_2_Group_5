#include <iostream>
#include "billionaire.h"

void analyzeWealthImpact(const std::vector<Billionaire>& data) {
    double totalWealth = 0;
    for (const auto& b : data) {
        totalWealth += b.netWorth;
    }
    std::cout << "Total dataset wealth: $" << totalWealth << "B\n";
}

int main() {
    std::vector<Billionaire> database = loadBillionaireData("billionaires_flat.txt");

    if (!database.empty()) {
        analyzeWealthImpact(database);
    }

    return 0;
}