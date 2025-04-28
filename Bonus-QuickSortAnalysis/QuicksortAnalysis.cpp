// CSCE350 Zachary Sansone
// Empirical Analysis of QuickSort (Bonus)
// Generates 100 input files per size, runs QuickSort on each file,
// measures sort time excluding I/O, and outputs average times to output.txt

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <string>

// In-place QuickSort
int partition(float A[], int l, int r) {
    float pivot = A[l];
    int i = l, j = r + 1;
    while (true) {
        do { ++i; } while (i <= r && A[i] < pivot);
        do { --j; } while (j >= l && A[j] > pivot);
        if (i >= j) break;
        std::swap(A[i], A[j]);
    }
    std::swap(A[l], A[j]);
    return j;
}

void quickSort(float A[], int l, int r) {
    if (l < r) {
        int m = partition(A, l, r);
        quickSort(A, l, m - 1);
        quickSort(A, m + 1, r);
    }
}

int main() {
    std::vector<int> sizes = {10, 100, 1000, 10000, 100000};
    std::mt19937_64 rng(42);
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    std::ofstream output("output.txt");
    output << "Size  AverageTimeSeconds" << std::endl;

    for (int n : sizes) {
        // Pre-generate 100 random input files of size n
        for (int iter = 0; iter < 100; ++iter) {
            std::vector<float> data(n);
            for (int i = 0; i < n; ++i) data[i] = dist(rng);
            std::ofstream infile("input_" + std::to_string(n) + "_" + std::to_string(iter) + ".txt");
            for (float v : data) infile << v << " ";
        }

        double total_time = 0.0;
        // Sort each generated file and measure time excluding I/O
        for (int iter = 0; iter < 100; ++iter) {
            std::vector<float> arr(n);
            std::ifstream infile("input_" + std::to_string(n) + "_" + std::to_string(iter) + ".txt");
            for (int i = 0; i < n; ++i) infile >> arr[i];

            auto start = std::chrono::high_resolution_clock::now();
            quickSort(arr.data(), 0, n - 1);
            auto end = std::chrono::high_resolution_clock::now();
            total_time += std::chrono::duration<double>(end - start).count();
        }

        double avg_time = total_time / 100.0;
        output << n << "    " << avg_time << std::endl;
        std::cout << "Size " << n << " done, avg time = " << avg_time << "s" << std::endl;
    }

    output.close();
    return 0;
}