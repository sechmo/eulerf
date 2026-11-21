#include "simulation.h"


void Simulation::init() {

  for (auto [i,j] : indices() ) {

    Cell& c = getCell(i,j);

    c.state = 1;
    c.vel = {1.0, 1.0};

  }

}
