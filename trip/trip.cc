
#include "trip.h"

/**
 * Overload the << operator to print a trip
*/
std::ostream& operator<<(std::ostream& os, const Trip& trip) {
  os << trip.getCityA() << " " << trip.getCityB() << " " << trip.getTripPrice();
  return os;
}
