#include "../helpers.hpp"
#include <functional>

int main() {
    auto file = getFile();
    std::vector<std::tuple<std::vector<uint64_t>, std::function<uint64_t(uint64_t, uint64_t)>, uint64_t>> problems;
    auto splitLines = file | std::views::transform([](const auto& s) {return split(s, ' '); }) | std::ranges::to<std::vector>();
    for (auto i = 0ull; i < splitLines[0].size(); ++i) {
        auto val = std::vector(splitLines.begin(), splitLines.end() - 1) | std::views::transform([i](const auto& s) {return std::stoull(s[i]); }) | std::ranges::to<std::vector<uint64_t>>();
        if (splitLines.back()[i][0] == '*') {
            problems.emplace_back(val, [](uint64_t first, uint64_t second) {return first * second; }, 1ull);
        }
        else {
            problems.emplace_back(val, [](uint64_t first, uint64_t second) {return first + second; }, 0ull);
        }
    }
    auto solutions = problems | std::views::transform([](const auto& p) {return std::accumulate(std::get<0>(p).begin(), std::get<0>(p).end(), std::get<2>(p), std::get<1>(p)); });
    std::println("{}", std::accumulate(solutions.begin(), solutions.end(), 0ull));
}