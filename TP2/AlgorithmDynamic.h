#pragma once
#include "Algorithm.h"

struct Node
{
	int value;
	int id;
	Node* node;

	Node()
	{
		value = 0;
		id = 0;
		node = nullptr;
	}
};

class AlgorithmDynamic : public Algorithm
{
public:
    AlgorithmDynamic();
    virtual ~AlgorithmDynamic();
private:
    virtual Solution concreteSolve(const Problem& problem) override;
};

