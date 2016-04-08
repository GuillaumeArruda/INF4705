#ifndef VORACEALGORITHM_H
#define VORACEALGORITHM_H

#include "algorithm.h"
class VoraceAlgorithm : public Algorithm
{
public:
    VoraceAlgorithm();
private:
    Solution concreteSolve(Problem &problem);
    Student* chooseStudent(std::vector<Student*> students);
};

#endif // VORACEALGORITHM_H
