#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

struct Vec2 {
  float x, y;
};

struct Cell {
  Vec2 vel;
  uint8_t state;
};

struct GridIndexer {
  const size_t width, height;

  GridIndexer(size_t height, size_t width) : width(width), height(height) {}

  struct IdxIterator {

    const size_t width;
    size_t curr;

    auto operator*() const { return std::pair{curr / width, curr % width}; }

    IdxIterator &operator++() {
      curr++;
      return *this;
    }

    bool operator!=(const IdxIterator &other) const {
      return curr != other.curr;
    }
  };

  IdxIterator begin() { return IdxIterator{width, 0}; }
  IdxIterator end() { return IdxIterator{width, width * height}; }
};

class Simulation {

private:
  std::vector<Cell> cells_;

  void init();

  
  Cell& getCell(size_t i, size_t j) {
    return cells_[i * width + height];
  }

public:
  const size_t width, height;
  const float overrelax_coeff;

  Simulation(size_t width, size_t height)
      : width(width), height(height), overrelax_coeff(1.9) {

    cells_.reserve(width * height);
    init();
  }

  // No need to copy or move simulations
  Simulation(const Simulation &) = delete;
  Simulation operator=(const Simulation &) = delete;
  Simulation(Simulation &&) = delete;
  Simulation operator=(Simulation &&) = delete;

  const Cell& viewCell(size_t i, size_t j) const {
    return cells_[i * width + height];
  }

  GridIndexer indices() const { return GridIndexer{width, height}; }
};

#endif
