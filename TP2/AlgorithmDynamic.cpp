#include <iostream>
#include <set>
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
	int i = problem.locations.size();
	int j = problem.totalChickenProduction + 1;

	// Initialize results
	Node** income = new Node*[i];
	for (int k = 0; k < i; ++k)
	{
		income[k] = new Node[j];
	}

	// Fill with first location
	auto firstLocation = problem.locations[0];
	for (int l = 0; l < j; ++l)
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
	for (int k = 1; k < i; ++k)
	{
		Location location = problem.locations[k];
		for (int l = 0; l < j; ++l)
		{
			int valueWithoutNewLocation = income[k - 1][l].value;
			int valueWithNewLocation = 0;
			if (l - location.chickenConsommation >= 0)
			{
				valueWithNewLocation = income[k - 1][l - location.chickenConsommation].value + location.income;
			}

			if (valueWithNewLocation < valueWithoutNewLocation)
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

	std::vector<int> ids;
	Node* node = &income[i - 1][j - 1];

	int lastId = 0;
	while (node != nullptr)
	{
		if (node->id != lastId && node->id != 0)
		{
			ids.push_back(node->id);
			lastId = node->id;
		}
		node = node->node;
	}

	for (auto&& id : ids)
	{
		solution.locations.push_back(problem.locations[id - 1]);
	}

	std::cout << solution.totalIncome() << std::endl;
	std::cout << solution.totalConsommation() << std::endl;
	std::cout << solution.isValid() << std::endl;
    return solution;
}
