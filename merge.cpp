//Merge Sort
#include <iostream>
#include <vector>
using namespace std;
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    vector<int> L(n1), R(n2);

    // Copy data to temp arrays
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temp arrays back into arr
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    // Copy the remaining elements (if any)
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

// Recursively divide and sort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge sorted halves
        merge(arr, left, mid, right);
    }
}

// Print the array
void printArray(const vector<int>& arr) {
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

// Driver code
int main() {
    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};

    cout << "Original array: ";
    printArray(arr);

    mergeSort(arr, 0, arr.size() - 1);

    cout << "Sorted array: ";
    printArray(arr);

    return 0;
}
