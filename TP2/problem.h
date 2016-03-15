#pragma once
#include <string>
#include <vector>
#include "location.h"

class Problem
{
public:
    Problem(const std::string& filePath);
    ~Problem();
    void loadProblem(const std::string& filePath);
    std::vector<Location> locations;
    int totalChickenProduction;
};