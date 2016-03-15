#include "problem.h"
#include <fstream>
Problem::Problem(const std::string& filePath)
{
    loadProblem(filePath);
}

Problem::~Problem()
{

}

void Problem::loadProblem(const std::string& filePath)
{
    int numberOfLocation;
    std::ifstream file;
    file.open(filePath);
    if (file.is_open())
    {
        file >> numberOfLocation;
        for (int i = 0; i < numberOfLocation; ++i)
        {
            locations.push_back(Location());
            file >> locations[i].id;
            file >> locations[i].income;
            file >> locations[i].chickenConsommation;
        }
        file >> totalChickenProduction;
    }
    file.close();
}
