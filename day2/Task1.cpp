#include "../helpers.hpp"

#include <cstdint>

bool checkRepeat(uint64_t num) {
    uint64_t div = 10;
    uint64_t result;
    uint64_t modResult;
    do {
        result = num / div;
        modResult = num % div;
        div *= 10;
    } while (result > modResult);
    return result == modResult && std::to_string(num).size() == std::to_string(result).size() * 2;
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