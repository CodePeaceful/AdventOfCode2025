#include "../helpers.hpp"

int main() {
    auto v = getFile();
    int counter = 0;
    int dial = 50;
    for (const auto& s : v) {
        int change = std::stoi(s.substr(1));
        dial %= 100;
        dial += 100;
        dial %= 100;
        if (s[0] == 'L') {
            if (dial == 0)
                --counter;
            dial -= change;
            if (dial <= 0)
                counter++;
        }
        else {
            dial += change;
        }
        counter += std::abs(dial / 100);
    }
    std::println("{}", counter);
}