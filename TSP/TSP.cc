
#include <iostream>
#include <fstream>

#include "TSP.h"

TSP::TSP(std::string inputFileName) {
  std::ifstream inputFile(inputFileName);
  inputFile >> numberOfCities_;
  std::string cityA, cityB;
  int tripPrice;
  while (inputFile >> cityA >> cityB >> tripPrice) {
    cities_.insert(cityA);
    cities_.insert(cityB);
    trips_.push_back(Trip(cityA, cityB, tripPrice));
  }
  inputFile.close();
}

void TSP::printTrips() {
  for (auto trip : trips_) {
    std::cout << trip << std::endl;
  }
}

void TSP::printCities() {
  for (auto city : cities_) {
    std::cout << city << std::endl;
  }
}