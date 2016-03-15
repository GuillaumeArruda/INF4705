#pragma once
#include "Algorithm.h"
class AlgorithmLocal :
    public Algorithm
{
public:
    AlgorithmLocal();
    virtual ~AlgorithmLocal();
private:
    virtual Solution concreteSolve(const Problem& problem, Solution& solution) override;
};

