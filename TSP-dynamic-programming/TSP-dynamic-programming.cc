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

  // Calcular la ruta más corta y su distancia
  std::pair<int, std::vector<int>> result = find_travelling_salesman_cycle();
  min_distance_ = result.first;
  // Imprimir el resultado
  std::cout << "Minimum distance for TSP: " << min_distance_ << std::endl;
  std::cout << "Route: ";
  for (const auto& city : result.second) {
    std::cout << city << " ";
  }
}


int TSPDynamicProgramming::tsp(const std::vector<std::vector<int>>& distance, std::string startCity, std::set<std::string> leftCities) {
  

}

std::pair<int, std::vector<int>> TSPDynamicProgramming::find_travelling_salesman_cycle() {
        min_path_.resize(1 << numberOfCities_, std::vector<int>(numberOfCities_, std::numeric_limits<int>::max()));
        min_path_last_vertex_.resize(1 << numberOfCities_, std::vector<int>(numberOfCities_, -1));
        min_path_[0][0] = 0;  // Our starting point
        
        // Iterating over sets this way guarantees we explore smaller sets first
        for(unsigned int explored_set = 0; explored_set < (1U << numberOfCities_); explored_set++) {
            for(int last_vertex = 0; last_vertex < numberOfCities_; last_vertex++)
                    if(min_path_[explored_set][last_vertex] != std::numeric_limits<int>::max()) {  // Valid state?
                for(int next_vertex = 0; next_vertex < numberOfCities_; next_vertex++)
                        if(
                            edges_[last_vertex][next_vertex] != std::numeric_limits<int>::max() // Edge exists
                         && (explored_set & (1U << next_vertex)) == 0  // We don't go back to already explored vertex
                        ) {
                    // Perform the traversal and see if we find a new shortest path/cycle to the destination state
                    const unsigned int next_set = explored_set + (1U << next_vertex);
                    const int next_cost = min_path_[explored_set][last_vertex] + edges_[last_vertex][next_vertex];
                    if(next_cost < min_path_[next_set][next_vertex]) {
                        min_path_[next_set][next_vertex] = next_cost;
                        min_path_last_vertex_[next_set][next_vertex] = last_vertex;
                    }
                }
            }
        }
        int result_cost = min_path_[(1 << numberOfCities_) - 1][0];
        std::vector<int> cycle = {0};
        if (result_cost != std::numeric_limits<int>::max()) {
            int cur_state = (1 << numberOfCities_) - 1;
            int cur_vertex = 0;
            
            while(cur_state > 0) {  // Traverse back the minimum cycle
                int prev_vertex = min_path_last_vertex_[cur_state][cur_vertex];
                cur_state -= (1 << cur_vertex);
                cur_vertex = prev_vertex;
                cycle.push_back(cur_vertex);
            }
            std::reverse(cycle.begin(), cycle.end());
        }
        return std::make_pair(min_path_[(1 << numberOfCities_) - 1][0], cycle);  // The state corresponding to having traversed the cycle
    }



void TSPDynamicProgramming::print_result(int min_distance) {
  std::cout << "Minimum distance for TSP: " << min_distance << std::endl;
  std::cout << "Route: ";
  for (const auto& city : route_) {
    std::cout << city << " ";
  }
  std::cout << std::endl;
}
