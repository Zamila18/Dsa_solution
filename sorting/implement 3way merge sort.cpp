#include <bits/stdc++.h>
using namespace std;

// Merge function to merge three sorted arrays
void mergeThree(vector<int>& arr, int low, int mid1, int mid2, int high) {
    int n1 = mid1 - low + 1;
    int n2 = mid2 - mid1;
    int n3 = high - mid2 + 1;

    vector<int> left1(n1), left2(n2), right(n3);
    for (int i = 0; i < n1; i++) left1[i] = arr[low + i];
    for (int i = 0; i < n2; i++) left2[i] = arr[mid1 + 1 + i];
    for (int i = 0; i < n3; i++) right[i] = arr[mid2 + 1 + i];

    int i = 0, j = 0, k = 0, l = low;
    while (i < n1 && j < n2 && k < n3) {
        if (left1[i] <= left2[j] && left1[i] <= right[k]) {
            arr[l++] = left1[i++];
        } else if (left2[j] <= left1[i] && left2[j] <= right[k]) {
            arr[l++] = left2[j++];
        } else {
            arr[l++] = right[k++];
        }
    }

    while (i < n1) arr[l++] = left1[i++];
    while (j < n2) arr[l++] = left2[j++];
    while (k < n3) arr[l++] = right[k++];
}

// 3-Way Merge Sort function
void mergeSortThreeWay(vector<int>& arr, int low, int high) {
    if (low < high) {
        int mid1 = low + (high - low) / 3;
        int mid2 = mid1 + (high - low) / 3;

        mergeSortThreeWay(arr, low, mid1);
        mergeSortThreeWay(arr, mid1 + 1, mid2);
        mergeSortThreeWay(arr, mid2 + 1, high);

        mergeThree(arr, low, mid1, mid2, high);
    }
}

int main() {
    vector<int> arr = {5, 2, 9, 1, 5, 6};
    mergeSortThreeWay(arr, 0, arr.size() - 1);

    cout << "Sorted Array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
