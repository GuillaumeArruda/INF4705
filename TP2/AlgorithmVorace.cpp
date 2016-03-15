#include "AlgorithmVorace.h"
#include <cstdlib>

AlgorithmVorace::AlgorithmVorace()
{
}


AlgorithmVorace::~AlgorithmVorace()
{
}

Solution AlgorithmVorace::concreteSolve(const Problem& problem)
{
    Solution bestSolution(problem);
    for (int i = 0; i < 10; i++)
    {
        Solution tempSolution(problem);
        std::vector<Location> possibleLocationLeft(problem.locations);
        std::vector<float> locationProbability;
        while (possibleLocationLeft.size() > 0)
        {
            float totalCost = 0.0f;
            for (auto&& location : possibleLocationLeft)
            {
                float cost = location.cost();
                totalCost += cost;
                locationProbability.push_back(cost);
            }
            for (size_t i = 0; i < locationProbability.size(); ++i)
            {
                locationProbability[i] /= totalCost;
            }
            float chosenLocation = float(std::rand()) / RAND_MAX;
            float totalProbability = 0.f;
            for (size_t i = 0; i < locationProbability.size(); ++i)
            {
                totalProbability += locationProbability[i];
                if (totalProbability > chosenLocation)
                {
                    tempSolution.locations.push_back(possibleLocationLeft[i]);
                    possibleLocationLeft.erase(possibleLocationLeft.begin() + i);
                    if (!tempSolution.isValid())
                    {
                        tempSolution.locations.pop_back();
                    }
                    break;
                }
            }
            locationProbability.clear();
        }

        if (bestSolution.totalIncome() < tempSolution.totalIncome())
        {
            bestSolution = tempSolution;
        }
    }
    return bestSolution;
}
