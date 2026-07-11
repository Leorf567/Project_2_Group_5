#pragma once
#include <string>
#include <vector>

struct Billionaire {
    std::string name;
    int rank;
    int year;
    std::string company;
    std::string sector;
    int age;
    double netWorth;
};

std::vector<Billionaire> loadBillionaireData(const std::string& filepath);