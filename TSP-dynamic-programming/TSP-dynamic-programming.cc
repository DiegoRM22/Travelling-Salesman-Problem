#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>

#include "TSP-dynamic-programming.h"

void TSPDynamicProgramming::execute() {
    // Crear una matriz de distancias con tamaño numberOfCities_ x numberOfCities_
    std::vector<std::vector<int>> distance(numberOfCities_, std::vector<int>(numberOfCities_, 0));

    // Construir la matriz de distancias a partir de trips_
    int i = 0;
    for (const auto city_i : cities_) {
        int j = 0;
        for (const auto city_j : cities_) {
          std::string cityA = city_i;
          std::string cityB = city_j;
            distance[i][j] = searchTripPrice(cityA, cityB);
            j++;
        }
        i++;
    }

    for (int i = 0; i < numberOfCities_; i++) {
        for (int j = 0; j < numberOfCities_; j++) {
            std::cout << distance[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Calcular la distancia mínima utilizando programación dinámica
    int min_distance = tsp(distance, "B", cities_);

    // Imprimir el resultado
    print_result(min_distance);
    for (int i = 0; i < numberOfCities_; i++) {
        for (int j = 0; j < numberOfCities_; j++) {
            std::cout << distance[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


int TSPDynamicProgramming::tsp(const std::vector<std::vector<int>>& distance, std::string startCity, std::set<std::string> leftCities) {
  
  if (leftCities.size() == 1) {
    std::string endCity = *leftCities.begin();
    return distance[startCity[0] - 'A'][endCity[0] - 'A'];
  } else {
    int minDistance = std::numeric_limits<int>::max();
    std::string nextCity;
    
    for (const auto& city : leftCities) {
      if (city != startCity && visitedCities_.find(city) == visitedCities_.end()) {
        std::set<std::string> newLeftCities = leftCities;
        newLeftCities.erase(city);
        int distanceToCity = distance[startCity[0] - 'A'][city[0] - 'A'];
        if (distanceToCity != 0) {
          visitedCities_.insert(city);
          int newDistance = distanceToCity + tsp(distance, city, newLeftCities);
          if (newDistance < minDistance) {
            minDistance = newDistance;
            nextCity = city;
          }
          route_.push_back(nextCity);
          visitedCities_.erase(city);
        }
      }
    }
    std::cout << "Next city: " << nextCity << std::endl;
    return minDistance;
  }
}


void TSPDynamicProgramming::print_result(int min_distance) {
  std::cout << "Minimum distance for TSP: " << min_distance << std::endl;
  std::cout << "Route: ";
  for (const auto& city : route_) {
    std::cout << city << " ";
  }
  std::cout << std::endl;
}
