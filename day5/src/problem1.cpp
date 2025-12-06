#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define INPUT_FILE "../res/input.txt"

struct Range {
  std::uint64_t start;
  std::uint64_t end;
};

int main() {
  int ans = 0;

  std::ifstream input(INPUT_FILE);
  assert(input.is_open() && "Failed to open file");

  std::string line;
  std::vector<Range> ranges;

  while (std::getline(input, line) && line != "") {
    std::string start;
    std::string end;

    int pos = line.find('-');

    start = line.substr(0, pos);
    end = line.substr(pos + 1, line.size() - pos - 1);

    Range range;
    range.start = std::stoull(start);
    range.end = std::stoull(end);

    ranges.push_back(range);
  }

  while ((input >> line)) {
    std::uint64_t val = std::stoull(line);

    for (size_t i = 0; i < ranges.size(); i++) {
      if (ranges[i].start <= val && ranges[i].end >= val) {
        ans++;
        break;
      }
    }
  }
  std::cout << ans << std::endl;
}
