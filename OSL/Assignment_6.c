#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Define structure for Page Table entry
struct PageTable {
    int frame_no;  // Frame number in physical memory
    bool valid;    // Validity of the page (true if the page is in memory, false otherwise)
};

// Function to check if a page is present in the page table
bool isPagePresent(struct PageTable PT[], int page) {
    if (PT[page].valid == true) {
        return true;
    }
    return false;
}

// Function to update the page table with the given page and frame information
void updatePageTable(struct PageTable PT[], int page, int fr_no, int status) {
    PT[page].valid = status;    // Update validity status
    PT[page].frame_no = fr_no;  // Update frame number
}

// Function to print the current content of the frames
void printFrameContent(int frame[], int no_frame) {
    for (int i = 0; i < no_frame; i++) {
        printf("%d ", frame[i]);
    }
    printf("\n");
}

int main() {
    int i, n, no_of_frame, page_fault = 0, current = 0;
    bool flag = false; // Flag to indicate if frames are filled at least once

    // Input number of pages in the reference string
    printf("Enter the number of pages: ");
    scanf("%d", &n);
    int reference_string[n];

    // Input the reference string
    printf("Enter the reference string: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &reference_string[i]);
    }

    // Input number of frames available in memory
    printf("\nEnter the number of frames: ");
    scanf("%d", &no_of_frame);
    int frame[no_of_frame];

    // Initialize frames to -1 (indicating empty frames)
    for (int i = 0; i < no_of_frame; i++) {
        frame[i] = -1;
    }

    struct PageTable PT[50];  // Page table for up to 50 pages

    // Initialize all page table entries to invalid (not in memory)
    for (int i = 0; i < 50; i++) {
        PT[i].valid = false;
    }

    printf("\n*** Frame content at different times: ***\n");

    // Process each page in the reference string
    for (int i = 0; i < n; i++) {
        if (!isPagePresent(PT, reference_string[i])) { // If page fault occurs
            page_fault++;  // Increment page fault counter
            if (!flag && current < no_of_frame) { // Fill empty frames if available
                frame[current] = reference_string[i];
                printFrameContent(frame, no_of_frame); // Print current frame content
                updatePageTable(PT, reference_string[i], current, 1); // Update page table
                current++; // Move to next frame slot
                if (current == no_of_frame) { // If all frames are filled, reset current
                    current = 0;
                    flag = true;
                }
            } else { // Replace pages in a circular manner (FIFO)
                updatePageTable(PT, frame[current], -1, 0); // Invalidate the current page in the table
                frame[current] = reference_string[i]; // Load new page into frame
                printFrameContent(frame, no_of_frame); // Print current frame content
                updatePageTable(PT, reference_string[i], current, 1); // Update page table for the new page
                current = (current + 1) % no_of_frame; // Move to next frame slot
            }
        }
    }

    // Print the results
    printf("\nTotal number of page faults = %d\n", page_fault);
    printf("Page fault ratio = %.2f\n", (float)page_fault / n);
    printf("Page hit ratio = %.2f\n", (float)(n - page_fault) / n);

    return 0;
}
