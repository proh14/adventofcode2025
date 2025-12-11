#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

#define INPUT_FILE "../res/input.txt"

std::unordered_map<std::string, std::vector<std::string>> key_map;

std::unordered_map<std::string, int> memo;
int number_of_ways(std::string key) {
  if (key == "out") {
    return 1;
  }

  if (memo.find(key) != memo.end()) {
    return memo[key];
  }

  int total_ways = 0;
  for (const std::string &word : key_map[key]) {
    total_ways += number_of_ways(word);
  }
  memo[key] = total_ways;

  return total_ways;
}

int main() {
  int ans = 0;

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

  ans = number_of_ways("you");

  std::cout << ans << std::endl;

  return 0;
}
