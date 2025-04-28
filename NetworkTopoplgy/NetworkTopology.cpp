// CSCE350 Zachary Sansone
// Detects if a Network Topology
// is a ring, star, or fully connected.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <chrono>

int main() {
    //Read the input file
    std::ifstream input("input.txt");
    std::string line;
    std::vector<std::vector<int>> A;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        std::vector<int> row;
        int x;
        while (iss >> x) {
            row.push_back(x);
        }
        A.push_back(row);
    }
    input.close();

    int n = A.size();

    // Start timing
    auto start = std::chrono::high_resolution_clock::now();
    std::string topology;

    // Check if fully connecetd: off diag = 1, diag = 0
    bool isConnected = true;
    for (int i = 0; i < n && isConnected; ++i) {
        for (int j = 0; j < n;  ++j) {
            if ((i == j && A[i][j] != 0 || i != j && A[i][j] != 1)) {
                isConnected = false;
                break;
            }
        }
    }
    if (isConnected) {
        topology = "fully connected mesh";
    } else {
         // Check star topology
         int center = -1;
         for (int i = 0; i < n; ++i) {
             int degree = 0;
             for (int j = 0; j < n; ++j) degree += A[i][j];
             if (degree == n - 1 && A[i][i] == 0) {
                 if (center < 0) center = i;
                 else center = -2; // more than one candidate
             }
         }
         bool isStar = (center >= 0);
         if (isStar) {
             for (int i = 0; i < n; ++i) {
                 if (i == center) continue;
                 int degree = 0;
                 for (int j = 0; j < n; ++j) degree += A[i][j];
                 if (degree != 1 || A[i][center] != 1 || A[i][i] != 0) {
                     isStar = false;
                     break;
                 }
             }
         }
         if (isStar) {
             topology = "star";
         } else {
             // Check ring topology: degree 2 + connectivity
             bool degree2 = true;
             for (int i = 0; i < n; ++i) {
                 if (A[i][i] != 0) { degree2 = false; break; }
                 int degree = 0;
                 for (int j = 0; j < n; ++j) degree += A[i][j];
                 if (degree != 2) { degree2 = false; break; }
             }
             bool isRing = false;
             if (degree2) {
                 // BFS for connectivity
                 std::vector<bool> visited(n, false);
                 std::queue<int> q;
                 visited[0] = true;
                 q.push(0);
                 int count = 1;
                 while (!q.empty()) {
                     int u = q.front(); q.pop();
                     for (int v = 0; v < n; ++v) {
                         if (A[u][v] == 1 && !visited[v]) {
                             visited[v] = true;
                             q.push(v);
                             ++count;
                         }
                     }
                 }
                 isRing = (count == n);
             }
             topology = (isRing ? "ring" : "unknown");
         }
     }
 
     // Stop timing
     auto end = std::chrono::high_resolution_clock::now();
     std::chrono::duration<double> elapsed = end - start;
 
     // Write result and timing
     std::ofstream output("output.txt");
     output << topology << std::endl;
     output << "Execution time: " << elapsed.count() << " seconds" << std::endl;
     output.close();
 
     return 0;
}
