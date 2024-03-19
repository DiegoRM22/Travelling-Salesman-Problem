

#include "TSP-brute-force.h"
#include "../trip/trip.h"

/**
 * @brief Constructor de la clase TSPBruteForce
*/
void TSPBruteForce::execute() {
  bruteForce();
  bestTripRoute_.push_back(bestTripRoute_[0]); // Agregar la ciudad de origen al final de la ruta
  printBestTrip();
}

/**
 * @brief Método que implementa el algoritmo de fuerza bruta para resolver el problema del TSP
 * @param startCity Ciudad de inicio para el recorrido
*/
void TSPBruteForce::bruteForce(const std::string &startCity) {
  // Insertar la ciudad actual en el conjunto de ciudades visitadas
  visitedCities_.insert(startCity);

  // Agregar la ciudad actual a la ruta actual
  currentRoute_.push_back(startCity);

  // Si hemos visitado todas las ciudades, calcular la distancia total de la ruta y actualizar la mejor ruta si es necesario
  if (visitedCities_.size() == numberOfCities_) {
    int currentTripPrice = calculateTotalDistance(currentRoute_, trips_);
    if (currentTripPrice < bestTripPrice_ || bestTripPrice_ == INT_MAX) {
      bestTripPrice_ = currentTripPrice;
      bestTripRoute_ = currentRoute_;
    }
  } else {
    // Recorrer todas las ciudades vecinas no visitadas
    for (const auto &trip : trips_) {
      if (trip.getCityA() == startCity && visitedCities_.find(trip.getCityB()) == visitedCities_.end()) {
        bruteForce(trip.getCityB()); // Llamada recursiva con la siguiente ciudad
        visitedCities_.erase(trip.getCityB()); // Desmarcar la ciudad visitada para explorar otras opciones
        currentRoute_.pop_back(); // Retroceder en la ruta
      } else if (trip.getCityB() == startCity && visitedCities_.find(trip.getCityA()) == visitedCities_.end()) {
        bruteForce(trip.getCityA()); // Llamada recursiva con la siguiente ciudad
        visitedCities_.erase(trip.getCityA()); // Desmarcar la ciudad visitada para explorar otras opciones
        currentRoute_.pop_back(); // Retroceder en la ruta
      }
    }
  }
}


/**
 * @brief Método que imprime la mejor ruta encontrada por el algoritmo de fuerza bruta
*/
void TSPBruteForce::printBestTrip() {
  // std::cout << "Best trip: ";
  // for (const auto &city : bestTripRoute_) {
  //   std::cout << city << " ";
  // }
  std::cout << bestTripPrice_ << std::endl;
}

/**
 * @brief Método que calcula la distancia total de una ruta
 * @param route Ruta a calcular
 * @param trips Lista de viajes disponibles
 * @return La distancia total de la ruta
*/
int TSPBruteForce::calculateTotalDistance(const std::vector<std::string>& route, const std::vector<Trip>& trips) {
  int totalDistance = 0;
  for (int i = 0; i < route.size() - 1; i++) {
    for (const auto &trip : trips) {
      if (trip.getCityA() == route[i] && trip.getCityB() == route[i + 1]) {
        totalDistance += trip.getTripPrice();

      } else if (trip.getCityB() == route[i] && trip.getCityA() == route[i + 1]) {
        totalDistance += trip.getTripPrice();
      }
    }
  }
  // Sumar el viaje de regreso a la ciudad de origen solo es un viaje
  for (const auto &trip : trips) {
    if (trip.getCityA() == route[route.size() - 1] && trip.getCityB() == route[0]) {
      totalDistance += trip.getTripPrice();
      break;
    } else if (trip.getCityB() == route[route.size() - 1] && trip.getCityA() == route[0]) {
      totalDistance += trip.getTripPrice();
      break;
    }
  }
  return totalDistance;
}

