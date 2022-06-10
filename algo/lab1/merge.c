#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) {(a<b)?(a):(b)}

void display(int *A, int n) {
    for (int i=0; i<n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

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

int main() {
    int raw[10] = {45, 50, 778, 48, 716, 4, 0, 422, 14, 90 };
    MergeSort(raw, 10);
    display(raw, 10);
}