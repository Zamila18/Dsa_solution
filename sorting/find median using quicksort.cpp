#include <bits/stdc++.h>
using namespace std;

// Function to perform partitioning for QuickSort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// QuickSort function
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to find the median
double findMedian(vector<int>& arr) {
    int n = arr.size();
    quickSort(arr, 0, n - 1);  // Sort the array using QuickSort

    if (n % 2 == 0) {
        return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;  // Average of the two middle elements
    } else {
        return arr[n / 2];  // Middle element
    }
}

int main() {
    vector<int> arr = {5, 1, 3, 2, 4};
    cout << "Median: " << findMedian(arr) << endl;
    return 0;
}
