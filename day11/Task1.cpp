#include "../helpers.hpp"

#include <map>
#include <array>

using device = std::array<char, 3>;

int count(const std::map<device, std::vector<device>>& file, device d) {
    static std::map<device, int> memo;
    if (memo.contains(d)) {
        return memo[d];
    }
    auto children = file.at(d);
    if (children.size() == 1 && children[0] == device{'o', 'u', 't'}) {
        return 1;
    }
    int out = std::accumulate(children.begin(), children.end(), 0, [&file](int i, device c) {return i + count(file, c); });
    memo[d] = out;
    return out;
}

int main() {
    auto file = getFile() | std::views::transform([](const auto& s) {
        auto base = split(s, ':');
        auto end = base[1].substr(1);
        auto children = split(end, ' ') | std::views::transform([](const auto& s) {return device{s[0], s[1], s[2]}; }) | std::ranges::to<std::vector>();
        return std::make_pair(device{base[0][0], base[0][1], base[0][2]}, children);
        }) | std::ranges::to<std::map>();

    std::println("{}", count(file, device{'y', 'o', 'u'}));
}