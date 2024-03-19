
#include "TSP-dynamic-programming.h"

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>


/**
 * @brief Ejecuta el algoritmo de programación dinámica para resolver el problema del vendedor viajero (TSP).
 */
void TSPDynamicProgramming::execute() {
  // Establecer las aristas
  edges_.resize(numberOfCities_, std::vector<int>(numberOfCities_, std::numeric_limits<int>::max()));
  for (const auto &trip : trips_) {
    int cityA = std::distance(cities_.begin(), cities_.find(trip.getCityA()));
    int cityB = std::distance(cities_.begin(), cities_.find(trip.getCityB()));
    edges_[cityA][cityB] = searchTripPrice(trip.getCityA(), trip.getCityB());
    edges_[cityB][cityA] = searchTripPrice(trip.getCityA(), trip.getCityB());
    edges_[cityA][cityA] = 0;
    edges_[cityB][cityB] = 0;
  }

  std::string startCity = "A";
  int startIndex = std::distance(cities_.begin(), cities_.find(startCity));
  std::pair<int, std::vector<int>> result = solve(startIndex);
  print_result(result.first);
  std::vector<int> routeIndexes = result.second;
  for (const auto &index : routeIndexes) {
    route_.push_back(*std::next(cities_.begin(), index));
  }
  // std::cout << "Route: ";
  // for (const auto &city : route_) {
  //   std::cout << city << " ";
  // }
  // std::cout << std::endl;
}

/**
 * @brief Resuelve el problema del vendedor viajero (TSP) utilizando programación dinámica.
 * @param startIndex El índice del punto de partida.
 * @return Un par que contiene el costo mínimo del ciclo y la secuencia de ciudades que forman el ciclo mínimo.
 */
std::pair<int, std::vector<int>> TSPDynamicProgramming::solve(int startIndex) {
  // Se redimensionan las matrices para almacenar los costos mínimos y los vértices previos para cada conjunto de ciudades visitadas.
  min_path_.resize(1 << numberOfCities_, std::vector<int>(numberOfCities_, std::numeric_limits<int>::max()));
  min_path_last_vertex_.resize(1 << numberOfCities_, std::vector<int>(numberOfCities_, -1));
  
  // Se inicializa el costo mínimo para el conjunto vacío de ciudades visitadas con el punto de partida especificado por 'startIndex'.
  min_path_[0][startIndex] = 0;  // Nuestro punto de partida

  // Se itera sobre todos los subconjuntos de ciudades visitadas, comenzando desde el conjunto vacío.
  for(unsigned int explored_set = 0; explored_set < (1U << numberOfCities_); explored_set++) {
    for(int last_vertex = 0; last_vertex < numberOfCities_; last_vertex++)
      if(min_path_[explored_set][last_vertex] != std::numeric_limits<int>::max()) {
        for(int next_vertex = 0; next_vertex < numberOfCities_; next_vertex++)
          if(
            edges_[last_vertex][next_vertex] != std::numeric_limits<int>::max() &&  // El borde existe
            (explored_set & (1U << next_vertex)) == 0  // No volvemos a un vértice ya explorado
          ) {
            const unsigned int next_set = explored_set + (1U << next_vertex);
            const int next_cost = min_path_[explored_set][last_vertex] + edges_[last_vertex][next_vertex];
            if(next_cost < min_path_[next_set][next_vertex]) {
              min_path_[next_set][next_vertex] = next_cost;
              min_path_last_vertex_[next_set][next_vertex] = last_vertex;
            }
          }
      }
  }
  
  // Se calcula el costo del resultado final y se construye el ciclo mínimo si se encuentra una solución factible.
  int result_cost = min_path_[(1 << numberOfCities_) - 1][startIndex];
  std::vector<int> cycle = {startIndex};
  if (result_cost != std::numeric_limits<int>::max()) {
    int cur_state = (1 << numberOfCities_) - 1;
    int cur_vertex = startIndex;
    
    // Se construye el ciclo mínimo recorriendo hacia atrás el camino más corto.
    while(cur_state > 0) {
      int prev_vertex = min_path_last_vertex_[cur_state][cur_vertex];
      cur_state -= (1 << cur_vertex);
      cur_vertex = prev_vertex;
      cycle.push_back(cur_vertex);
    }
    std::reverse(cycle.begin(), cycle.end());
  }
  
  // Se devuelve un par que contiene el costo mínimo del ciclo y la secuencia de ciudades que forman el ciclo mínimo.
  return std::make_pair(min_path_[(1 << numberOfCities_) - 1][startIndex], cycle);
}

/**
 * @brief Imprime el resultado del problema del vendedor viajero (TSP).
 * @param min_distance El costo mínimo del ciclo.
 */
void TSPDynamicProgramming::print_result(int min_distance) {
  // std::cout << "Best trip: ";
  // for (const auto &city : route_) {
  //   std::cout << city << " ";
  // }
  std::cout << min_distance << std::endl;
}
