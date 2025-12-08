#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

#define INPUT_FILE "../res/input.txt"

#define CONNECTIONS 1000

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
  DSU(int n) : parent(n), size(n, 1) {
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

  for (int i = 0; i < CONNECTIONS; i++) {
    Distance d = distances[i];
    dsu.unite(d.a_idx, d.b_idx);
  }

  std::unordered_map<int, int> group_sizes;
  for (size_t i = 0; i < coords.size(); i++) {
    int root = dsu.find(i);
    group_sizes[root]++;
  }

  std::vector<int> sizes;
  for (const auto &pair : group_sizes) {
    sizes.push_back(pair.second);
  }
  sort(sizes.begin(), sizes.end(), std::greater<int>());

  ans = sizes[0] * sizes[1] * sizes[2];

  std::cout << ans << std::endl;
}
