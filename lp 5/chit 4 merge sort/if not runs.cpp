#include <iostream>
#include <vector>
#include <ctime>
#include <omp.h>

using namespace std;

// Merge Function
void merge(vector<int>& arr, int left, int mid, int right) {

    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {

        if (L[i] <= R[j]) {

            arr[k] = L[i];
            i++;
        }
        else {

            arr[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1) {

        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {

        arr[k] = R[j];
        j++;
        k++;
    }
}

// Sequential Merge Sort
void sequentialMergeSort(vector<int>& arr, int left, int right) {

    if (left < right) {

        int mid = (left + right) / 2;

        sequentialMergeSort(arr, left, mid);

        sequentialMergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Parallel Merge Sort
void parallelMergeSort(vector<int>& arr, int left, int right) {

    if (left < right) {

        int mid = (left + right) / 2;

        #pragma omp parallel sections
        {

            #pragma omp section
            parallelMergeSort(arr, left, mid);

            #pragma omp section
            parallelMergeSort(arr, mid + 1, right);
        }

        merge(arr, left, mid, right);
    }
}

// Print Array
void printArray(vector<int>& arr) {

    for (int i = 0; i < arr.size(); i++) {

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

    // Sequential Timing
    clock_t start1 = clock();

    sequentialMergeSort(arr1, 0, n - 1);

    clock_t end1 = clock();

    // Parallel Timing
    clock_t start2 = clock();

    parallelMergeSort(arr2, 0, n - 1);

    clock_t end2 = clock();

    double seqTime =
        double(end1 - start1) / CLOCKS_PER_SEC;

    double parTime =
        double(end2 - start2) / CLOCKS_PER_SEC;

    cout << "\nSequential Merge Sort:" << endl;
    printArray(arr1);

    cout << "Sequential Time: "
         << seqTime << " seconds" << endl;

    cout << "\nParallel Merge Sort:" << endl;
    printArray(arr2);

    cout << "Parallel Time: "
         << parTime << " seconds" << endl;

    return 0;
}
