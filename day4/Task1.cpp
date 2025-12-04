#include "../helpers.hpp"

int main() {
    auto file = getFile();
    int lc = static_cast<int>(file.size());
    int cc = static_cast<int>(file[0].size());
    int counter = 0;
    for (int i = 0; i < lc; ++i) {
        for (int j = 0; j < cc; ++j) {
            if (file[i][j] == '@') {
                int count = 0;
                if (i > 0 && file[i - 1][j] == '@') {
                    ++count;
                }
                if (j > 0 && file[i][j - 1] == '@') {
                    ++count;
                }
                if (i > 0 && j > 0 && file[i - 1][j - 1] == '@') {
                    ++count;
                }
                if (i < lc - 1 && file[i + 1][j] == '@') {
                    ++count;
                }
                if (j < cc - 1 && file[i][j + 1] == '@') {
                    ++count;
                }
                if (i < lc - 1 && j > 0 && file[i + 1][j - 1] == '@') {
                    ++count;
                }
                if (i > 0 && j < cc - 1 && file[i - 1][j + 1] == '@') {
                    ++count;
                }
                if (i < lc - 1 && j < cc - 1 && file[i + 1][j + 1] == '@') {
                    ++count;
                }
                if (count < 4) {
                    ++counter;
                }
            }
        }
    }
    std::println("{}", counter);
}