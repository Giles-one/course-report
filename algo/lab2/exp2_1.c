// gcc exp2_1.c && ./a.out 
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define swap(a, b) do{ typeof(a) t; t=a; a=b; b=t; }while(0)

/* generate a random in [from, to] */
int randint(int from, int to) {
    int ret = rand();
    ret = from + ret%(to-from+1);
    return ret;
}

/* initialize the seed */
static void __attribute__ ((constructor)) init_seed() {
    srand((unsigned int)time(NULL));
}

/* partition */
int Partition(int a[], int low, int high) {
    int save = a[low];
    while(low<high) {
        while(low<high && a[high]>=save) high--;
        if(low<high) {
            a[low] = a[high];
            low++;
        }
        while(low<high && a[low]<save) low++;
        if(low<high) {
            a[high] = a[low];
            high--;
        }
    }
    a[low] = save;
    return low;
}

/* random partition */
int Rpartition(int a[], int low, int high) {
    int i = randint(low, high);
    swap(a[low], a[i]);
    Partition(a, low, high);
}

void RQuickSort(int a[], int low, int high) {
    if(low < high) {
        int q = Rpartition(a, low, high);
        RQuickSort(a, low, q-1);
        RQuickSort(a, q+1, high);
    }
}

int randomizedSelect(int a[], int low, int high, int findIndex) {
    if(low==high)
        return a[low];
    int i = Rpartition(a, low, high);
    int find = i+1-low;
    if(findIndex<=find) {
        randomizedSelect(a, low, i, findIndex);
    } else {
        randomizedSelect(a, i+1, high, findIndex-find);
    }
}

int main() {

    int a[] = {49,2 ,100, 23, 78,3, 7,38, 65, 97, 76, 13, 27, 49};
    int num = sizeof(a)/4;
    printf("%d\n", randomizedSelect(a, 0, num-1, 5));
    return 0;
}