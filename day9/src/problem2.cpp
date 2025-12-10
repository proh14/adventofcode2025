#include <algorithm>
#include <cassert>
#include <cstdint>
#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

#define INPUT_FILE "../res/input_test.txt"

std::unordered_map<int, int> x_map;
std::unordered_map<int, int> y_map;

char **grid;
int grid_width;
int grid_height;

void compress_x_coordinates(const std::vector<std::pair<int, int>> &coords) {
  std::vector<int> x_values;

  for (const auto &coord : coords) {
    x_values.push_back(coord.first);
  }

  std::sort(x_values.begin(), x_values.end());
  x_values.erase(std::unique(x_values.begin(), x_values.end()), x_values.end());

  for (size_t i = 0; i < x_values.size(); ++i) {
    x_map[x_values[i]] = i;
  }
}

void compress_y_coordinates(const std::vector<std::pair<int, int>> &coords) {
  std::vector<int> y_values;

  for (const auto &coord : coords) {
    y_values.push_back(coord.second);
  }

  std::sort(y_values.begin(), y_values.end());
  y_values.erase(std::unique(y_values.begin(), y_values.end()), y_values.end());

  for (size_t i = 0; i < y_values.size(); ++i) {
    y_map[y_values[i]] = i;
  }
}

std::pair<int, int> get_coords(const std::unordered_map<int, int> &x_map,
                               const std::unordered_map<int, int> &y_map,
                               int original_x, int original_y) {
  int compressed_x = x_map.at(original_x);
  int compressed_y = y_map.at(original_y);
  return {compressed_x, compressed_y};
}

void make_bounds(std::vector<std::pair<int, int>> coords) {
  for (size_t i = 0; i < coords.size(); ++i) {
    auto [x1, y1] = get_coords(x_map, y_map, coords[i].first, coords[i].second);
    auto [x2, y2] =
        get_coords(x_map, y_map, coords[(i + 1) % coords.size()].first,
                   coords[(i + 1) % coords.size()].second);

    int dx = x2 - x1;
    int dy = y2 - y1;

    int dir_x = (dx == 0) ? 0 : (dx >= 0 ? 1 : -1);
    int dir_y = (dy == 0) ? 0 : (dy >= 0 ? 1 : -1);

    for (int x = x1; x != x2; x += dir_x) {
      grid[y1][x] = 'X';
    }

    for (int y = y1; y != y2; y += dir_y) {
      grid[y][x1] = 'X';
    }
  }
}

void flood_fill() {
  std::deque<std::pair<int, int>> q;
  q.push_back({grid_width / 2, grid_height / 2});
  grid[grid_height / 2][grid_width / 2] = '.';

  const std::vector<std::pair<int, int>> directions = {
      {1, 0}, {-1, 0}, {0, 1}, {0, -1}};

  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop_front();

    for (const auto &[dx, dy] : directions) {
      int nx = x + dx;
      int ny = y + dy;

      if (nx >= 0 && nx < grid_width && ny >= 0 && ny < grid_height &&
          grid[ny][nx] == ' ') {
        grid[ny][nx] = '.';
        q.push_back({nx, ny});
      }
    }
  }
}

bool is_rectangle_possible(std::pair<int, int> &corner1,
                           std::pair<int, int> &corner2) {

  auto [x1, y1] = get_coords(x_map, y_map, corner1.first, corner1.second);
  auto [x2, y2] = get_coords(x_map, y_map, corner2.first, corner2.second);

  for (int x = std::min(x1, x2); x <= std::max(x1, x2); ++x) {
    if (grid[y1][x] == ' ' || grid[y2][x] == ' ') {
      return false;
    }
  }
  for (int y = std::min(y1, y2); y <= std::max(y1, y2); ++y) {
    if (grid[y][x1] == ' ' || grid[y][x2] == ' ') {
      return false;
    }
  }
  return true;
}

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

  compress_x_coordinates(coords);
  compress_y_coordinates(coords);

  grid_width = x_map.size();
  grid_height = y_map.size();

  grid = new char *[grid_height];
  grid[0] = new char[grid_height * grid_width];
  for (int i = 1; i < grid_height; i++)
    grid[i] = grid[0] + i * grid_width;

  std::fill(grid[0], grid[0] + grid_width * grid_height, ' ');

  make_bounds(coords);

  flood_fill();

  std::vector<std::uint64_t> areas;
  for (size_t i = 0; i < coords.size(); i++) {
    for (size_t j = i + 1; j < coords.size(); j++) {
      if (!is_rectangle_possible(coords[i], coords[j])) {
        continue;
      }

      std::uint64_t area =
          (std::llabs(coords[i].first - coords[j].first) + 1) *
          (std::llabs(coords[i].second - coords[j].second) + 1);
      areas.push_back(area);
    }
  }

  std::sort(areas.begin(), areas.end(), std::greater<std::uint64_t>());

  std::cout << areas[0] << std::endl;

  input.close();
  return 0;
}
