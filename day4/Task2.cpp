#include "../helpers.hpp"

int main() {
    auto file = getFile();
    int lc = static_cast<int>(file.size());
    int cc = static_cast<int>(file[0].size());
    int before = -1;
    int counter = 0;
    while (before < counter) {
        before = counter;
        for (int i = 0; i < lc; ++i) {
            for (int j = 0; j < cc; ++j) {
                if (file[i][j] == '@') {
                    int count = 0;
                    if (i > 0 && (file[i - 1][j] == '@' || file[i - 1][j] == 'X')) {
                        ++count;
                    }
                    if (j > 0 && (file[i][j - 1] == '@' || file[i][j - 1] == 'X')) {
                        ++count;
                    }
                    if (i > 0 && j > 0 && (file[i - 1][j - 1] == '@' || file[i - 1][j - 1] == 'X')) {
                        ++count;
                    }
                    if (i < lc - 1 && (file[i + 1][j] == '@' || file[i + 1][j] == 'X')) {
                        ++count;
                    }
                    if (j < cc - 1 && (file[i][j + 1] == '@' || file[i][j + 1] == 'X')) {
                        ++count;
                    }
                    if (i < lc - 1 && j > 0 && (file[i + 1][j - 1] == '@' || file[i + 1][j - 1] == 'X')) {
                        ++count;
                    }
                    if (i > 0 && j < cc - 1 && (file[i - 1][j + 1] == '@' || file[i - 1][j + 1] == 'X')) {
                        ++count;
                    }
                    if (i < lc - 1 && j < cc - 1 && (file[i + 1][j + 1] == '@' || file[i + 1][j + 1] == 'X')) {
                        ++count;
                    }
                    if (count < 4) {
                        ++counter;
                        file[i][j] = 'X';
                    }
                }
            }
        }
        for (auto& l : file) {
            for (auto& c : l) {
                if (c == 'X') {
                    c = '.';
                }
            }
        }
    }
    std::println("{}", counter);
}