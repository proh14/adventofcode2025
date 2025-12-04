#include <cassert>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>

#define INPUT_FILE "../res/input.txt"
#define ITERATIONS 12

std::uint64_t biggest_nums(const std::string &s, int first, int current_it) {
  int biggest = 0;
  size_t biggest_index = -1;
  for (size_t i = first; i < s.size(); ++i) {
    if ((current_it == ITERATIONS - 1 ||
         i <= s.size() - 1 - ((ITERATIONS - 1) - current_it)) &&
        s[i] - '0' > biggest) {
      biggest = s[i] - '0';
      biggest_index = i;
    }
  }
  if (current_it == ITERATIONS - 1) {
    return biggest;
  }
  return biggest * pow(10, ITERATIONS - 1 - current_it) +
         biggest_nums(s, biggest_index + 1, current_it + 1);
}

int main() {

  std::ifstream input(INPUT_FILE);

  std::string current;

  std::uint64_t ans = 0;

  while (input >> current) {
    uint64_t x = biggest_nums(current, 0, 0);
    std::cout << x << std::endl;
    ans += x;
  }

  std::cout << ans << std::endl;

  return 0;
}
