#include "AlgorithmVorace.h"
#include <random>

AlgorithmVorace::AlgorithmVorace()
{
    
}


AlgorithmVorace::~AlgorithmVorace()
{
}

Solution AlgorithmVorace::concreteSolve(const Problem& problem)
{
    Solution bestSolution(problem);
    std::uniform_real_distribution<float> randomGenerator = std::uniform_real_distribution<float>(0.f, 1.f);
    for (int i = 0; i < 10; i++)
    {
        Solution tempSolution(problem);
        std::random_device rd;
        std::mt19937 gen(rd());
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
            float chosenLocation = randomGenerator(gen);
            float totalProbability = 0.f;
            for (size_t i = 0; i < locationProbability.size(); ++i)
            {
                totalProbability += locationProbability[i];
                if (totalProbability > chosenLocation)
                {
                    if (possibleLocationLeft[i].chickenConsommation + tempSolution.totalConsommation() <  tempSolution.totalChickenProduction)
                    {
                        tempSolution.locations.push_back(possibleLocationLeft[i]);
                    }
                    possibleLocationLeft.erase(possibleLocationLeft.begin() + i);
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
