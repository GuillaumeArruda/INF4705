#include <iostream>
#include "AlgorithmDynamic.h"

AlgorithmDynamic::AlgorithmDynamic()
{
}


AlgorithmDynamic::~AlgorithmDynamic()
{
}

Solution AlgorithmDynamic::concreteSolve(const Problem& problem)
{
	Solution solution = Solution(problem);
    int numberOfLocation = problem.locations.size();
    int maxChickenConsommation = problem.totalChickenProduction + 1;

	// Initialize results
    Node** income = new Node*[numberOfLocation];
    for (int k = 0; k < numberOfLocation; ++k)
	{
        income[k] = new Node[maxChickenConsommation];
	}

	// Fill with first location
	auto firstLocation = problem.locations[0];
    for (int l = 0; l < maxChickenConsommation; ++l)
	{
		income[0][l].node = nullptr;
		if (l - firstLocation.chickenConsommation >= 0)
		{
			income[0][l].value = firstLocation.income;
			income[0][l].id = firstLocation.id;
		}
		else
		{
			income[0][l].value = 0;
			income[0][l].id = 0;
		}
	}

	// Fill with locations
    for (int k = 1; k < numberOfLocation; ++k)
	{
		Location location = problem.locations[k];
        for (int l = 0; l < maxChickenConsommation; ++l)
		{
			int valueWithoutNewLocation = income[k - 1][l].value;
			int valueWithNewLocation = 0;

            if (l - location.chickenConsommation >= 0)
			{
				valueWithNewLocation = income[k - 1][l - location.chickenConsommation].value + location.income;
			}

			if (valueWithNewLocation <= valueWithoutNewLocation)
			{
				income[k][l].node = &income[k - 1][l];
				income[k][l].value = valueWithoutNewLocation;
				income[k][l].id = income[k - 1][l].id;
			}
			else
			{
                income[k][l].node = &income[k - 1][l - location.chickenConsommation];
				income[k][l].value = valueWithNewLocation;
				income[k][l].id = location.id;
			}
		}
	}

    int lastId = -1;
    for(auto node = &income[numberOfLocation -1][maxChickenConsommation -1]; node != nullptr; node = node->node)
    {
        if (node->id != lastId && node->id != 0)
        {
			solution.locations.push_back(problem.locations[node->id - 1]);
			lastId = node->id;
        }
    }

	std::cout << solution.totalIncome() << std::endl;
	std::cout << solution.totalConsommation() << std::endl;
	std::cout << solution.isValid() << std::endl;
    return solution;
}
