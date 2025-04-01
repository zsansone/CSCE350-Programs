// CSCE350 Zachary Sansone
// This program implements Merge Sort 
// and Quick Sort algorithms
// and compares their performace 
// on an input file.

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

void merge(float B[], int p, float C[], int q, float A[]) {
    int i = 0, j = 0, k = 0; // Initialize indices
    while (i < p && j < q) {
        if (B[i] <= C[j]) {
            A[k++] = B[i++]; // Copy from B
        } else {
            A[k++] = C[j++]; // Copy from C
        }

    }

    if (i == p) 
        while (j < q) {
            A[k++] = C[j++]; // Copy remaining from C
        }
    else 
        while (i < p) {
            A[k++] = B[i++]; // Copy remaining from B
        }
}

void mergeSort(float A[], int n) {
    if (n > 1) {
        int mid = n / 2; // Find floor of n/2

        std::vector<float> B(A, A + mid); // Create left array
        std::vector<float> C(A + mid, A + n); // Create right array

        mergeSort(B.data(), mid); // Sort left half
        mergeSort(C.data(), n - mid); // Sort right half

        merge(B.data(), mid, C.data(), n - mid, A); // Merge sorted halves
    }
}

int partition(float A[], int l, int r) {
    float p = A[l]; // First element as pivot
    int i = l, j = r + 1; 

    do {
        do { i++;} while ( i != r && A[i] < p); // Find first element greater than pivot
        do { j--; } while ( j != l && A[j] > p); // Find first element less than pivot
        if (i < j) {
            std::swap(A[i], A[j]); // Swap elements
        }
    } while (i < j);

    std::swap(A[l], A[j]); // Swap pivot with j
    return j; // Return pivot index
}

void quickSort(float A[], int l, int r) {
    if (l < r) {
        int s = partition(A, l, r); // Partition the array
        quickSort(A, l, s - 1); // Sort left half
        quickSort(A, s + 1, r); // Sort right half
    }
}

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    if (!input) {
        std::cerr << "Error opening input file." << std::endl;
        return 1;
    }

    std::vector<float> arr;
    float num;

    while (input >> num) {
        arr.push_back(num); // Read numbers from file
    }

    input.close(); // Close input file

    if (arr.empty()) {
        std::cerr << "Input file is empty or contains no valid numbers." << std::endl;
        return 1;
    }

    int n = arr.size(); // Get size of array


    std::vector<float> quickSortArray(arr); // Use vector for dynamic array
    std::vector<float> mergeSortArray(arr); // Use vector for dynamic array

    auto start1 = std::chrono::high_resolution_clock::now(); // Start timer
    quickSort(quickSortArray.data(), 0, n - 1); // Call quicksort
    auto end1 = std::chrono::high_resolution_clock::now(); // End timer
    std::chrono::duration<double> quickSortDuration = end1 - start1; // Calculate duration
    
    auto start2 = std::chrono::high_resolution_clock::now(); // Start timer
    mergeSort(mergeSortArray.data(), n); // Call mergesort
    auto end2 = std::chrono::high_resolution_clock::now(); // End timer
    std::chrono::duration<double> mergeSortDuration = end2 - start2; // Calculate duration

    // Output results
    output << "Original Array: ";
    for (float val : arr) {
        output << val << " ";
    }
    output << std::endl;
    output << std::endl;

    output << "Quick Sort Time: " << quickSortDuration.count() << " seconds" << std::endl;
    output << "Merge Sort Time: " << mergeSortDuration.count() << " seconds" << std::endl;

    if (quickSortDuration < mergeSortDuration) {
        output << "Quick Sort is faster." << std::endl;
    } else if (quickSortDuration > mergeSortDuration) {
        output << "Merge Sort is faster." << std::endl;
    } else {
        output << "Both sorting algorithms took the same time." << std::endl;
    }

    output << "Quick Sort Array: ";
    for (float val : quickSortArray) {
        output << val << " "; // Output sorted array
    }
    output << std::endl;
    output << "Merge Sort Array: ";
    for (float val : mergeSortArray) {
        output << val << " "; // Output sorted array
    }
    output << std::endl;
    

    // Check if arrays are equal
    bool arraysEqual = true;
    for (int i = 0; i < n; i++) {
        if (quickSortArray[i] != mergeSortArray[i]) {
            arraysEqual = false;
            break;
        }
    }

    if (arraysEqual) {
        output << "The arrays are equal." << std::endl;
    } else {
        output << "The arrays are not equal." << std::endl;
    }
    output << std::endl;

    output.close(); // Close output file

    return 0;
}