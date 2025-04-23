// CSCE350 Zachary Sansone
// This program implements Min Heap
// and displays its execiution time
// on an input file.

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

void heapify(std::vector<int>& heap, int n, int i) {
    int smallest = i;       // Assume the current node is smallest
    int left = 2 * i;      // Let child idx
    int right = 2 * i + 1; // Right child idx

    if (left <= n && heap[left] < heap[smallest]) {
        smallest = left; 
    }
    if (right <= n && heap[right] < heap[smallest]) {
        smallest = right; 
    }

    if (smallest != i) {
        std::swap(heap[i], heap[smallest]); 
        heapify(heap, n, smallest); // Recursively heapify the affected subtree
    }
}

void buildMinHeap(std::vector<int>& heap, int n) {
    for (int i = n / 2; i >= 1; i--) {
        heapify(heap, n, i);
    }
}

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("minOutput.txt");

    int n;
    input >> n;

    std::vector<int> heap(n+1); // Create heap array
    for (int i = 1; i <= n; i++) {
        input >> heap[i]; // Put elements in heap
    }

    input.close(); 

    auto start = std::chrono::high_resolution_clock::now();
    buildMinHeap(heap, n); // Build Min heap
    auto end = std::chrono::high_resolution_clock::now();

    for(int i = 1; i <= n; i++) {
        output << heap[i] << " "; // Output heap
    }
    output << std::endl;

    std::chrono::duration<double> duration = end - start;
    output << "Execution time: " << duration.count() << "seconds" << std::endl; // Output execution time

    return 0;
}