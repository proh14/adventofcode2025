#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#define INPUT_FILE "../res/input.txt"

struct Operation {
  char type;
  std::stack<int> values;
};

std::uint64_t do_operation(Operation &op) {
  std::uint64_t ans = op.values.top();
  op.values.pop();

  while (!op.values.empty()) {
    int value = op.values.top();
    op.values.pop();
    if (op.type == '+')
      ans += value;
    if (op.type == '*')
      ans *= value;
  }
  return ans;
}

int main() {
  std::uint64_t ans = 0;
  std::ifstream input(INPUT_FILE);
  assert(input.is_open() && "Failed to open input");

  std::string line;

  std::vector<Operation> operations;

  std::getline(input, line);
  std::stringstream ss(line);

  std::string num;
  while (ss >> num) {
    Operation op;
    op.values.push(std::stoi(num));
    operations.push_back(op);
  }

  while (std::getline(input, line)) {
    std::stringstream ss(line);
    int current_op = 0;
    while (ss >> num) {
      if (num == "+" || num == "*") {
        operations[current_op].type = num[0];
        ans += do_operation(operations[current_op]);
        current_op++;
        continue;
      }
      operations[current_op].values.push(std::stoi(num));
      current_op++;
    }
  }

  std::cout << ans << std::endl;
}
