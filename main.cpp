#include <iostream>
#include <algorithm>
#include<fstream>
#include <chrono>
#include <random>

using namespace std;

void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void counting_sort(int arr[], int size) {
    // Find the maximum element in the array
    int max_val = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    // Create a count array of size max_val+1, and initialize all elements to 0
    int count[max_val+1] = {0};

    // Count the number of occurrences of each element in arr, and store in count array
    for (int i = 0; i < size; i++) {
        count[arr[i]]++;
    }

    // Modify the count array to show the cumulative number of elements up to each index
    for (int i = 1; i <= max_val; i++) {
        count[i] += count[i-1];
    }

    // Create a temporary output array
    int output[size];

    // Traverse the array arr in reverse order, and place each element in the correct position in the output array
    for (int i = size-1; i >= 0; i--) {
        output[count[arr[i]]-1] = arr[i];
        count[arr[i]]--;
    }

    // Copy the elements from the output array back to the input array
    for (int i = 0; i < size; i++) {
        arr[i] = output[i];
    }
}



// A utility function to swap two elements in an array
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// A utility function to max-heapify a subtree rooted at index i of the array A of size n
void max_heapify(int A[], int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2*i + 1; // Left child
    int right = 2*i + 2; // Right child

    // If left child is larger than root
    if (left < n && A[left] > A[largest]) {
        largest = left;
    }

    // If right child is larger than largest so far
    if (right < n && A[right] > A[largest]) {
        largest = right;
    }

    // If largest is not root
    if (largest != i) {
        swap(&A[i], &A[largest]);
        // Recursively max-heapify the affected subtree
        max_heapify(A, n, largest);
    }
}

// The main function to sort an array of size n using heap sort
void heap_sort(int A[], int n) {
    // Build a max heap from the array
    for (int i = n/2 - 1; i >= 0; i--) {
        max_heapify(A, n, i);
    }

    // Extract elements from the heap and place them in the sorted section of the array
    for (int i = n-1; i >= 1; i--) {
        // Swap the root of the heap (which is the largest element) with the last element in the heap
        swap(&A[0], &A[i]);

        // Restore the max heap property in the remaining heap
        max_heapify(A, i, 0);
    }
}




void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}


// A utility function to merge two sorted subarrays A[left..mid] and A[mid+1..right]
void merge(int A[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) {
        L[i] = A[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = A[mid + 1 + j];
    }

    // Merge the two temporary arrays back into A[left..right]
    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = left; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        }
        else {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[] if there are any
    while (i < n1) {
        A[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[] if there are any
    while (j < n2) {
        A[k] = R[j];
        j++;
        k++;
    }
}

// The main function that sorts the array A[left..right] using merge sort
void merge_sort(int A[], int left, int right) {
    if (left < right) {
        // Find the middle point to divide the array into two subarrays
        int mid = left + (right - left) / 2;

        // Recursively sort the two subarrays
        merge_sort(A, left, mid);
        merge_sort(A, mid+1, right);

        // Merge the two sorted subarrays
        merge(A, left, mid, right);
    }
}


int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i+1;
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quick_sort(arr, low, p-1);
        quick_sort(arr, p+1, high);
    }
}

void selection_sort(int A[], int n) {
    // One by one move boundary of unsorted subarray
    for (int i = 0; i < n - 1; i++) {
        // Find the minimum element in unsorted array
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[min_idx]) {
                min_idx = j;
            }
        }

        // Swap the found minimum element with the first element
        int temp = A[min_idx];
        A[min_idx] = A[i];
        A[i] = temp;
    }
}


int main() {
    int arr[10];
    ifstream infile("random_numbers2.txt");

    /*ofstream outfile("random_numbers.txt");                   //GENERATOR FOR FILE
    // Generate 100 unsorted numbers
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100000);

    for (int & i : arr) {
        i = dis(gen);
        outfile << i << " ";
    }*/

    for (int & i : arr) {
        infile >> i;
    }

    // Sort using bubble sort
    auto start = chrono::high_resolution_clock::now();
    bubble_sort(arr, 10);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cout << "Bubble sort took " << duration.count() << " nanoseconds." << endl;

    start = chrono::high_resolution_clock::now();
    counting_sort(arr, 10);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cout << "Counting sort took " << duration.count() << " nanoseconds." << endl;

    start = chrono::high_resolution_clock::now();
    heap_sort(arr, 10);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cout << "Heap sort took " << duration.count() << " nanoseconds." << endl;

    // Sort using insertion sort
    start = chrono::high_resolution_clock::now();
    insertion_sort(arr, 10);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cout << "Insertion sort took " << duration.count() << " nanoseconds." << endl;

    start = chrono::high_resolution_clock::now();
    merge_sort(arr, 0, 9);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cout << "Merge sort took " << duration.count() << " nanoseconds." << endl;

    // Sort using quicksort
    start = chrono::high_resolution_clock::now();
    quick_sort(arr, 0, 9);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cout << "Quicksort took " << duration.count() << " nanoseconds." << endl;

    start = chrono::high_resolution_clock::now();
    selection_sort(arr, 10);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cout << "Selection sort took " << duration.count() << " nanoseconds." << endl;

    return 0;
}
