#include <iostream>
#include <fstream>
#include <ctime> // Para usar srand()

#include "instance-generator.h"

// Función para comprobar la existencia del archivo y obtener su nombre
std::string getInstanceFileName(int numberOfCities, int instanceNumber) {
  std::string instanceFilePath;
  bool fileExists = false;

  do {
    instanceFilePath = "./" + std::to_string(numberOfCities) + "nodes-" + std::to_string(instanceNumber) + ".txt";
    std::ifstream file(instanceFilePath);
    fileExists = file.good();
    file.close();
    if (fileExists) {
      instanceNumber++;
    }
  } while (fileExists);

  return instanceFilePath;
}

/**
 * @brief Constructor de la clase InstanceGenerator
*/
InstanceGenerator::InstanceGenerator(int numberOfCities, int maxTripPrice, int numberOfInstances) {
  srand(time(NULL)); // Inicializa la semilla para generar números aleatorios

  int numberOfInstance = instanceNumber_;

  std::string instanceFilePath = getInstanceFileName(numberOfCities, numberOfInstance);
  const int asciiA = 65;

  for (int instance = 0; instance < numberOfInstances; instance++) {
    std::ofstream instanceFile(instanceFilePath);
    instanceFile << numberOfCities << std::endl;
    for (int cityA = 0; cityA < numberOfCities; cityA++) {
      for (int cityB = cityA + 1; cityB < numberOfCities; cityB++) { // Comenzar desde cityA + 1 para evitar duplicados
        instanceFile << static_cast<char>(asciiA + cityA) << " " << static_cast<char>(asciiA + cityB) << " " << rand() % maxTripPrice + 1 << std::endl;
      }
    }
    instanceFile.close();
    generatedInstanceFiles_.push_back(instanceFilePath);
    instanceNumber_++;
    instanceFilePath = getInstanceFileName(numberOfCities, instanceNumber_);
  }
  instanceNumber_++; // Incrementa el número de instancia para la próxima vez.
}
