#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <unordered_map>

#define INPUT_FILE "../res/input.txt"

#define WIDTH 141
#define HEIGHT 142

char grid[HEIGHT][WIDTH];

typedef std::pair<int, int> pair_int;

struct pair_hash {
  std::size_t operator()(const pair_int &p) const {
    auto h1 = std::hash<int>{}(p.first);
    auto h2 = std::hash<int>{}(p.second);
    return h1 ^ (h2 << 1);
  }
};

std::unordered_map<pair_int, std::uint64_t, pair_hash> memo;
std::uint64_t start_from(int sx, int sy) {
  std::uint64_t ans = 0;
  for (int y = sy; y < HEIGHT; ++y) {
    if (grid[y][sx] != '^') {
      continue;
    }

    auto it = memo.find(std::make_pair(sx, sy));

    if (it != memo.end()) {
      return it->second;
    }

    if (sx + 1 < WIDTH)
      ans += start_from(sx + 1, y);

    if (sx - 1 >= 0)
      ans += start_from(sx - 1, y);

    memo.emplace(std::make_pair(sx, sy), ans);
    return ans;
  }
  return 1;
}

int main() {
  std::ifstream input(INPUT_FILE);
  assert(input.is_open() && "Failed to open input file.");

  int startX = -1;
  int startY = -1;

  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      input >> grid[y][x];
      if (grid[y][x] == 'S') {
        startX = x;
        startY = y;
      }
    }
  }

  std::uint64_t ans = start_from(startX, startY + 1);

  std::cout << ans << std::endl;

  input.close();
  return 0;
}
