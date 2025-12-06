#include "../helpers.hpp"
#include <functional>

int main() {
    auto file = getFile();
    std::vector<std::tuple<std::vector<uint64_t>, std::function<uint64_t(uint64_t, uint64_t)>, uint64_t>> problems;
    std::vector<uint64_t> problemIndex;
    for (uint64_t i = 0; i < file.back().size(); ++i) {
        if (!std::isspace(file.back()[i])) {
            problemIndex.push_back(i);
        }
    }
    problemIndex.push_back(file.back().size() + 1);
    for (auto i = 0ull; i < problemIndex.size() - 1; ++i) {
        auto lines = std::vector(file.begin(), file.end() - 1)
            | std::views::transform([i, &problemIndex](const auto& l) {return l | std::views::drop(problemIndex[i]) | std::views::take(problemIndex[i + 1] - problemIndex[i] - 1) | std::ranges::to<std::vector>(); })
            | std::ranges::to<std::vector>();

        std::vector<uint64_t> val;
        for (auto j = 0ull; j < lines.front().size(); ++j) {
            uint64_t num = 0;
            for (const auto& l : lines) {
                if (std::isalnum(l[j])) {
                    num *= 10;
                    num += l[j] - '0';
                }
            }
            val.push_back(num);
        }

        if (file.back()[problemIndex[i]] == '*') {
            problems.emplace_back(val, [](uint64_t first, uint64_t second) {return first * second; }, 1ull);
        }
        else {
            problems.emplace_back(val, [](uint64_t first, uint64_t second) {return first + second; }, 0ull);
        }
    }
    auto solutions = problems | std::views::transform([](const auto& p) {return std::accumulate(std::get<0>(p).begin(), std::get<0>(p).end(), std::get<2>(p), std::get<1>(p)); });
    std::println("{}", std::accumulate(solutions.begin(), solutions.end(), 0ull));
}