#include "../helpers.hpp"

#include <unordered_set>

std::vector<std::pair<uint64_t, uint64_t>> checked;

uint64_t getNews(std::pair<uint64_t, uint64_t> values) {
    for (const auto& r : checked) {
        // has overlap
        if (values.second >= r.first && values.first <= r.second) {
            if (values.first >= r.first && values.second <= r.second) {
                return 0;
            }
            if (values.first >= r.first && values.second > r.second) {
                values.first = r.second + 1;
                continue;
            }
            if (values.first < r.first&& values.second <= r.second) {
                values.second = r.first - 1;
                continue;
            }
            if (values.first < r.first && values.second > r.second) {
                return getNews({values.first, r.first - 1}) + getNews({r.second + 1, values.second});
            }
            throw std::runtime_error("missed path");
        }
    }
    return values.second - values.first + 1;
}

int main() {
    auto file = getFile();
    auto data = file | std::views::take_while([](const auto& s) {return s.size() > 2; }) | std::views::transform([](const std::string& l) {
        auto s = split(l, '-');
        return std::make_pair<uint64_t, uint64_t>(std::stoull(s[0]), std::stoull(s[1]));
        });

    uint64_t count = 0;
    for (const auto& pair : data) {
        count += getNews(pair);
        checked.push_back(pair);
        std::println("{}", pair);
    }


    std::println("{}", count);
}