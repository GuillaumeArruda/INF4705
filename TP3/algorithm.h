#pragma once
#include "solution.h"
class Algorithm
{
public:
    Algorithm();
    virtual ~Algorithm();
    Solution solve(const Problem& problem, bool printResult);
private:
    virtual Solution concreteSolve(const Problem& problem) = 0;
};

