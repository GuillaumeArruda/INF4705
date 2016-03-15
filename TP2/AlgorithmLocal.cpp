#include "AlgorithmLocal.h"
#include "AlgorithmVorace.h"
#include <algorithm>

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
        int removeIndex = -1;
        int addIndex = -1;
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
                        removeIndex = i;
                        addIndex = j;
                    }
                }
            }
        }
        if (removeIndex != -1 && addIndex != -1)
        {
            solution.locations.push_back(locationNotInSolution[addIndex]);
            locationNotInSolution.erase(locationNotInSolution.begin() + addIndex);
            locationNotInSolution.push_back(solution.locations[removeIndex]);
            solution.locations.erase(solution.locations.begin() + removeIndex);
        }
        else
        {
            bestSolutionReached = true;
        }
    }
    return solution;
}
