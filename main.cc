
#include <iostream>
#include <fstream>

#include "TSP/TSP.h"
#include "TSP-brute-force/TSP-brute-force.h"
#include "TSP-greedy/TSP-greedy.h"
#include "TSP-dynamic-programming/TSP-dynamic-programming.h"
#include "instance-generator/instance-generator.h"

int main() {
  std::string inputFileName = "example.txt";
  // Algoritmo de fuerza bruta
  // TSPBruteForce tspBruteForce(inputFileName);
  // tspBruteForce.printTrips();
  // tspBruteForce.execute();

  // // Algoritmo voraz
  // TSPGreedy tspGreedy(inputFileName);
  // tspGreedy.printTrips();
  // tspGreedy.execute();

  // // Algoritmo de programación dinámica
  TSPDynamicProgramming tspDynamicProgramming(inputFileName);
  tspDynamicProgramming.printTrips();
  tspDynamicProgramming.execute();
  

  return 0;

}
