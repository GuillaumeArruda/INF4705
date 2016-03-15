#pragma once
#include "Algorithm.h"
class AlgorithmDynamic :
    public Algorithm
{
public:
    AlgorithmDynamic();
    virtual ~AlgorithmDynamic();
private:
    virtual Solution concreteSolve(const Problem& problem, Solution& solution) override;
};

