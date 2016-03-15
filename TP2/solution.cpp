#include "solution.h"
#include <iostream>
Solution::Solution(const Problem& problem)
{
    totalChickenProduction = problem.totalChickenProduction;
}

Solution::~Solution()
{
}

bool Solution::isValid()
{
    return (totalConsommation() < totalChickenProduction) && locations.size() > 0;
}

void Solution::print()
{
    for (auto&& location : locations)
    {
        std::cout << "Id: " << location.id << " Revenu: " << location.income << " Consommation: " << location.chickenConsommation << std::endl;
    }
    std::cout << "Nombre de restaurant: " << locations.size() << std::endl;
    std::cout << "Revenu total: " << totalIncome() << std::endl;
    std::cout << "Consommation total: " << totalConsommation() << std::endl;
}

int Solution::totalIncome()
{
    int income = 0;
    for (auto&& location : locations)
    {
        income += location.income;
    }
    return income;
}

int Solution::totalConsommation()
{
    int consommation = 0;
    for (auto&& location : locations)
    {
        consommation += location.chickenConsommation;
    }
    return consommation;
}
