#include <bits/stdc++.h>
using namespace std;

int findFirstOneIndex(vector<int>& arr) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == 1 && (mid == 0 || arr[mid-1] == 0)) {
            return mid;  // First occurrence of 1
        } else if (arr[mid] == 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;  // No 1's in the array
}

int main() {
    vector<int> arr = {0, 0, 1, 1, 1};  // Example array
    int firstOneIndex = findFirstOneIndex(arr);
    if (firstOneIndex != -1) {
        cout << "Sum of the array is: " << arr.size() - firstOneIndex << endl;
    } else {
        cout << "Sum of the array is: 0" << endl;  // All 0's case
    }
    return 0;
}
