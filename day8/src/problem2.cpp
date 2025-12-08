#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

#define INPUT_FILE "../res/input.txt"

struct Coord {
  int x, y, z;
  Coord(int x, int y, int z) : x(x), y(y), z(z) {}
  Coord() : x(0), y(0), z(0) {}

  bool operator==(const Coord &other) const {
    return x == other.x && y == other.y && z == other.z;
  }
};

struct DSU {
  std::vector<int> parent, size;
  int count;
  DSU(int n) : parent(n), size(n, 1), count(n) {
    for (int i = 0; i < n; i++)
      parent[i] = i;
  }

  int find(int a) {
    if (parent[a] != a)
      parent[a] = find(parent[a]);
    return parent[a];
  }

  void unite(int a, int b) {
    int rootA = find(a);
    int rootB = find(b);
    if (rootA != rootB) {
      if (size[rootA] < size[rootB])
        std::swap(rootA, rootB);
      parent[rootB] = rootA;
      size[rootA] += size[rootB];
      count--;
    }
  }
};

double distance(Coord a, Coord b) {
  return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2) +
                   std::pow(a.z - b.z, 2));
}

struct Distance {
  int a_idx;
  int b_idx;
  double dist;
  Distance(int a_idx, int b_idx, double dist)
      : a_idx(a_idx), b_idx(b_idx), dist(dist) {}
};

int main() {
  std::ifstream input(INPUT_FILE);
  int ans = 0;
  assert(input.is_open() && "Failed to open input");

  std::vector<Coord> coords;

  std::string line;

  while (std::getline(input, line)) {
    std::istringstream iss(line);
    int x, y, z;
    char comma;
    iss >> x >> comma >> y >> comma >> z;
    coords.push_back(Coord(x, y, z));
  }

  std::vector<Distance> distances;

  for (size_t i = 0; i < coords.size(); i++) {
    for (size_t j = i + 1; j < coords.size(); j++) {
      double dist = distance(coords[i], coords[j]);
      distances.push_back(Distance(i, j, dist));
    }
  }

  std::sort(distances.begin(), distances.end(),
            [](Distance a, Distance b) { return a.dist < b.dist; });

  DSU dsu(coords.size());

  for (const auto &d : distances) {
    dsu.unite(d.a_idx, d.b_idx);
    if (dsu.count == 1) {
      ans = coords[d.a_idx].x * coords[d.b_idx].x;
      break;
    }
  }

  std::cout << ans << std::endl;
}
