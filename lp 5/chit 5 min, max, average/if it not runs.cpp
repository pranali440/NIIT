#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter elements:" << endl;

    for (int i = 0; i < n; i++) {

        cin >> arr[i];
    }

    int minimum = arr[0];
    int maximum = arr[0];
    int sum = 0;

    // Parallel Sum
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {

        sum += arr[i];
    }

    // Parallel Min and Max
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {

        #pragma omp critical
        {
            if (arr[i] < minimum) {

                minimum = arr[i];
            }

            if (arr[i] > maximum) {

                maximum = arr[i];
            }
        }
    }

    double average = (double)sum / n;

    cout << "\nMinimum Element: " << minimum << endl;

    cout << "Maximum Element: " << maximum << endl;

    cout << "Sum of Elements: " << sum << endl;

    cout << "Average of Elements: " << average << endl;

    return 0;
}
