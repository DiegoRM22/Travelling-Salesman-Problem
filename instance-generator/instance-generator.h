
#ifndef INSTANCE_GENERATOR_H
#define INSTANCE_GENERATOR_H

#include <iostream>
#include <vector>

class InstanceGenerator {
  public:
   InstanceGenerator(int numberOfCities, int maxTripPrice, int numberOfInstances);
   std::string getGeneratedInstanceFile() const { return generatedInstanceFiles_.back(); }
  private:
   int instanceNumber_ = 1;
   std::vector<std::string> generatedInstanceFiles_;
};

#endif