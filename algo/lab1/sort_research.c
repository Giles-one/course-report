// gcc sort_research.c -g && ./a.out 10000 1
// gcc sort_research.c -g && ./a.out 10000 0
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define errExit(msg) { perror(msg); exit(EXIT_FAILURE); }
#define min(a, b) {(a<b)?(a):(b)}

#define BUBBLE 0
#define MERGE 1

void print(int data[], int num) {
    for(int i=0; i<num; i++)
        printf("%d\n", data[i]);
}

void BubbleSort(int data[], int num) {
    int tmp;
    for(int i=0; i<num-1; i++) {
        for(int j=0; j<num-1-i; j++) {
            if(data[j] > data[j+1]) {
                tmp = data[j];
                data[j] = data[j+1];
                data[j+1] = tmp;
            }
        }
    }
}
#define min(a, b) {(a<b)?(a):(b)}
void MergeSort(int _raw[], int len) {
    int *tmp;
    int *raw = _raw;
    int *done = malloc(len*sizeof(int));

    for(int i=1; i<len; i*=2) {
        for(int start=0; start<len; start += 2*i) {
            int mid = min(start+i, len);
            int start1 = start;
            int end1 = mid;
            int start2 = mid;
            int end2 = min(start+i+i, len);

            int k = start;
            while(start1<end1 && start2<end2) {
                if (raw[start1] < raw[start2]) {
                    done[k++] = raw[start1++];
                } else {
                    done[k++] = raw[start2++];
                }
            }
            while(start1 < end1)
                done[k++] = raw[start1++];
            while(start2 < end2)
                done[k++] = raw[start2++];

        }
        tmp = raw;
        raw = done;
        done = tmp;
    }
    if (raw != _raw)
        memcpy(_raw, raw, len*sizeof(int));
}

int check(int data[], int num) {
    for(int i=0; i<num-1; i++) {
        if(data[i] > data[i+1])
            return 0;
    }
    return 1;
}

int main(int argc, char* argv[]) {
    int size;
    int type;
    int* data;
    int data_num;
    char path[0x30];

    if (argc != 3) {
        printf("Usage: ./a.out num type \n");
        exit(EXIT_FAILURE);
    }
    size = atoi(argv[1]);
    type = atoi(argv[2]);
    snprintf(path, 0x30, "dataset/data_%d", size);
    
    /* open file */
    FILE *fp = fopen(path, "r");
    if(fp == NULL)
        errExit("fp == NULL");
    fscanf(fp, "%d", &data_num);
    data = malloc(data_num * sizeof(int));
    
    /* fetch date from file */
    int i = 0;
    for (i=0; (fscanf(fp, "%d", &data[i]) != EOF); i++);
    assert(i == data_num);

    clock_t begin;
    clock_t end;

    /* calculate the time */    
    switch(type)
    {
        case BUBBLE:
            begin = clock();
            BubbleSort(data, data_num);
            end = clock();
            break;
        case MERGE:
            begin = clock();
            MergeSort(data, data_num);
            end = clock();
            break;
    }

    /* check data in order */
    assert(check(data, data_num) == 1);

    printf("[*] %s (%d, %f) \n", type?"MergeSort ":"BubbleSort", data_num, (double)(end-begin)/CLOCKS_PER_SEC);
    fclose(fp);
    return 0;
}
