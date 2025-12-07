#include <bits/stdc++.h>
#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

#define INPUT_FILE "../res/input.txt"

std::uint64_t do_stack_operations(std::stack<int> &numbers, char operation) {
  std::uint64_t result = numbers.top();
  numbers.pop();

  assert(operation == '+' || operation == '*');

  while (!numbers.empty()) {
    int next_number = numbers.top();
    numbers.pop();
    if (operation == '+') {
      result += next_number;
    } else if (operation == '*') {
      result *= next_number;
    }
  }
  return result;
}

int main() {
  std::uint64_t ans = 0;
  std::ifstream input(INPUT_FILE);
  assert(input.is_open() && "Failed to open input");
  std::vector<std::string> lines;

  for (std::string line; std::getline(input, line);) {
    lines.push_back(line);
  }

  int height = lines.size();
  int width = lines[0].size();

  int cur_col = width - 1;

  std::stack<int> numbers;
  char operation = ' ';
  while (cur_col >= 0) {
    bool all_spaces = true;
    for (int row = 0; row < height; ++row) {
      if (lines[row][cur_col] != ' ') {
        all_spaces = false;
        break;
      }
    }

    if (all_spaces) {
      ans += do_stack_operations(numbers, operation);
      operation = ' ';
      cur_col--;
      continue;
    }

    int number = 0;
    for (int row = 0; row < height; ++row) {
      char c = lines[row][cur_col];
      if (isdigit(c)) {
        number = number * 10 + (c - '0');
      }
      if (c == '*' || c == '+') {
        operation = c;
      }
    }
    numbers.push(number);
    cur_col--;
  }
  ans += do_stack_operations(numbers, operation);

  std::cout << ans << std::endl;
}
