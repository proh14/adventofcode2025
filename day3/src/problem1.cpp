#include <cassert>
#include <fstream>
#include <iostream>

#define INPUT_FILE "../res/input.txt"

int main() {

  std::ifstream input(INPUT_FILE);

  std::string current;

  int ans = 0;

  while (input >> current) {
    int biggest = 0;
    int second_biggest = 0;

    size_t biggest_index = -1;

    for (size_t i = 0; i < current.size(); ++i) {
      if (i != current.size() - 1 && current[i] - '0' > biggest) {
        biggest = current[i] - '0';
        biggest_index = i;
      }
    }

    for (size_t i = biggest_index + 1; i < current.size(); ++i) {
      if (current[i] - '0' > second_biggest) {
        second_biggest = current[i] - '0';
      }
    }

    ans += biggest * 10 + second_biggest;
    std::cout << biggest * 10 + second_biggest << std::endl;
  }

  std::cout << ans << std::endl;

  return 0;
}
