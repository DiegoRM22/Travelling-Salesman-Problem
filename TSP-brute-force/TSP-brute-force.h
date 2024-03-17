
#ifndef TSP_BRUTE_FORCE_H
#define TSP_BRUTE_FORCE_H

#include <iostream>
#include <climits>

#include "../TSP/TSP.h"

class TSPBruteForce : public TSP {
 public:
  TSPBruteForce(std::string inputFileName) : TSP(inputFileName) {}
  void execute() override;
  void bruteForce(const std::string &startCity = "B");
  void printBestTrip();
  int calculateTotalDistance(const std::vector<std::string>& route, const std::vector<Trip>& trips);
  int bestTripPrice_ = INT_MAX;
  private:
   std::vector<std::string> bestTripRoute_;
   std::vector<std::vector<Trip>> posiblyRoutes_;
   std::vector<std::string> currentRoute_;
   std::vector<int> tripPrices_;
   

};


#endif