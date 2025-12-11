#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <z3++.h>

#define INPUT_FILE "../res/input.txt"

void parse_lights(const std::string &word, std::vector<bool> &lights) {
  for (char c : word) {
    if (c == '#') {
      lights.push_back(true);
    } else if (c == '.') {
      lights.push_back(false);
    }
  }
}

void add_buttons(const std::string &word,
                 std::vector<std::vector<int>> &buttons) {
  std::vector<int> button;
  for (size_t i = 1; i < word.size() - 1; ++i) {
    if (word[i] >= '0' && word[i] <= '9') {
      button.push_back(word[i] - '0');
    }
  }
  buttons.push_back(button);
}

int main() {
  int ans = 0;

  std::ifstream input(INPUT_FILE);
  assert(input.is_open() && "Failed to open input");

  std::string line;
  while (std::getline(input, line)) {
    std::istringstream iss(line);

    std::string word;

    std::vector<bool> lights;
    std::vector<std::vector<int>> buttons;

    while (iss >> word) {
      if (word[0] == '[') {
        parse_lights(word, lights);
      }

      if (word[0] == '(') {
        add_buttons(word, buttons);
      }
    }

    z3::context c;
    z3::optimize opt(c);

    z3::expr_vector button_vars(c);
    for (size_t i = 0; i < buttons.size(); ++i) {
      z3::expr var = c.bool_const(("b" + std::to_string(i)).c_str());
      button_vars.push_back(var);
    }

    for (size_t i = 0; i < lights.size(); i++) {
      z3::expr_vector affecting_buttons(c);
      for (size_t j = 0; j < buttons.size(); j++) {
        if (std::find(buttons[j].begin(), buttons[j].end(), i) !=
            buttons[j].end()) {
          affecting_buttons.push_back(button_vars[j]);
        }
      }

      z3::expr desired_state = c.bool_val(lights[i]);

      z3::expr xor_expr = affecting_buttons[0];

      for (size_t k = 1; k < affecting_buttons.size(); k++) {
        xor_expr = xor_expr ^ affecting_buttons[k];
      }

      opt.add(desired_state == xor_expr);
    }

    z3::expr total_presses = c.int_val(0);

    for (size_t i = 0; i < button_vars.size(); i++) {
      total_presses = total_presses + button_vars[i];
    }

    opt.minimize(total_presses);

    if (opt.check() == z3::sat) {
      z3::model m = opt.get_model();
      z3::expr result = m.eval(total_presses, true);
      ans += result.get_numeral_int();
    }
  }

  std::cout << ans << std::endl;

  input.close();
  return 0;
}
