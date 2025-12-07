#include "../helpers.hpp"
#include <map>

int main() {
    auto file = getFile();
    auto l1 = file[0] | std::ranges::to<std::vector>();
    auto start = findIndex(l1, 'S');
    std::map<int, uint64_t> beams;
    beams[start] = 1;
    uint64_t counter = 1;
    for (const auto& line : file | std::views::drop(1)) {
        std::vector<int> toRemove;
        std::vector<std::pair<int, uint64_t>> toAdd;
        for (auto [i, j] : beams) {
            if (line[i] == '^') {
                toRemove.push_back(i);
                toAdd.push_back({i - 1, j});
                toAdd.push_back({i + 1, j});
                counter += j;
            }
        }
        for (int i : toRemove) {
            beams.erase(i);
        }
        for (auto [i, j] : toAdd) {
            beams[i] += j;
        }
    }
    std::println("{}", counter);
}