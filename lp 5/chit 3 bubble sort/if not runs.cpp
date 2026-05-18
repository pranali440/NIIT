#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void parallelBubbleSort(vector<int>& arr, int n) {

    for (int i = 0; i < n; i++) {

        #pragma omp parallel for
        for (int j = 0; j < n - 1; j++) {

            if (arr[j] > arr[j + 1]) {

                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter elements:" << endl;

    for (int i = 0; i < n; i++) {

        cin >> arr[i];
    }

    parallelBubbleSort(arr, n);

    cout << "Sorted Array:" << endl;

    for (int i = 0; i < n; i++) {

        cout << arr[i] << " ";
    }

    return 0;
}
