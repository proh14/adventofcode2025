#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#define INPUT_FILE "../res/input.txt"

int main() {
  std::ifstream input(INPUT_FILE);
  assert(input.is_open() && "Failed to open input");

  std::string line;

  std::vector<std::pair<int, int>> coords;

  while (std::getline(input, line)) {
    std::istringstream ss(line);

    char comma;
    int x, y;
    ss >> x >> comma >> y;

    coords.push_back({x, y});
  }

  std::vector<std::uint64_t> areas;
  for (size_t i = 0; i < coords.size(); i++) {
    for (size_t j = i + 1; j < coords.size(); j++) {
      std::uint64_t area =
          (std::llabs(coords[i].first - coords[j].first) + 1) *
          (std::llabs(coords[i].second - coords[j].second) + 1);
      areas.push_back(area);
    }
  }

  sort(areas.begin(), areas.end(), std::greater<std::uint64_t>());

  std::cout << areas[0] << std::endl;

  input.close();
  return 0;
}
