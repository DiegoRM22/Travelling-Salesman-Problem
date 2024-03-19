
#ifndef TSP_GREEDY_H
#define TSP_GREEDY_H

#include <iostream>
#include <climits>

#include "../TSP/TSP.h"

class TSPGreedy : public TSP {
 public:
  TSPGreedy(std::string inputFileName) : TSP(inputFileName) {}
  void execute() override;
  void greedy(const std::string &startCity = "A");
  void printBestTrip();
  int bestTripPrice_ = INT_MAX;
  private:
   std::vector<std::string> bestTripRoute_;
   std::vector<std::vector<Trip>> posiblyRoutes_;
   std::vector<std::string> currentRoute_;
   int totalPrice_ = 0;
};

#endif