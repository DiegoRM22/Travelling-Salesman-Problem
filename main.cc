#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <atomic>

#include "TSP/TSP.h"
#include "TSP-brute-force/TSP-brute-force.h"
#include "TSP-greedy/TSP-greedy.h"
#include "TSP-dynamic-programming/TSP-dynamic-programming.h"
#include "instance-generator/instance-generator.h"

template<typename T>
void executeWithTimeout(T& algorithm, std::chrono::minutes timeout, std::atomic_bool& finished) {
  std::thread thread([&algorithm, &finished]() {
    algorithm.execute();
    finished.store(true);
  });

  auto start = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(timeout);
  auto end = start + duration;

  while (std::chrono::high_resolution_clock::now() < end && !finished.load()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Esperar un poco antes de verificar nuevamente
  }

  if (!finished.load()) {
    if (thread.joinable()) {
      thread.detach();
      std::cout << "Tiempo de ejecución excedido\n";
    }
  } else {
    thread.join(); // Si el algoritmo terminó antes, unir el hilo secundario
  }
}

int main() {
  const std::chrono::minutes kTimeLimit = std::chrono::minutes(1);
  std::vector<std::string> generatedInstanceFiles;
  InstanceGenerator instanceGenerator(4, 100, 1);
  generatedInstanceFiles.push_back(instanceGenerator.getGeneratedInstanceFile());
  InstanceGenerator instanceGenerator2(8, 100, 1);
  generatedInstanceFiles.push_back(instanceGenerator2.getGeneratedInstanceFile());
  InstanceGenerator instanceGenerator3(10, 100, 1);
  generatedInstanceFiles.push_back(instanceGenerator3.getGeneratedInstanceFile());
  // medias de tiempo
  std::chrono::duration<double> average_brute_force;
  std::chrono::duration<double> average_greedy;
  std::chrono::duration<double> average_dynamic_programming;

  for (auto inputFileName : generatedInstanceFiles) {
    std::cout << "Archivo de entrada: " << inputFileName << std::endl;
    // Algoritmo de fuerza bruta
    TSPBruteForce tspBruteForce(inputFileName);
    std::atomic_bool finished_brute_force(false);
    auto start_brute_force = std::chrono::high_resolution_clock::now();
    executeWithTimeout(tspBruteForce, kTimeLimit, finished_brute_force);
    auto end_brute_force = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_brute_force = end_brute_force - start_brute_force;
    average_brute_force += elapsed_brute_force;
    if (finished_brute_force) {
      std::cout << "Tiempo de ejecución de fuerza bruta: " << elapsed_brute_force.count() << " segundos\n";
    } else {
      std::cout << "Tiempo de ejecución de fuerza bruta: EXCESIVO\n";
    }

    std::cout << "----------------------------------------\n";

    std::cout << "Archivo de entrada: " << inputFileName << std::endl;
    // Algoritmo voraz
    TSPGreedy tspGreedy(inputFileName);
    std::atomic_bool finished_greedy(false);
    auto start_greedy = std::chrono::high_resolution_clock::now();
    executeWithTimeout(tspGreedy, kTimeLimit, finished_greedy);
    auto end_greedy = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_greedy = end_greedy - start_greedy;
    average_greedy += elapsed_greedy;
    if (finished_greedy) {
      std::cout << "Tiempo de ejecución de voraz: " << elapsed_greedy.count() << " segundos\n";
    } else {
      std::cout << "Tiempo de ejecución de voraz: EXCESIVO\n";
    }

    std::cout << "----------------------------------------\n";

    std::cout << "Archivo de entrada: " << inputFileName << std::endl;
    // Algoritmo de programación dinámica
    TSPDynamicProgramming tspDynamicProgramming(inputFileName);
    std::atomic_bool finished_dynamic_programming(false);
    auto start_dynamic_programming = std::chrono::high_resolution_clock::now();
    executeWithTimeout(tspDynamicProgramming, kTimeLimit, finished_dynamic_programming);
    auto end_dynamic_programming = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_dynamic_programming = end_dynamic_programming - start_dynamic_programming;
    average_dynamic_programming += elapsed_dynamic_programming;
    if (finished_dynamic_programming) {
      std::cout << "Tiempo de ejecución de programación dinámica: " << elapsed_dynamic_programming.count() << " segundos\n";
    } else {
      std::cout << "Tiempo de ejecución de programación dinámica: EXCESIVO\n";
    }

    std::cout << "----------------------------------------\n\n\n";
  }

  std::cout << "Tiempo promedio de ejecución de fuerza bruta: " << average_brute_force.count() / generatedInstanceFiles.size() << " segundos\n";
  std::cout << "Tiempo promedio de ejecución de voraz: " << average_greedy.count() / generatedInstanceFiles.size() << " segundos\n";
  std::cout << "Tiempo promedio de ejecución de programación dinámica: " << average_dynamic_programming.count() / generatedInstanceFiles.size() << " segundos\n";
  
  return 0;
}
