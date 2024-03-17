
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

  protected:
   int numberOfCities_;
   std::vector<Trip> trips_;
   std::set<std::string> cities_;
   std::set<std::string> visitedCities_;
};

#endif