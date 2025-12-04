#include <cassert>
#include <fstream>
#include <iostream>

#define INPUT_FILE "../res/input.txt"

#define GRID_WIDTH 140
#define GRID_HEIGHT 140

char grid[GRID_HEIGHT][GRID_WIDTH];

bool is_roll_valid(int x, int y) {
  int adj_rolls = 0;
  for (int dx = -1; dx <= 1; dx++) {
    for (int dy = -1; dy <= 1; dy++) {
      int nx = x + dx;
      int ny = y + dy;

      if (nx < 0 || nx >= GRID_WIDTH || ny < 0 || ny >= GRID_HEIGHT ||
          (dx == 0 && dy == 0))
        continue;

      if (grid[ny][nx] == '@')
        adj_rolls++;

      if (adj_rolls >= 4)
        return false;
    }
  }
  return true;
}

void fill_grid(std::ifstream &file) {
  for (int i = 0; i < GRID_HEIGHT; ++i) {
    for (int j = 0; j < GRID_WIDTH; ++j) {
      file >> grid[i][j];
    }
  }
}

int main() {

  int ans = 0;

  std::ifstream input(INPUT_FILE);
  assert(input.is_open() && "Failed to open input");
  fill_grid(input);

  for (int y = 0; y < GRID_HEIGHT; y++) {
    for (int x = 0; x < GRID_WIDTH; x++) {
      if (grid[y][x] == '@') {
        if (is_roll_valid(x, y))
          ans++;
      }
    }
  }

  std::cout << ans << std::endl;

  input.close();
  return 0;
}
