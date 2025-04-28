// CSCE350 Zachary Sansone
// Boyer-Moore String Matching Algorithm
// Reads pattern and text from input.txt
// Writes index of first match (or -1) and execution time to output.txt

#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>

int main() {
    std::ifstream input("input.txt");
    std::string pattern, text;
    std::getline(input, pattern);
    std::getline(input, text);
    input.close();

    int m = pattern.size();
    int n = text.size();
    
    // 1) Bad-character table (last occurrence)
    std::vector<int> badChar(256, -1);
    for (int i = 0; i < m; ++i) {
        unsigned char c = static_cast<unsigned char>(pattern[i]);
        badChar[c] = i;
    }

    // 2) Good-suffix tables: suffix and prefix
    std::vector<int> suffix(m, -1);
    std::vector<bool> prefix(m, false);
    for (int i = 0; i < m - 1; ++i) {
        int j = i;
        int k = 0;  // length of current matching suffix
        while (j >= 0 && pattern[j] == pattern[m - 1 - k]) {
            --j;
            ++k;
            suffix[k] = j + 1;  // record start position of suffix
        }
        if (j < 0) {
            prefix[k] = true;   // whole prefix matches suffix
        }
    }

    // 3) Good-suffix shift table
    std::vector<int> gs(m, m);
    for (int i = 0; i < m - 1; ++i) {
        int len = m - 1 - i;
        if (suffix[len] != -1) {
            gs[i] = i - suffix[len] + 1;
        }
    }
    // fallback for prefixes
    int lastPrefix = m;
    for (int k = m - 1; k >= 0; --k) {
        if (prefix[m - 1 - k]) {
            lastPrefix = m - 1 - k;
        }
        gs[k] = std::min(gs[k], lastPrefix + (m - 1 - k));
    }

    // 4) Search using Boyer-Moore
    auto start = std::chrono::high_resolution_clock::now();
    int index = -1;
    int pos = 0;
    while (pos <= n - m) {
        int j;
        for (j = m - 1; j >= 0; --j) {
            if (pattern[j] != text[pos + j]) break;
        }
        if (j < 0) {
            index = pos;
            break;
        }
        unsigned char bad = static_cast<unsigned char>(text[pos + j]);
        int bcShift = j - badChar[bad];
        int gsShift = 1;
        if (j < m - 1) gsShift = gs[j + 1];
        pos += std::max(bcShift, gsShift);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::ofstream output("output.txt");
    output << index << std::endl;
    output << "Execution time: " << elapsed.count() << " seconds" << std::endl;
    output.close();
    return 0;
}