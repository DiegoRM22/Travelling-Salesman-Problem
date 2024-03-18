#ifndef TSP_DYNAMIC_PROGRAMMING_H
#define TSP_DYNAMIC_PROGRAMMING_H

#include <iostream>
#include <vector>
#include <set>

#include "../TSP/TSP.h"

class TSPDynamicProgramming : public TSP {
public:
    TSPDynamicProgramming(std::string& file_name) : TSP(file_name) {}
    ~TSPDynamicProgramming() {}

    void execute() override;
    void print_result(int min_distance);
private:
    int tsp(const std::vector<std::vector<int>>& distance, std::string startCity, std::set<std::string> leftCities);
    int minDistance(const std::vector<std::vector<int>>& distance);
    std::vector<std::string> route_;
};

#endif // TSP_DYNAMIC_PROGRAMMING_H
