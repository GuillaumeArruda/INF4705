#include "solution.h"

Solution::Solution(Problem& problem)
{
    m_problem = &problem;
}

bool Solution::isValid()
{
    return students.size() == (*m_problem).students.size();
}

void Solution::print()
{
    for (const auto& student : students)
    {
        std::cout << student.id + 1 << std::endl;
    }
    std::cout << "fin" << std::endl;
}

int Solution::numberOfObstrucatedStudent()
{
    int numberOfObstrucatedStudent = 0;
    for (size_t i = 0; i < students.size(); ++i)
    {
        for (size_t j = i; j >= 0; --j)
        {
            if (students[i].height < students[j].height)
            {
                numberOfObstrucatedStudent++;
                break;
            }
        }
    }
    return numberOfObstrucatedStudent;
}
