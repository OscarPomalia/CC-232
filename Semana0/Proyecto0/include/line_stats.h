#ifndef CC232_LINE_STATS_H
#define CC232_LINE_STATS_H

#include <cstddef>
#include <string>
#include <vector>

namespace cc232 {

struct LineSummary {
    std::size_t total_lines{};
    std::size_t nonempty_lines{};
    std::size_t total_chars{};
    std::size_t longest_line_length{};
};

LineSummary summarize_lines(const std::vector<std::string>& lines);
std::size_t count_lines_longer_than(const std::vector<std::string>& lines, std::size_t limit);

}  // namespace cc232

#endif
