#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Sequential Bubble Sort
void sequentialBubbleSort(vector<int>& arr, int n) {

    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            if (arr[j] > arr[j + 1]) {

                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallel Bubble Sort using OpenMP
void parallelBubbleSort(vector<int>& arr, int n) {

    for (int i = 0; i < n; i++) {

        // Odd phase
        #pragma omp parallel for
        for (int j = 1; j < n - 1; j += 2) {

            if (arr[j] > arr[j + 1]) {

                swap(arr[j], arr[j + 1]);
            }
        }

        // Even phase
        #pragma omp parallel for
        for (int j = 0; j < n - 1; j += 2) {

            if (arr[j] > arr[j + 1]) {

                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Print array
void printArray(vector<int>& arr, int n) {

    for (int i = 0; i < n; i++) {

        cout << arr[i] << " ";
    }

    cout << endl;
}

int main() {

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr1(n), arr2(n);

    cout << "Enter elements:" << endl;

    for (int i = 0; i < n; i++) {

        cin >> arr1[i];

        arr2[i] = arr1[i];
    }

    // Sequential Bubble Sort Timing
    double start1 = omp_get_wtime();

    sequentialBubbleSort(arr1, n);

    double end1 = omp_get_wtime();

    // Parallel Bubble Sort Timing
    double start2 = omp_get_wtime();

    parallelBubbleSort(arr2, n);

    double end2 = omp_get_wtime();

    cout << "\nSequential Bubble Sort Result:" << endl;
    printArray(arr1, n);

    cout << "Sequential Execution Time: "
         << (end1 - start1) << " seconds" << endl;

    cout << "\nParallel Bubble Sort Result:" << endl;
    printArray(arr2, n);

    cout << "Parallel Execution Time: "
         << (end2 - start2) << " seconds" << endl;

    return 0;
}
