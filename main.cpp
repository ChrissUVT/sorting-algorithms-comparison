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
    int max_val = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    int count[max_val+1] = {0};
    for (int i = 0; i < size; i++) {
        count[arr[i]]++;
    }

    
    for (int i = 1; i <= max_val; i++) {
        count[i] += count[i-1];
    }
    
    int output[size];

    for (int i = size-1; i >= 0; i--) {
        output[count[arr[i]]-1] = arr[i];
        count[arr[i]]--;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = output[i];
    }
}


void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void max_heapify(int A[], int n, int i) {
    int largest = i; 
    int left = 2*i + 1; 
    int right = 2*i + 2; 
    
    if (left < n && A[left] > A[largest]) {
        largest = left;
    }

    if (right < n && A[right] > A[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&A[i], &A[largest]);
        max_heapify(A, n, largest);
    }
}

void heap_sort(int A[], int n) {
    for (int i = n/2 - 1; i >= 0; i--) {
        max_heapify(A, n, i);
    }

    for (int i = n-1; i >= 1; i--) {
 
        swap(&A[0], &A[i]);

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


void merge(int A[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = A[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = A[mid + 1 + j];
    }

    int i = 0; 
    int j = 0; 
    int k = left; 
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

    while (i < n1) {
        A[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        A[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int A[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(A, left, mid);
        merge_sort(A, mid+1, right);
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
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[min_idx]) {
                min_idx = j;
            }
        }

        int temp = A[min_idx];
        A[min_idx] = A[i];
        A[i] = temp;
    }
}


int main() {
    int arr[10];
    ifstream infile("random_numbers2.txt");

    /*ofstream outfile("random_numbers.txt");                   //GENERATOR FOR FILE COMMENTED                              
    random_device rd;                                          //BY USING THESE LINES YOU WILL GENERATE A FILE CONTINING YOU INPUT
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100000);

    for (int & i : arr) {
        i = dis(gen);
        outfile << i << " ";
    }*/

    for (int & i : arr) {
        infile >> i;
    }

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
