#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#define INPUT_FILE "../res/input.txt"
#define MAX_INDEX 6

int main() {
  std::ifstream input(INPUT_FILE);
  assert(input.is_open() && "Failed to open input");

  int ans = 0;

  std::vector<int> squares;

  int current_index = 0;

  std::string line;
  int square = 0;

  while (current_index < MAX_INDEX && std::getline(input, line)) {
    if (line == "\n" || line.empty()) {
      current_index++;
      squares.push_back(square);
      square = 0;
      continue;
    }

    if (line[line.size() - 1] == ':')
      continue;

    for (char c : line) {
      if (c == '#') {
        square++;
      }
    }
  }

  while (std::getline(input, line)) {
    std::istringstream iss(line);

    std::string word;
    iss >> word;
    word = word.substr(0, word.size() - 1);

    int width = std::stoi(word.substr(0, word.find('x')));
    int height = std::stoi(word.substr(word.find('x') + 1));
    int area = width * height;

    int needed_squares = 0;
    int index = 0;

    int number;

    while (iss >> number && index < MAX_INDEX) {
      needed_squares += squares[index] * number;
    }

    if (area >= needed_squares) {
      ans++;
    }
  }

  std::cout << ans << std::endl;

  return 0;
}
