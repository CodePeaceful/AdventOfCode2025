#include "../helpers.hpp"
#include <set>

int main() {
    auto file = getFile();
    auto l1 = file[0] | std::ranges::to<std::vector>();
    auto start = findIndex(l1, 'S');
    std::set<int> beams{start};
    int counter = 0;
    for (const auto& line : file | std::views::drop(1)) {
        std::vector<int> toRemove;
        std::vector<int> toAdd;
        for (int i : beams) {
            if (line[i] == '^') {
                toRemove.push_back(i);
                toAdd.push_back(i - 1);
                toAdd.push_back(i + 1);
                ++counter;
            }
        }
        for (int i : toRemove) {
            beams.erase(i);
        }
        for (int i : toAdd) {
            beams.insert(i);
        }
    }
    std::println("{}", counter);
}