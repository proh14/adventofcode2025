#include <algorithm>
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
  uint64_t ans = 0;

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

  sort(ranges.begin(), ranges.end(),
       [](const Range &a, const Range &b) { return a.start < b.start; });

  Range merged_range = ranges[0];

  for (size_t i = 1; i < ranges.size(); ++i) {
    if (ranges[i].start <= merged_range.end + 1) {
      merged_range.end = std::max(merged_range.end, ranges[i].end);
    } else {
      ans += merged_range.end - merged_range.start + 1;
      merged_range = ranges[i];
    }
  }

  ans += merged_range.end - merged_range.start + 1;

  std::cout << ans << std::endl;
}
