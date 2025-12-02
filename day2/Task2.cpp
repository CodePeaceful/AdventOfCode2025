#include "../helpers.hpp"

#include <cstdint>

bool checkRepeat(uint64_t num) {
    auto s = std::to_string(num);
    uint64_t chunkSize = 1;
    while (chunkSize <= s.size() / 2) {
        if (s.size() % chunkSize == 0) {
            auto r = s | std::views::chunk(chunkSize) | std::views::transform([](auto s) {return std::string(s.begin(), s.end()); });
            bool same = true;
            for (const auto& sub : r) {
                if (r.front() != sub) {
                    same = false;
                    break;
                }
            }
            if (same) {
                return true;
            }
        }
        ++chunkSize;
    }
    return false;
}

int main() {
    auto l = getFile()[0];
    auto ranges = split(l, ',');
    uint64_t sum = 0;
    for (const auto& r : ranges) {
        auto pair = split(r, '-');
        for (uint64_t i = std::stoull(pair.front()); i <= std::stoull(pair.back()); ++i) {
            if (checkRepeat(i)) {
                sum += i;
            }
        }
    }
    std::println("{}", sum);
}