#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <string_view>

#define INPUT_FILE "../res/input.txt"

std::uint64_t sum_invalid(uint64_t &start, uint64_t &end) {
  std::uint64_t sum_invalid = 0;
  for (uint64_t i = start; i <= end; i++) {
    std::string current = std::to_string(i);
    if (current.length() % 2 != 0) {
      continue;
    }

    std::string_view view(current);

    int mid = view.length() / 2;

    if (view.substr(0, mid) == view.substr(mid, current.length())) {
      sum_invalid += i;
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
