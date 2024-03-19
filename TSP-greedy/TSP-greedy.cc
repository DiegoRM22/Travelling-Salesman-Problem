
#include "TSP-greedy.h"

/**
 * Execute the greedy algorithm to solve the TSP
*/
void TSPGreedy::execute() {
  greedy();
  printBestTrip();
}

/**
 * Greedy algorithm to solve the TSP
 * @param startCity The city to start the trip
*/
void TSPGreedy::greedy(const std::string &startCity) {
  std::string currentCity = startCity;
  visitedCities_.insert(currentCity);
  currentRoute_.push_back(currentCity);
  while (visitedCities_.size() < cities_.size()) {
    int minPrice = INT_MAX;
    std::string nextCity;
    for (auto trip : trips_) {
      if (trip.getCityA() == currentCity && visitedCities_.find(trip.getCityB()) == visitedCities_.end() && trip.getTripPrice() < minPrice) {
        minPrice = trip.getTripPrice();
        nextCity = trip.getCityB();
      }
      if (trip.getCityB() == currentCity && visitedCities_.find(trip.getCityA()) == visitedCities_.end() && trip.getTripPrice() < minPrice) {
        minPrice = trip.getTripPrice();
        nextCity = trip.getCityA();
      }
    }
    totalPrice_ += minPrice;
    currentCity = nextCity;
    visitedCities_.insert(currentCity);
    currentRoute_.push_back(currentCity);
  }
  totalPrice_ += trips_[0].getTripPrice();
  currentRoute_.push_back(startCity);
}

/**
 * Print the best trip found by the greedy algorithm
*/
void TSPGreedy::printBestTrip() {
  std::cout << "Best trip: ";
  for (const auto &city : currentRoute_) {
    std::cout << city << " ";
  }
  std::cout << "with a price of " << totalPrice_ << std::endl;
}