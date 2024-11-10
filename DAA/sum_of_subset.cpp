#include <iostream>
#include <vector>

using namespace std;

// Function to display a subset
void displaySubset(const vector<int>& subset) {
    cout << "{ ";
    for (int num : subset) {
        cout << num << " ";
    }
    cout << "}" << endl;
}

// Recursive function to find subsets with a given sum
void findSubsets(vector<int>& set, vector<int>& subset, int index, int targetSum, int currentSum) {
    if (currentSum == targetSum) {
        displaySubset(subset);
        return;
    }
    
    // If current sum exceeds target or we've processed all elements, backtrack
    if (currentSum > targetSum || index >= set.size()) {
        return;
    }
    
    // Include the current element in the subset
    subset.push_back(set[index]);
    findSubsets(set, subset, index + 1, targetSum, currentSum + set[index]);
    
    // Exclude the current element from the subset (backtrack)
    subset.pop_back();
    findSubsets(set, subset, index + 1, targetSum, currentSum);
}

int main() {
    vector<int> set = {10, 7, 5, 18, 12, 20, 15}; // Example set of numbers
    int targetSum = 30;                           // Target sum

    cout << "Subsets with sum " << targetSum << " are:" << endl;

    vector<int> subset;
    findSubsets(set, subset, 0, targetSum, 0);

    return 0;
}
