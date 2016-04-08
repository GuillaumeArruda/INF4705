#include "voraceAlgorithm.h"
#include <random>
#include <ctime>

VoraceAlgorithm::VoraceAlgorithm()
{
    std::srand(unsigned int(std::time(nullptr)));
}

Solution VoraceAlgorithm::concreteSolve(Problem &problem)
{
    while (true)
    {
        std::vector<Student*> students;
        for (auto& student : problem.students)
        {
            student.inSolution = false;
            students.push_back(&student);
        }
        Solution tempSolution(problem);

        Student* lastStudentAdded = chooseStudent(students);
        tempSolution.students.push_back(lastStudentAdded);
        lastStudentAdded->inSolution = true;
        while (true)
        {
            Student* nextStudent = chooseStudent(lastStudentAdded->friends);
            if (nextStudent != nullptr)
            {
                lastStudentAdded = nextStudent;
                tempSolution.students.push_back(lastStudentAdded);
                lastStudentAdded->inSolution = true;
            }
            else
            {
                break;
            }
        }
        if (tempSolution.isValid())
        {
            std::reverse(tempSolution.students.begin(), tempSolution.students.end());
            return tempSolution;
        }
    }
}

Student* VoraceAlgorithm::chooseStudent(std::vector<Student*> students)
{
    int totalHeight = 0;
    for (auto& student : students)
    {
        if (!student->inSolution)
        {
            totalHeight += student->height;
        }
    }
    std::vector<double> probabilities;
    for (auto& student : students)
    {
        if (!student->inSolution)
        {
            probabilities.push_back(double(student->height) / totalHeight);
        }
        else
        {
            probabilities.push_back(0.0);
        }
    }
    double choosenProb = double(std::rand() - 1) / RAND_MAX;
    double totalProb = 0.0;
    for (size_t i = 0; i < probabilities.size(); ++i)
    {
        totalProb += probabilities[i];
        if (totalProb > choosenProb)
        {
            return students[i];
        }
    }
    int numberOfStudent = probabilities.size();
    return nullptr;
}