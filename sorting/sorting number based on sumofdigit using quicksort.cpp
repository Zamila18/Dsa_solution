#include <bits/stdc++.h>
using namespace std;

// Function to calculate the sum of digits of a number
int sumOfDigits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

// Comparison function for QuickSort
bool compare(int a, int b) {
    int sumA = sumOfDigits(a), sumB = sumOfDigits(b);
    if (sumA != sumB) return sumA < sumB;  // First compare by sum of digits
    return a < b;  // If sums are equal, compare the numbers themselves
}

// QuickSort function
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (compare(arr[j], pivot)) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        quickSort(arr, low, i);
        quickSort(arr, i + 2, high);
    }
}

int main() {
    vector<int> arr = {21, 13, 25, 31, 15};  // Example array
    quickSort(arr, 0, arr.size() - 1);

    cout << "Sorted Array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
