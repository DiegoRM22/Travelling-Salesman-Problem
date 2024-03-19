
#include "TSP-dynamic-programming.h"

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>


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
  std::cout << "Route: ";
  for (const auto &city : route_) {
    std::cout << city << " ";
  }
  std::cout << std::endl;

}

std::pair<int, std::vector<int>> TSPDynamicProgramming::solve(int startIndex) {
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
  return std::make_pair(min_path_[(1 << numberOfCities_) - 1][0], cycle);
}

void TSPDynamicProgramming::print_result(int min_distance) {
  std::cout << "Best trip: ";
  for (const auto &city : route_) {
    std::cout << city << " ";
  }
  std::cout << "with a price of " << min_distance << std::endl;
}
