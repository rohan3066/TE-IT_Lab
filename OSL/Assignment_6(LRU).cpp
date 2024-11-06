#include <iostream>
#include <vector>
#include <climits>
using namespace std;
struct PageTable {
    int frame_no;            // Frame number in physical memory
    int last_time_of_access; // Last access time for LRU
    bool valid;              // Validity of the page (true if the page is in memory, false otherwise)
};

// Function to check if a page is present in the page table
bool isPagePresent(vector<PageTable>& PT, int page) {
    return PT[page].valid;
}

// Function to update the page table with the given page, frame number, and access time
void updatePageTable(vector<PageTable>& PT, int page, int fr_no, bool status, int access_time) {
    PT[page].valid = status;
    if (status) {
        PT[page].last_time_of_access = access_time;
        PT[page].frame_no = fr_no;
    }
}

// Function to print the current content of the frames
void printFrameContents(const vector<int>& frame) {
    for (size_t i = 0; i < frame.size(); i++) {
        cout << "Frame " << i + 1 << ": " << frame[i] << endl;
    }
}

// Function to find the least recently used (LRU) page index in the frame array
void searchLRUPage(vector<PageTable>& PT, const vector<int>& frame, int & LRU_page_index) {
    int min_time = INT_MAX;
    for (size_t i = 0; i < frame.size(); i++) {
        if (PT[frame[i]].last_time_of_access < min_time) {
            min_time = PT[frame[i]].last_time_of_access;
            LRU_page_index = i;
        }
    }
}

int main() {
    int n, no_of_frames, page_fault = 0, current = 0;
    bool flag = false;

    cout << "\nEnter the number of pages: ";
    cin >> n;
    vector<int> reference_string(n);

    cout << "\nEnter the reference string: ";
    for (int& page : reference_string) {
        cin >> page;
    }

    cout << "\nEnter the number of frames: ";
    cin >> no_of_frames;
    vector<int> frame(no_of_frames, -1);  // Initialize frames to -1 (indicating empty frames)

    vector<PageTable> PT(50, { -1, 0, false });  // Page table for up to 50 pages, initialized to invalid

    cout << "\n**** Frame contents at different times ****\n";

    for (int i = 0; i < n; i++) {
        if (!isPagePresent(PT, reference_string[i])) { // If page fault occurs
            page_fault++;  // Increment page fault counter

            if (!flag && current < no_of_frames) { // Fill empty frames if available
                frame[current] = reference_string[i];
                printFrameContents(frame); // Print current frame content
                updatePageTable(PT, reference_string[i], current, true, i); // Update page table
                current++;

                if (current == no_of_frames) { // If all frames are filled, set flag to true
                    flag = true;
                }
            } else { // Replace pages using LRU policy
                int LRU_page_index;
                searchLRUPage(PT, frame, LRU_page_index);
                frame[LRU_page_index] = reference_string[i]; // Load new page into the LRU frame
                printFrameContents(frame); // Print current frame content
                updatePageTable(PT, reference_string[i], LRU_page_index, true, i); // Update page table for the new page
            }
            PT[reference_string[i]].last_time_of_access = i; // Update last access time
        }
    }

    // Print the results
    cout << "\nTotal number of page faults = " << page_fault << endl;
    cout << "Page fault ratio = " << static_cast<float>(page_fault) / n << endl;
    cout << "Page hit ratio = " << static_cast<float>(n - page_fault) / n << endl;

    return 0;
}
