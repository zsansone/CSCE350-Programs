// CSCE350 Zachary Sansone
// This program implements Max Heap
// and displays its execiution time
// on an input file.

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

void heapify(std::vector<int>& heap, int n, int i) {
    int largest = i;       // Assume the current node is largest
    int left = 2 * i;      // Let child idx
    int right = 2 * i + 1; // Right child idx

    if (left <= n && heap[left] > heap[largest]) {
        largest = left; 
    }
    if (right <= n && heap[right] > heap[largest]) {
        largest = right; 
    }

    if (largest != i) {
        std::swap(heap[i], heap[largest]); 
        heapify(heap, n, largest); // Recursively heapify the affected subtree
    }
}

void buildMaxHeap(std::vector<int>& heap, int n) {
    for (int i = n / 2; i >= 1; i--) {
        heapify(heap, n, i);
    }
}

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("maxOutput.txt");

    int n;
    input >> n;

    std::vector<int> heap(n+1); // Create heap array
    for (int i = 1; i <= n; i++) {
        input >> heap[i]; // Put elements in heap
    }

    input.close(); 

    auto start = std::chrono::high_resolution_clock::now();
    buildMaxHeap(heap, n); // Build max heap
    auto end = std::chrono::high_resolution_clock::now();

    for(int i = 1; i <= n; i++) {
        output << heap[i] << " "; // Output heap
    }
    output << std::endl;

    std::chrono::duration<double> duration = end - start;
    output << "Execution time: " << duration.count() << "seconds" << std::endl; // Output execution time

    return 0;
}