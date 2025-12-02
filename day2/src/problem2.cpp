#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

#define INPUT_FILE "../res/input.txt"

std::uint64_t sum_invalid(uint64_t &start, uint64_t &end) {
  std::uint64_t sum_invalid = 0;
  for (uint64_t i = start; i <= end; i++) {
    std::string current = std::to_string(i);
    for (uint64_t j = 0; j < current.length() - 1; j++) {
      if (current.length() % (j + 1) != 0) {
        continue;
      }
      std::string_view pattern = std::string_view(current).substr(0, j + 1);
      std::stringstream compare_ss;
      while (compare_ss.str().length() < current.length()) {
        compare_ss << pattern;
      }
      if (compare_ss.str().substr(0, current.length()) == current) {
        sum_invalid += i;
        break;
      }
    }
  }
  return sum_invalid;
}

int main() {

  std::ifstream input(INPUT_FILE);
  assert(input.is_open() && "Failed to open input file.");

  std::uint64_t ans = 0;

  std::string input_value;

  std::getline(input, input_value);

  std::stringstream ss(input_value);
  std::string token;

  while (std::getline(ss, token, ',')) {
    int dash_loc = token.find('-');
    std::uint64_t start = std::stoull(token.substr(0, dash_loc));
    std::uint64_t end = std::stoull(token.substr(dash_loc + 1, token.length()));

    ans += sum_invalid(start, end);
  }

  std::cout << ans << std::endl;
  input.close();
  return 0;
}
