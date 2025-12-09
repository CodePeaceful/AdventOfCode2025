#include "../helpers.hpp"



int main() {
    auto file = getFile() | std::views::transform([](const auto& l) {
        auto s = split(l, ',');
        return std::make_pair(std::stoll(s[0]), std::stoll(s[1])); }) |
        std::ranges::to<std::vector>();

        int64_t max = 0;
        for (auto it = file.begin(); it != file.end(); ++it) {
            for (auto jt = it + 1; jt != file.end(); ++jt) {
                int64_t size = (std::abs(it->first - jt->first) + 1) * (std::abs(it->second - jt->second) + 1);
                max = std::max(max, size);
            }
        }
        std::println("{}", max);

}