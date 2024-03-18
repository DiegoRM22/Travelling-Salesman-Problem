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

    std::pair<int, std::vector<int>> find_travelling_salesman_cycle();


    void execute() override;
    void print_result(int min_distance);
private:
    int tsp(const std::vector<std::vector<int>>& distance, std::string startCity, std::set<std::string> leftCities);
    int minDistance(const std::vector<std::vector<int>>& distance);
    std::vector<std::string> route_;
    std::vector<std::vector<int>> min_path_;
    int min_distance_;
};


#endif // TSP_DYNAMIC_PROGRAMMING_H
