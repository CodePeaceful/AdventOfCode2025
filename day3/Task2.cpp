#include "../helpers.hpp"

uint64_t sumFunc(const std::string& line) {
    uint64_t total = 0;
    auto it = line.begin();
    for (int i = 11; i >= 0; --i) {
        total *= 10;
        uint64_t max = 0;
        for (auto start = it; start < line.end() - i; ++start) {
            if (*start - '0' > max) {
                max = *start - '0';
                it = start;
            }
        }
        ++it;
        total += max;
    }
    return total;
}

int main() {
    auto v = getFile();
    uint64_t sum = 0;
    for (const auto& line : v) {
        sum += sumFunc(line);
    }
    std::println("{}", sum);

}