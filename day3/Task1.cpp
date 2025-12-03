#include "../helpers.hpp"

int sumFunc(const std::string& line) {
    int max1 = 0;
    auto it = line.begin();
    for (auto start = it; start < line.end() - 1; ++start) {
        if (*start - '0' > max1) {
            max1 = *start - '0';
            it = start;
        }
    }
    int max2 = 0;
    for (auto start = it + 1; start < line.end(); ++start) {
        if (*start - '0' > max2) {
            max2 = *start - '0';
        }
    }
    return 10 * max1 + max2;
}

int main() {
    auto v = getFile();
    int sum = 0;
    for (const auto& line : v) {
        sum += sumFunc(line);
    }
    std::println("{}", sum);

}