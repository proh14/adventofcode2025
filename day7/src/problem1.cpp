#include <cassert>
#include <fstream>
#include <iostream>

#define INPUT_FILE "../res/input.txt"

#define WIDTH 141
#define HEIGHT 142

char grid[HEIGHT][WIDTH];
int ans = 0;

void start_from(int sx, int sy) {
  for (int y = sy; y < HEIGHT; ++y) {
    if (grid[y][sx] == '|')
      return;

    if (grid[y][sx] != '^') {
      grid[y][sx] = '|';
      continue;
    }

    ans++;

    if (sx + 1 < WIDTH && grid[y][sx + 1] != '|')
      start_from(sx + 1, y);

    if (sx - 1 >= 0 && grid[y][sx - 1] != '|')
      start_from(sx - 1, y);

    return;
  }
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

  start_from(startX, startY + 1);

  std::cout << ans << std::endl;

  input.close();
  return 0;
}
