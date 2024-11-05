#include <iostream>
#include <vector>

using namespace std;

int np, nr;
vector<vector<int>> max_matrix(10, vector<int>(10)), allocation(10, vector<int>(10)), need(10, vector<int>(10));
vector<int> avail(10);

void read_matrix(vector<vector<int>> &matrix) {
    for(int i = 0; i < np; i++) {
        for(int j = 0; j < nr; j++) {
            cin >> matrix[i][j];
        }
    }
}

void display_matrix(const vector<vector<int>> &matrix) {
    for(int i = 0; i < np; i++) {
        for(int j = 0; j < nr; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void calculate_need() {
    for(int i = 0; i < np; i++) {
        for(int j = 0; j < nr; j++) {
            need[i][j] = max_matrix[i][j] - allocation[i][j];
        }
    }
}

void banker() {
    vector<int> finish(np, 0), safe_seq(np, 0);
    int k = 0;

    while(k < np) {
        bool flag = false;

        for(int i = 0; i < np; i++) {
            if(finish[i] == 0) {
                bool can_proceed = true;
                for(int j = 0; j < nr; j++) {
                    if(need[i][j] > avail[j]) {
                        can_proceed = false;
                        break;
                    }
                }

                if(can_proceed) {
                    finish[i] = 1;
                    safe_seq[k++] = i;
                    for(int j = 0; j < nr; j++) {
                        avail[j] += allocation[i][j];
                    }
                    flag = true;
                }
            }
        }

        if(!flag) {
            cout << "\nThe system is in deadlock\n";
            return;
        }
    }

    cout << "\nThe process is in a safe state\n";
    for(int i = 0; i < np; i++) {
        cout << "Process " << safe_seq[i] << " has finished\n";
    }
}

int main() {
    cout << "Enter the number of processes: ";
    cin >> np;
    cout << "Enter the number of resources: ";
    cin >> nr;

    cout << "\nEnter the allocation matrix:\n";
    read_matrix(allocation);

    cout << "\nEnter the max matrix:\n";
    read_matrix(max_matrix);

    cout << "\nEnter the available resources:\n";
    for(int j = 0; j < nr; j++) {
        cin >> avail[j];
    }

    cout << "\n********* Entered Data *************\n\n";
    cout << "Allocation Matrix:\n";
    display_matrix(allocation);
    cout << "\nMax Matrix:\n";
    display_matrix(max_matrix);
    
    cout << "\nAvailable Resources:\n";
    for(int j = 0; j < nr; j++) {
        cout << avail[j] << " ";
    }
    cout << endl;

    calculate_need();
    cout << "\nNeed Matrix:\n";
    display_matrix(need);

    banker();
    cout << endl;

    return 0;
}
