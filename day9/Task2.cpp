#include "../helpers.hpp"

//FIXME: awnser to high


bool checkArea(const std::vector<std::pair<long long, long long>>& file, std::pair<long long, long long> i, std::pair<long long, long long> j) {
    if (i.first == j.first || i.second == j.second) {
        // ignoring lines
        return false;
    }
    if (i.first < j.first && i.second < j.second) {
        return std::any_of(file.begin(), file.end(), [i, j](auto p) {return p.first <= i.first && p.second >= j.second; }) &&
            std::any_of(file.begin(), file.end(), [i, j](auto p) {return p.first >= j.first && p.second <= i.second; });
    }
    if (i.first > j.first && i.second < j.second) {
        return std::any_of(file.begin(), file.end(), [i, j](auto p) {return p.first >= i.first && p.second >= j.second; }) &&
            std::any_of(file.begin(), file.end(), [i, j](auto p) {return p.first <= j.first && p.second <= i.second; });
    }
    if (i.first < j.first && i.second > j.second) {
        return std::any_of(file.begin(), file.end(), [i, j](auto p) {return p.first <= i.first && p.second <= j.second; }) &&
            std::any_of(file.begin(), file.end(), [i, j](auto p) {return p.first >= j.first && p.second >= i.second; });
    }
    if (i.first > j.first && i.second > j.second) {
        return std::any_of(file.begin(), file.end(), [i, j](auto p) {return p.first >= i.first && p.second <= j.second; }) &&
            std::any_of(file.begin(), file.end(), [i, j](auto p) {return p.first <= j.first && p.second >= i.second; });
    }
    return false;
}

int main() {
    auto file = getFile() | std::views::transform([](const auto& l) {
        auto s = split(l, ',');
        return std::make_pair(std::stoll(s[0]), std::stoll(s[1])); }) |
        std::ranges::to<std::vector>();

        int64_t max = 0;
        int yes = 0;
        int no = 0;
        for (auto it = file.begin(); it != file.end(); ++it) {
            for (auto jt = it + 1; jt != file.end(); ++jt) {
                int64_t size = (std::abs(it->first - jt->first) + 1) * (std::abs(it->second - jt->second) + 1);
                if (checkArea(file, *it, *jt)) {
                    max = std::max(max, size);
                    ++yes;
                }
                else {
                    ++no;
                }
            }
        }
        std::println("yes: {}, no: {}", yes, no);
        std::println("{}", max);

}