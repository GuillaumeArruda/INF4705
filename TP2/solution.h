#pragma once
#include "problem.h"

class Solution
{
public:
    Solution(const Problem& problem);
    ~Solution();
    std::vector<Location> locations;
    int totalChickenProduction;
    bool isValid();
    void print();
    int totalIncome();
    int totalConsommation();
};

