#include "../helpers.hpp"

#include <map>
#include <array>

using device = std::array<char, 3>;

uint64_t count(const std::map<device, std::vector<device>>& file, device d, std::pair<bool, bool> fftdac) {
    if (d == device{'f', 'f', 't'}) {
        fftdac.first = true;
    }
    if (d == device{'d', 'a', 'c'}) {
        fftdac.second = true;
    }

    static std::map<std::pair<device, std::pair<bool, bool>>, uint64_t> memo;
    if (memo.contains({d, fftdac})) {
        return memo[{d, fftdac}];
    }

    auto children = file.at(d);
    if (children.size() == 1 && children[0] == device{'o', 'u', 't'}) {
        if (fftdac.first && fftdac.second) {
            return 1;
        }
        return 0;
    }
    uint64_t out = std::accumulate(children.begin(), children.end(), 0ull, [&file, fftdac](uint64_t i, device c) {return i + count(file, c, fftdac); });
    memo[{d, fftdac}] = out;
    return out;
}

int main() {
    auto file = getFile() | std::views::transform([](const auto& s) {
        auto base = split(s, ':');
        auto end = base[1].substr(1);
        auto children = split(end, ' ') | std::views::transform([](const auto& s) {return device{s[0], s[1], s[2]}; }) | std::ranges::to<std::vector>();
        return std::make_pair(device{base[0][0], base[0][1], base[0][2]}, children);
        }) | std::ranges::to<std::map>();

    std::println("{}", count(file, device{'s', 'v', 'r'}, {false, false}));
}