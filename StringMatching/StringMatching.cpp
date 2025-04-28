// CSCE350 Zachary Sansone
// Horspool's String Matching Algorithm
// Reads pattern and text from input.txt
// Writes index of first match (or -1) and execution time to output.txt

#include <fstream>
#include <string>
#include <vector>
#include <chrono>

int main() {
    std::ifstream input("input.txt");
    std::string pattern;
    std::string text;
    std::getline(input, pattern);
    std::getline(input, text);
    input.close();

    int m = pattern.size();
    int n = text.size();

    // Build shift table for ASCII characters
    std::vector<int> shift(256, m);
    for (int i = 0; i < m - 1; ++i) {
        unsigned char c = static_cast<unsigned char>(pattern[i]);
        shift[c] = m - 1 - i;
    }

    // Horspool search (assumes m <= n)
    auto start = std::chrono::high_resolution_clock::now();
    int index = -1;
    int pos = m - 1;
    while (pos < n) {
        int k = 0;
        while (k < m && pattern[m - 1 - k] == text[pos - k]) {
            ++k;
        }
        if (k == m) {
            index = pos - m + 1;
            break;
        }
        unsigned char c = static_cast<unsigned char>(text[pos]);
        pos += shift[c];
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::ofstream output("output.txt");
    output << index << std::endl;
    output << "Execution time: " << elapsed.count() << " seconds" << std::endl;
    output.close();
    return 0;
}