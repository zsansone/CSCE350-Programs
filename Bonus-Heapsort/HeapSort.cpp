// CSCE350 Zachary Sansone
// This program implements heap sort
// using previous Max Heap function
// on an input file.

#include <iostream>
#include <fstream>
#include <vector>

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
    std::ofstream output("output.txt");

    int n;
    input >> n;


    std::vector<int> heap(n+1); // Create heap array
    for (int i = 1; i <= n; i++) {
        input >> heap[i]; // Put elements in heap
    }

    input.close(); 

    buildMaxHeap(heap, n); // Build max heap

    
    output << "heap: ";
    for(int i = 1; i <= n; i++) {
        output << heap[i] << " "; // Output heap
    }
    output << std::endl;

    for (int i = n ; i >= 2; i--) {
        std::swap(heap[1], heap[i]); 
        heapify(heap, i - 1, 1); // Heapify the reduced heap
    }
    
    output << "heapsort: ";
    for(int i = 1; i <= n; i++) {
        output << heap[i] << " "; // Output sorted array
    }
    output << std::endl;

    return 0;
}