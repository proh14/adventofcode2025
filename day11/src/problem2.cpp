#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

#define INPUT_FILE "../res/input.txt"

std::unordered_map<std::string, std::vector<std::string>> key_map;

std::unordered_map<std::string, std::uint64_t> memo;
std::uint64_t number_of_ways(std::string key, bool dac = false,
                             bool fft = false) {
  if (key == "out") {
    return dac && fft ? 1 : 0;
  }

  if (key == "dac")
    dac = true;

  if (key == "fft")
    fft = true;

  std::string memo_key = key + "|" + (dac ? "1" : "0") + (fft ? "1" : "0");

  if (memo.find(memo_key) != memo.end()) {
    return memo[memo_key];
  }

  std::uint64_t total_ways = 0;
  for (const std::string &word : key_map[key]) {
    total_ways += number_of_ways(word, dac, fft);
  }

  memo[memo_key] = total_ways;

  return total_ways;
}

int main() {
  std::uint64_t ans = 0;

  std::ifstream input(INPUT_FILE);
  assert(input.is_open() && "Failed to open input");

  std::string line;

  while (std::getline(input, line)) {
    std::istringstream iss(line);

    std::string key;

    iss >> key;

    key = key.substr(0, key.size() - 1);

    std::string word;

    while (iss >> word) {
      key_map[key].push_back(word);
    }
  }

  ans = number_of_ways("svr");

  std::cout << ans << std::endl;

  return 0;
}
