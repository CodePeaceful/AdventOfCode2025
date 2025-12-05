#include "../helpers.hpp"

bool isFresh(const std::vector<std::pair<uint64_t, uint64_t>>& data, uint64_t value) {
    for (const auto& r : data) {
        if (value >= r.first && value <= r.second) {
            return true;
        }
    }
    return false;
}

int main() {
    auto file = getFile();
    auto data = file | std::views::take_while([](const auto& s) {return s.size() > 2; }) | std::views::transform([](const std::string& l) {
        auto s = split(l, '-');
        return std::make_pair<uint64_t, uint64_t>(std::stoull(s[0]), std::stoull(s[1]));
        }) | std::ranges::to<std::vector>();

    auto values = file | std::views::drop_while([](const auto& s) {return s.size() > 2; }) | std::views::drop_while([](const auto& s) {return s.empty(); });
    auto result = std::count_if(values.begin(), values.end(), [&data](const auto& s) { return isFresh(data, std::stoull(s)); });


    std::println("{}", result);
}