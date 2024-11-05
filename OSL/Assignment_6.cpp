#include <iostream>
#include <vector>

using namespace std;

// Define structure for Page Table entry
struct PageTable {
    int frame_no;  // Frame number in physical memory
    bool valid;    // Validity of the page (true if the page is in memory, false otherwise)
};

// Function to check if a page is present in the page table
bool isPagePresent(vector<PageTable>& PT, int page) {
    return PT[page].valid;
}

// Function to update the page table with the given page and frame information
void updatePageTable(vector<PageTable>& PT, int page, int fr_no, bool status) {
    PT[page].valid = status;    // Update validity status
    PT[page].frame_no = fr_no;  // Update frame number
}

// Function to print the current content of the frames
void printFrameContent(const vector<int>& frame) {
    for (int i : frame) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    int n, no_of_frame, page_fault = 0, current = 0;
    bool flag = false; // Flag to indicate if frames are filled at least once

    // Input number of pages in the reference string
    cout << "Enter the number of pages: ";
    cin >> n;
    vector<int> reference_string(n);

    // Input the reference string
    cout << "Enter the reference string: ";
    for (int& page : reference_string) {
        cin >> page;
    }

    // Input number of frames available in memory
    cout << "\nEnter the number of frames: ";
    cin >> no_of_frame;
    vector<int> frame(no_of_frame, -1);  // Initialize frames to -1 (indicating empty frames)

    vector<PageTable> PT(50, { -1, false });  // Page table for up to 50 pages initialized to invalid

    cout << "\n*** Frame content at different times: ***\n";

    // Process each page in the reference string
    for (int page : reference_string) {
        if (!isPagePresent(PT, page)) { // If page fault occurs
            page_fault++;  // Increment page fault counter
            if (!flag && current < no_of_frame) { // Fill empty frames if available
                frame[current] = page;
                printFrameContent(frame); // Print current frame content
                updatePageTable(PT, page, current, true); // Update page table
                current++; // Move to next frame slot
                if (current == no_of_frame) { // If all frames are filled, reset current
                    current = 0;
                    flag = true;
                }
            } else { // Replace pages in a circular manner (FIFO)
                updatePageTable(PT, frame[current], -1, false); // Invalidate the current page in the table
                frame[current] = page; // Load new page into frame
                printFrameContent(frame); // Print current frame content
                updatePageTable(PT, page, current, true); // Update page table for the new page
                current = (current + 1) % no_of_frame; // Move to next frame slot
            }
        }
    }

    // Print the results
    cout << "\nTotal number of page faults = " << page_fault << endl;
    cout << "Page fault ratio = " << static_cast<float>(page_fault) / n << endl;
    cout << "Page hit ratio = " << static_cast<float>(n - page_fault) / n << endl;

    return 0;
}
