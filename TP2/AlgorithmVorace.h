#pragma once
#include "Algorithm.h"
class AlgorithmVorace :
    public Algorithm
{
public:
    AlgorithmVorace();
    virtual ~AlgorithmVorace();
private:
    virtual Solution concreteSolve(const Problem& problem) override;
};

