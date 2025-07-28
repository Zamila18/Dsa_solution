#include <bits/stdc++.h>
using namespace std;

// Function to find the first occurrence of the element
int firstOccurrence(vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1, result = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            result = mid;
            high = mid - 1;  // Move left to find the first occurrence
        } else if (arr[mid] > target) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return result;
}

// Function to find the last occurrence of the element
int lastOccurrence(vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1, result = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            result = mid;
            low = mid + 1;  // Move right to find the last occurrence
        } else if (arr[mid] > target) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return result;
}

int main() {
    vector<int> arr = {1, 2, 2, 2, 3, 4, 5};
    int target = 2;

    cout << "First Occurrence: " << firstOccurrence(arr, target) << endl;
    cout << "Last Occurrence: " << lastOccurrence(arr, target) << endl;
    return 0;
}
