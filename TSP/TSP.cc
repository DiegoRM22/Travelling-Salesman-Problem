
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

int TSP::searchTripPrice(const std::string &cityA, const std::string &cityB) {
  for (auto trip : trips_) {
    if ((trip.getCityA() == cityA && trip.getCityB() == cityB) || (trip.getCityA() == cityB && trip.getCityB() == cityA)) {
      return trip.getTripPrice();
    } else if (cityA == cityB) {
      return 0;
    }
  }
  return -1;
}