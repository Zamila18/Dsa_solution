#include <bits/stdc++.h>
using namespace std;

// Function to perform binary search to find the correct position
int binarySearch(vector<int>& arr, int key, int low, int high) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) return mid + 1;
        else if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return low;  // Return the position where the element should be inserted
}

// Function to perform Insertion Sort with Binary Search
void insertionSortBinarySearch(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int pos = binarySearch(arr, key, 0, i - 1);
        // Shift elements to make space for the key
        for (int j = i; j > pos; j--) {
            arr[j] = arr[j - 1];
        }
        arr[pos] = key;
    }
}

int main() {
    vector<int> arr = {5, 1, 3, 2, 4};
    insertionSortBinarySearch(arr);

    cout << "Sorted Array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
