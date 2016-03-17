#include "AlgorithmLocal.h"
#include "AlgorithmVorace.h"
#include <algorithm>
#include <iostream>

AlgorithmLocal::AlgorithmLocal()
{
}


AlgorithmLocal::~AlgorithmLocal()
{
}

Solution AlgorithmLocal::concreteSolve(const Problem& problem)
{
    AlgorithmVorace vorace;
    Solution solution(problem);
    solution = vorace.solve(problem, false, false);
    bool bestSolutionReached = false;
    std::vector<Location> locationNotInSolution(problem.locations.size());
    std::sort(solution.locations.begin(), solution.locations.end());
    auto it = std::set_difference(problem.locations.begin(), problem.locations.end(), solution.locations.begin(), solution.locations.end(), locationNotInSolution.begin());
    locationNotInSolution.resize(it - locationNotInSolution.begin());
    while (!bestSolutionReached)
    {
        int solutionTotalIncome = solution.totalIncome();
        int solutionTotalConsommation = solution.totalConsommation();
        int bestIncome = solutionTotalIncome;
        int removeIndex[2];
        removeIndex[0] = -1;
        removeIndex[1] = -1;
        int addIndex[2];
        addIndex[0] = -1;
        addIndex[1] = -1;
        //One replace one
        for (size_t i = 0; i < solution.locations.size(); ++i)
        {
            int currentIncome = solutionTotalIncome - solution.locations[i].income;
            int currentConsommation = solutionTotalConsommation - solution.locations[i].chickenConsommation;
            for (size_t j = 0; j < locationNotInSolution.size(); ++j)
            {
                if (currentConsommation + locationNotInSolution[j].chickenConsommation < problem.totalChickenProduction)
                {
                    int newIncome = currentIncome + locationNotInSolution[j].income;
                    if (newIncome > bestIncome)
                    {
                        bestIncome = newIncome;
                        removeIndex[0] = i;
                        removeIndex[1] = -1;
                        addIndex[0] = j;
                        addIndex[1] = -1;
                    }
                }
            }
        }
        //One replace two
        for(size_t i = 0; i < solution.locations.size(); ++i)\
        {
            int incomeWithoutFistLocation = solutionTotalIncome - solution.locations[i].income;
            int consommationWithoutFirstLocation = solutionTotalConsommation - solution.locations[i].chickenConsommation;
            for(size_t j = i + 1; j < solution.locations.size(); ++j)
            {
                int currentIncome = incomeWithoutFistLocation - solution.locations[j].income;
                int currentConsommation = consommationWithoutFirstLocation - solution.locations[j].chickenConsommation;
                for(size_t k = 0; k < locationNotInSolution.size(); ++k)
                {
                    if(currentConsommation + locationNotInSolution[k].chickenConsommation < problem.totalChickenProduction)
                    {
                        int newIncome = currentIncome + locationNotInSolution[k].income;
                        if(newIncome > bestIncome)
                        {
                            bestIncome = newIncome;
                            removeIndex[0] = i;
                            removeIndex[1] = j;
                            addIndex[0] = k;
                            addIndex[1] = -1;
                        }
                    }
                }
            }
        }

        //Two replace one
        for(size_t i = 0; i < solution.locations.size(); ++i)\
        {
            int incomeWithoutFistLocation = solutionTotalIncome - solution.locations[i].income;
            int consommationWithoutFirstLocation = solutionTotalConsommation - solution.locations[i].chickenConsommation;
            for(size_t j = 0; j < locationNotInSolution.size(); ++j)
            {
                int currentIncome = incomeWithoutFistLocation +locationNotInSolution[j].income;
                int currentConsommation = consommationWithoutFirstLocation + locationNotInSolution[j].chickenConsommation;
                if(currentConsommation < problem.totalChickenProduction)
                {
                    for(size_t k = j + 1; k < locationNotInSolution.size(); ++k)
                    {
                        if(currentConsommation + locationNotInSolution[k].chickenConsommation < problem.totalChickenProduction)
                        {
                            int newIncome = currentIncome + locationNotInSolution[k].income;
                            if(newIncome > bestIncome)
                            {
                                bestIncome = newIncome;
                                removeIndex[0] = i;
                                removeIndex[1] = -1;
                                addIndex[0] = j;
                                addIndex[1] = k;
                            }
                        }
                    }
                }
            }
        }
        //Two replace two
        for(size_t i = 0; i < solution.locations.size(); ++i)\
        {
            int incomeWithoutFistLocation = solutionTotalIncome - solution.locations[i].income;
            int consommationWithoutFirstLocation = solutionTotalConsommation - solution.locations[i].chickenConsommation;
            for(size_t j = i + 1; j <solution.locations.size(); ++j)
            {
                int incomeWithoutTwoLocation = incomeWithoutFistLocation - solution.locations[j].income;
                int consommationWithoutTwoLocation = consommationWithoutFirstLocation - solution.locations[j].chickenConsommation;
                for(size_t k = 0; k < locationNotInSolution.size(); ++k)
                {
                    int currentIncome = incomeWithoutTwoLocation + locationNotInSolution[k].income;
                    int currentConsommation = consommationWithoutTwoLocation + locationNotInSolution[k].chickenConsommation;
                    if(currentConsommation < problem.totalChickenProduction)
                    {
                        for(size_t l = k + 1; l < locationNotInSolution.size(); ++l)
                        {
                            if(currentConsommation + locationNotInSolution[l].chickenConsommation < problem.totalChickenProduction)
                            {
                                int newIncome = currentIncome + locationNotInSolution[l].income;
                                if(newIncome > bestIncome)
                                {
                                    bestIncome = newIncome;
                                    removeIndex[0] = i;
                                    removeIndex[1] = j;
                                    addIndex[0] = k;
                                    addIndex[1] = l;
                                }
                            }
                        }
                    }
                }
            }
        }

        if (removeIndex[0] != -1 && addIndex[0] != -1)
        {
            if(addIndex[1] != -1)
            {
                solution.locations.push_back(locationNotInSolution[addIndex[1]]);
                locationNotInSolution.erase(locationNotInSolution.begin() + addIndex[1]);
            }
            if(removeIndex[1] != -1)
            {
                locationNotInSolution.push_back(solution.locations[removeIndex[1]]);
                solution.locations.erase(solution.locations.begin() + removeIndex[1]);
            }
            solution.locations.push_back(locationNotInSolution[addIndex[0]]);
            locationNotInSolution.erase(locationNotInSolution.begin() + addIndex[0]);
            locationNotInSolution.push_back(solution.locations[removeIndex[0]]);
            solution.locations.erase(solution.locations.begin() + removeIndex[0]);
        }
        else
        {
            bestSolutionReached = true;
        }
    }
    return solution;
}
