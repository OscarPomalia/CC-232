#include "line_stats.h"

namespace cc232 {

LineSummary summarize_lines(const std::vector<std::string>& lines) {
    LineSummary summary{};
    summary.total_lines = lines.size();

    for (const auto& line : lines) {
        if (!line.empty()) {
            ++summary.nonempty_lines;
        }
        summary.total_chars += line.size();
        if (line.size() > summary.longest_line_length) {
            summary.longest_line_length = line.size();
        }
    }

    return summary;
}

std::size_t count_lines_longer_than(const std::vector<std::string>& lines, std::size_t limit) {
    std::size_t count = 0;
    for (const auto& line : lines) {
        if (line.size() > limit) {
            ++count;
        }
    }
    return count;
}

}  // namespace cc232
