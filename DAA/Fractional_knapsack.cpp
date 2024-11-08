#include <bits/stdc++.h>
using namespace std;

struct Item {
    int value;
    int weight;
};

void merge(Item arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Item l[n1], r[n2];

    for (int i = 0; i < n1; i++) {
        l[i] = arr[left + i];
    }

    for (int j = 0; j < n2; j++) {
        r[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        double r1 = (double)l[i].value / (double)l[i].weight;
        double r2 = (double)r[j].value / (double)r[j].weight;

        if (r1 > r2) {
            arr[k] = l[i];
            i++;
        } else {
            arr[k] = r[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = l[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = r[j];
        j++;
        k++;
    }
}

void mergeSort(Item arr[], int left, int right) {
    if (left < right) {
        int mid = (left) + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

double fractionnalKnap(Item arr[], int w, int n) {
    mergeSort(arr, 0, n - 1);

    int currWeight = 0;
    double Finalvalue = 0;

    for (int i = 0; i < n; i++) {
        if (currWeight + arr[i].weight <= w) {
            currWeight += arr[i].weight;
            Finalvalue += arr[i].value;
        } else {
            int remain = w - currWeight;
            Finalvalue += (arr[i].value / (double)arr[i].weight * (double)(remain));
            break;
        }
    }
    return Finalvalue;
}

int main() {
    int n, weight;
    cout << "Enter the number of items: ";
    cin >> n;

    Item arr[n];
    cout << "Enter the maximum weight of the knapsack: ";
    cin >> weight;

    cout << "Enter the value and weight of each item:\n";
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << " - Value: ";
        cin >> arr[i].value;
        cout << "Item " << i + 1 << " - Weight: ";
        cin >> arr[i].weight;
    }

    double ans = fractionnalKnap(arr, weight, n);

    cout << "\n|-------------------------------|\n";
    cout << "| Item | Value | Weight |\n";
    cout << "|-------------------------------|\n";
    for (int i = 0; i < n; i++) {
        cout << "| " << setw(4) << i + 1 << " | " << setw(5) << arr[i].value
             << " | " << setw(6) << arr[i].weight << " |\n";
    }
    cout << "|-------------------------------|\n";
    cout << "The maximum value achievable is: " << fixed << setprecision(2) << ans << endl;

    return 0;
}
