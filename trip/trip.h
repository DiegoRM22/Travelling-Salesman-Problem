
#ifndef TRIP_H
#define TRIP_H

#include <iostream>

class Trip {
  public:
   Trip(std::string cityA, std::string cityB, int tripPrice) : cityA_(cityA), cityB_(cityB), tripPrice_(tripPrice) {}
   std::string getCityA() const { return cityA_; }
   std::string getCityB() const { return cityB_; }
   int getTripPrice() const { return tripPrice_; }
   
  private:
   std::string cityA_;
   std::string cityB_;
   int tripPrice_;
};

std::ostream& operator<<(std::ostream& os, const Trip& trip);

#endif