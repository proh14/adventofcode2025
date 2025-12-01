#include <cassert>
#include <fstream>
#include <iostream>

#define INPUT_FILE "../res/input.txt"

int main() {

  std::ifstream input(INPUT_FILE);

  int dialnum_now = 50;
  char dir;
  int amount;
  int ans = 0;
  int multiplier = 0;

  assert(input.is_open() && "Failed to open input file.");

  while (input >> dir >> amount) {
    if (dir == 'R')
      multiplier = 1;
    else if (dir == 'L')
      multiplier = -1;

    for (int i = 1; i <= amount; i++) {
      int temp_value =
          ((dialnum_now - multiplier * (amount - i)) % 100 + 100) % 100;
      if (temp_value == 0)
        ans++;
    }

    dialnum_now = ((dialnum_now - multiplier * amount) % 100 + 100) % 100;
  }

  std::cout << ans << std::endl;

  input.close();
  return 0;
}
