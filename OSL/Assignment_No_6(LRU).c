#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<limits.h>

struct PageTable{
    int frame_no;
    int last_time_of_access;
    bool valid;
};

bool isPagePresent(struct PageTable PT[],int page){
    if(PT[page].valid==1){
        return true;
    }
    return false;
}

void updatePageTable(struct PageTable PT[],int page,int fr_no,int status,int access_time){
    PT[page].valid=status;

    if(status==1){
        PT[page].last_time_of_access=access_time;
        PT[page].frame_no=fr_no;
    }
}

void printFrameContents(int frame[],int no_of_frames){
    for(int i=0;i<no_of_frames;i++){
        printf("Frame %d: %d\n",i+1,frame[i]);

    }
}

void searchLRUPage(struct PageTable PT[],int frame[],int no_of_frames,int *LRU_page_index){
    int min=INT_MAX;
    for(int i=0;i<no_of_frames;i++){
        if(PT[frame[i]].last_time_of_access<min){
            min=PT[frame[i]].last_time_of_access;
            *LRU_page_index=i;
        }
    }

}


int main(){
    int i=0,n,no_of_frames,page_fault=0,current=0;
    bool flag=false;
    printf("\n Enter the no of page :\n");
    scanf("%d",&n);
    int referance_string[n];
    printf("\n Enter the referance string :\n");
    for(i=0;i<n;i++){
        scanf("%d",&referance_string[i]);
    }

    printf("\n Enter no of frames:");
    scanf("%d",&no_of_frames);
    int frame[no_of_frames];

    for(int i=0;i<no_of_frames;i++){
        frame[i]=-1;
    }
    struct PageTable PT[50];
    for(int i=0;i<50;i++){
        PT[i].valid=0;
    }
    printf("\n ****The contents inside the frame array at different time****\n");
    for(int i=0;i<n;i++){
        if(!(isPagePresent(PT,referance_string[i]))){
            page_fault++;
            if(flag==false && current<no_of_frames){
                frame[current]=referance_string[i];
                printFrameContents(frame,no_of_frames);
                updatePageTable(PT,referance_string[i],current,1,i);
                current++;

                if(current==no_of_frames){
                    flag=true;

                }
            }
            else{
                int LRU_page_index;
                searchLRUPage(PT,frame,no_of_frames,&LRU_page_index);
                frame[LRU_page_index]=referance_string[i];
                printFrameContents(frame,no_of_frames);
                updatePageTable(PT,referance_string[i],LRU_page_index,1,i);

            }
            PT[referance_string[i]].last_time_of_access=i;
        }
    }

    printf("\nTotal number of page faults = %d\n", page_fault);
    printf("Page fault ratio = %.2f\n", (float)page_fault / n);
    printf("Page hit ratio = %.2f\n", (float)(n - page_fault) / n);

    return 0;
}
