#include "../helpers.hpp"
#include <numeric>
#include <execution>

auto getValue = [](const std::vector<std::string>& line) {
    const std::vector<bool> req = line.front() | std::views::drop(1) | std::views::take_while([](char c) {return c != ']'; }) | std::views::transform([](char c) {return c == '#'; }) | std::ranges::to<std::vector>();
    std::vector<std::vector<int>> options = line | std::views::drop(1) | std::views::take_while([](const auto& s) {return s[0] == '('; }) |
        std::views::transform([](const auto& s) {return std::string{s.begin() + 1, s.end() - 1}; }) |
        std::views::transform([](const auto& s) {return split(s, ',') | std::views::transform([](const auto& s) {return std::stoi(std::string(s)); }) | std::ranges::to<std::vector>(); }) |
        std::ranges::to<std::vector>();

    std::sort(options.begin(), options.end());
    int min = options.size();

    do {
        auto test = req;
        if (min == 1) {
            break;
        }
        for (int i = 0; const auto& option : options) {
            ++i;
            if (i > min) {
                break;
            }
            for (int j : option) {
                test[j] = !test[j];
            }
            if (std::none_of(test.begin(), test.end(), [](bool b) {return b; })) {
                if (i < min) {
                    min = i;
                }
                break;
            }
        }
    } while (std::ranges::next_permutation(options).found);
    std::println("line {} done", req);
    return min;
    };

int main() {
    auto file = getFile() | std::views::transform([](const auto& s) {return split(s, ' '); });

    int sum = std::transform_reduce(std::execution::par_unseq, file.begin(), file.end(), 0, std::plus{ }, getValue);

    std::println("{}", sum);
}