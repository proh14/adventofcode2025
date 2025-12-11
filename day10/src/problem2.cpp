#include <algorithm>
#include <bits/stdc++.h>
#include <cassert>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <z3++.h>

#define INPUT_FILE "../res/input.txt"

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

void parse_jolts(const std::string &word, std::vector<int> &jolts) {

  int current_jolt = 0;
  for (size_t i = 0; i < word.size(); ++i) {
    if (isdigit(word[i])) {
      current_jolt = current_jolt * 10 + (word[i] - '0');
    } else if (word[i] == ',' || word[i] == '}') {
      jolts.push_back(current_jolt);
      current_jolt = 0;
    }
  }
}

int main() {
  int ans = 0;

  std::ifstream input(INPUT_FILE);
  assert(input.is_open() && "Failed to open input");

  std::string line;
  while (std::getline(input, line)) {
    std::istringstream iss(line);

    std::string word;

    std::vector<std::vector<int>> buttons;
    std::vector<int> jolts;

    while (iss >> word) {
      if (word[0] == '{') {
        parse_jolts(word, jolts);
      }

      if (word[0] == '(') {
        add_buttons(word, buttons);
      }
    }

    z3::context c;
    z3::optimize opt(c);

    z3::expr_vector button_vars(c);
    for (size_t i = 0; i < buttons.size(); ++i) {
      z3::expr var = c.int_const(("b" + std::to_string(i)).c_str());
      button_vars.push_back(var);
    }

    for (size_t i = 0; i < jolts.size(); ++i) {
      z3::expr_vector affecting_buttons(c);
      for (size_t j = 0; j < buttons.size(); ++j) {
        if (std::find(buttons[j].begin(), buttons[j].end(), i) !=
            buttons[j].end()) {
          affecting_buttons.push_back(button_vars[j]);
          opt.add(button_vars[j] >= 0);
        }
      }
      z3::expr sum = z3::sum(affecting_buttons);
      z3::expr desired_jolts = c.int_val(jolts[i]);

      opt.add(sum == desired_jolts);
    }

    z3::expr total_presses = c.int_val(0);

    for (size_t i = 0; i < button_vars.size(); ++i) {
      total_presses = total_presses + button_vars[i];
    }

    opt.minimize(total_presses);

    if (opt.check() == z3::sat) {
      z3::model m = opt.get_model();
      ans += m.eval(total_presses).get_numeral_int();
    }
  }

  std::cout << ans << std::endl;

  input.close();
  return 0;
}
