#include "simulation.h"

void Simulation::init() {

   for (auto [i, j] : indices()) {

      cells_.push_back({.vel = {1.0, 1.0}, .state = 1});
   }
}
