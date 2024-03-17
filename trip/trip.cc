
#include "trip.h"

std::ostream& operator<<(std::ostream& os, const Trip& trip) {
  os << trip.getCityA() << " " << trip.getCityB() << " " << trip.getTripPrice();
  return os;
}