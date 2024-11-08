#include <bits/stdc++.h>
using namespace std;

void zero_one_knapsack(int p[], int wt[], int m, int n) {
    int dp[n + 1][m + 1];
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= m; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (wt[i - 1] <= w) {
                dp[i][w] = max(p[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    cout << "The maximum value achievable is: " << dp[n][m] << endl;
}

int main() {
    int n, m;
    cout << "Enter the number of items: ";
    cin >> n;
    
    int p[n], wt[n];
    cout << "Enter the maximum capacity of the knapsack: ";
    cin >> m;

    cout << "Enter the values and weights of each item:\n";
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << " - Value: ";
        cin >> p[i];
        cout << "Item " << i + 1 << " - Weight: ";
        cin >> wt[i];
    }

    zero_one_knapsack(p, wt, m, n);

    return 0;
}
