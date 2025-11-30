#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ranges>
#include <stdexcept>
#include <print>

std::vector<std::string> getFile() {
    std::ifstream in("data.txt");
    if (in.is_open()) {
        std::string line;
        std::vector<std::string> lines;
        while (std::getline(in, line)) {
            lines.push_back(line);
        }
        return lines;
    }
    throw std::runtime_error("data.txt not found");
}

std::vector<std::string> split(const std::string& str, char seperator) {
    return str | std::views::split(seperator) | std::views::transform([](auto s) {return std::string(s.begin(), s.end()); }) | std::ranges::to<std::vector>();
}

// size < 32 bit singed integer limit
template<typename T>
int findIndex(std::vector<T>& v, T val) {
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] == val) {
            return i;
        }
    }
    return -1;
}