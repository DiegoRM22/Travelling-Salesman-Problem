
#include <iostream>
#include <fstream>

#include "TSP/TSP.h"
#include "TSP-brute-force/TSP-brute-force.h"
#include "instance-generator/instance-generator.h"

int main() {
  std::string inputFileName = "example.txt";
  // Algoritmo de fuerza bruta
  TSPBruteForce tspBruteForce(inputFileName);
  tspBruteForce.printTrips();
  tspBruteForce.execute();
  return 0;

}
