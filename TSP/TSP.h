
#ifndef TSP_H
#define TSP_H

#include <iostream>
#include <set>
#include <vector>

#include "../trip/trip.h"

class TSP {
  public:
   TSP(std::string inputFileName);
   virtual void execute() = 0;
   void printTrips();
   void printCities();
   int searchTripPrice(const std::string &cityA, const std::string &cityB);
   std::set<std::string> cities_;



  protected:
   int numberOfCities_;
   std::vector<Trip> trips_;
   std::set<std::string> visitedCities_;
};

#endif