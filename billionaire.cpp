#include "billionaire.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::vector<Billionaire> loadBillionaireData(const std::string& filepath) {
    std::vector<Billionaire> database;
    std::ifstream file(filepath);
    std::string line;
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return database;
    }
    std::getline(file, line); // Skip header
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        Billionaire b;
        try {
            std::getline(ss, b.name, '\t');
            std::getline(ss, token, '\t');
            b.rank = token.empty() ? 0 : std::stoi(token);
            std::getline(ss, token, '\t');
            b.year = token.empty() ? 0 : std::stoi(token);
            std::getline(ss, b.company, '\t');
            std::getline(ss, b.sector, '\t');
            std::getline(ss, token, '\t');
            b.age = token.empty() ? 0 : std::stoi(token);
            std::getline(ss, token, '\t');
            b.netWorth = token.empty() ? 0.0 : std::stod(token);
            std::getline(ss, b.country, '\t');
            std::getline(ss, token, '\t');
            b.gdp = token.empty() ? 0.0 : std::stod(token);
            database.push_back(b);
        } catch (const std::exception& e) {
            std::cerr << "Skipping malformed row: " << line << std::endl;
        }
    }
    return database;
}
