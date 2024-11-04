#include <iostream>
#include <vector>
#include <unistd.h> // For fork(), getpid(), getppid()
#include <sys/types.h>

using namespace std;

void merge(vector<int>& arr, int low, int mid, int high);
void mergeSort(vector<int>& arr, int low, int high);

void merge(vector<int>& arr, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    // Temporary arrays
    vector<int> left(n1), right(n2);

    // Copy data to temp arrays
    for (int i = 0; i < n1; i++)
        left[i] = arr[low + i];
    for (int j = 0; j < n2; j++)
        right[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[low..high]
    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of left[], if any
    while (i < n1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    // Copy remaining elements of right[], if any
    while (j < n2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;

        // Sort first and second halves
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);

        // Merge the sorted halves
        merge(arr, low, mid, high);
    }
}

void display(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << "\t";
    }
    cout << endl;
}

int main() {
    int pid, child_pid;
    int size;

    cout << "Enter the number of Integers to Sort: ";
    cin >> size;

    vector<int> arr(size);

    for (int i = 0; i < size; i++) {
        cout << "Enter number " << (i + 1) << ": ";
        cin >> arr[i];
    }

    cout << "Your Entered Integers for Sorting" << endl;
    display(arr);

    pid = getpid();
    cout << "Current Process ID is : " << pid << endl;

    cout << "[ Forking Child Process ... ] " << endl;
    child_pid = fork();

    if (child_pid < 0) {
        cout << "\nChild Process Creation Failed!!!!" << endl;
        exit(-1);
    } else if (child_pid == 0) {
        cout << "\nThe Child Process\n";
        cout << "Child process ID: " << getpid() << endl;
        cout << "Parent of child process ID: " << getppid() << endl;
        cout << "Child is sorting the list of Integers by MERGE SORT:" << endl;
        mergeSort(arr, 0, size - 1);
        cout << "The sorted List by Child:" << endl;
        display(arr);
        cout << "Child Process Completed ..." << endl;
        sleep(10);
        cout << "Parent of child process ID after sleep: " << getppid() << endl;
    } else {
        cout << "Parent process ID: " << getpid() << " started" << endl;
        cout << "Parent of parent process ID: " << getppid() << endl;
        sleep(30);
        cout << "The Parent Process" << endl;
        cout << "Parent " << pid << " is sorting the list of Integers by MERGE SORT" << endl;
        mergeSort(arr, 0, size - 1);
        cout << "The sorted List by Parent:" << endl;
        display(arr);
        cout << "Parent Process Completed ..." << endl;
    }

    return 0;
}
