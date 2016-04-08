#include "solution.h"
#include <algorithm>

Solution::Solution(Problem& problem)
{
    m_problem = &problem;
}

bool Solution::isValid()
{
    auto tempStudents = students;
    std::unique(tempStudents.begin(), tempStudents.end(),
                [](auto& left, auto& right)
                    {return left->id == right->id;});
    return tempStudents.size() == (*m_problem).students.size();
}

void Solution::print()
{
    for (const auto& student : students)
    {
        std::cout << student->id + 1 << std::endl;
    }
    std::cout << "fin" << std::endl;
}

int Solution::numberOfObstrucatedStudent()
{
    int numberOfObstrucatedStudent = 0;
    int maxHeight = -1;
    for (auto& student : students)
    {
        if(student->height > maxHeight)
        {
            maxHeight = student->height;
        }
        else
        {
            numberOfObstrucatedStudent++;
        }
    }
    return numberOfObstrucatedStudent;
}
