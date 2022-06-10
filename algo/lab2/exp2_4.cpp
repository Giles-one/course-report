// g++ ./exp2_4.cpp && ./a.out 100000
#include<time.h>
#include<iostream>
#include<cmath>
#include<cassert>
 
#define errExit(msg) { perror(msg); exit(EXIT_FAILURE); }
/*
Site: https://www.bilibili.com/video/BV1Po4y117Jk
笨办法 -> 两两遍历，O(n2)
分治：
    - 一维形式， 只在x轴
        + 划分子问题
        + 由中位数(为了子问题平衡)平均划分为S1左, S2右
        + S1, S2分别是子问题
        + 原问题的解等于S1找到的d1, S2找到的d2， 以及横跨在S1，S2上的d3，min{d1, d2, d3}
        + 横跨的d3, 必然是S1中最右边的点与S2中最左边的点的距离
    - 二维形式，x,y 轴
        + 分割使用x轴的中位数，(为什么不分别使用x轴，y轴的中位数，这样的代价是否是值得的)
        + 
*/

using namespace std;
const int M = 50;

class PointX {
public:
    int operator<=(PointX a) const { return (x <= a.x); }
 
    int ID;
    float x, y;
};
 
class PointY {
public:
    int operator<=(PointY a) const { return (y <= a.y); }
 
    int p;      //同一点在数组x中的坐标
    float x, y; //点坐标
};


template<typename Type>
void Copy(Type a[], Type b[], int left, int right) {
    for (int i = left; i <= right; i++)
        a[i] = b[i];
}
template<class Type>
void Merge(Type c[], Type d[], int l, int m, int r) {
    int i = l, j = m + 1, k = l;
    while ((i <= m) && (j <= r)) {
        if (c[i] <= c[j]) {
            d[k++] = c[i++];
        } else {
            d[k++] = c[j++];
        }
    }
 
    if (i > m) {
        for (int q = j; q <= r; q++) {
            d[k++] = c[q];
        }
    } else {
        for (int q = i; q <= m; q++) {
            d[k++] = c[q];
        }
    }
}

template<class Type>
void MergeSort(Type a[], Type b[], int left, int right) {
    if (left < right) {
        int i = (left + right) / 2;
        MergeSort(a, b, left, i);
        MergeSort(a, b, i + 1, right);
        Merge(a, b, left, i, right);  //合并到数组b
        Copy(a, b, left, right);      //复制回数组a
    }
}

 
//平面上任意两点u和v之间的距离可计算如下  
template<class Type>
inline float distance(const Type &u, const Type &v) {
    float dx = u.x - v.x;
    float dy = u.y - v.y;
    return sqrt(dx * dx + dy * dy);
}

void closest(PointX X[], PointY Y[], PointY Z[], int l, int r, PointX &a, PointX &b, float &d) {
    if (r - l == 1) //两点的情形
    {
        a = X[l];
        b = X[r];
        d = distance(X[l], X[r]);
        return;
    }
 
    if (r - l == 2) //3点的情形
    {
        float d1 = distance(X[l], X[l + 1]);
        float d2 = distance(X[l + 1], X[r]);
        float d3 = distance(X[l], X[r]);
 
        if (d1 <= d2 && d1 <= d3) {
            a = X[l];
            b = X[l + 1];
            d = d1;
            return;
        }
 
        if (d2 <= d3) {
            a = X[l + 1];
            b = X[r];
            d = d2;
        } else {
            a = X[l];
            b = X[r];
            d = d3;
        }
        return;
    }
 
    //多于3点的情形，用分治法   
    int m = (l + r) / 2;
    int f = l, g = m + 1;
   
    for (int i = l; i <= r; i++) {
        if (Y[i].p > m) Z[g++] = Y[i];
        else Z[f++] = Y[i];
    }
 
    closest(X, Z, Y, l, m, a, b, d);
    float dr;
 
    PointX ar, br;
    closest(X, Z, Y, m + 1, r, ar, br, dr);
 
    if (dr < d) {
        a = ar;
        b = br;
        d = dr;
    }
 
    Merge(Z, Y, l, m, r);   //重构数组Y
 
    //d矩形条内的点置于Z中  
    int k = l;
    for (int i = l; i <= r; i++) {
        if (fabs(X[m].x - Y[i].x) < d) {
            Z[k++] = Y[i];
        }
    }
 
    //搜索Z[l:k-1]  
    for (int i = l; i < k; i++) {
        for (int j = i + 1; j < k && Z[j].y - Z[i].y < d; j++) {
            float dp = distance(Z[i], Z[j]);
            if (dp < d) {
                d = dp;
                a = X[Z[i].p];
                b = X[Z[j].p];
            }
        }
    }
}
 
bool Cpair2(PointX X[], int n, PointX &a, PointX &b, float &d) {
    if (n < 2) return false;
 
    PointX *tmpX = new PointX[n];
    MergeSort(X, tmpX, 0, n - 1);
 
    PointY *Y = new PointY[n];
    for (int i = 0; i < n; i++) //将数组X中的点复制到数组Y中
    {
        Y[i].p = i;
        Y[i].x = X[i].x;
        Y[i].y = X[i].y;
    }
 
    PointY *tmpY = new PointY[n];
    MergeSort(Y, tmpY, 0, n - 1);
 
    PointY *Z = new PointY[n];
    closest(X, Y, Z, 0, n - 1, a, b, d);
 
    delete[]Y;
    delete[]Z;
    delete[]tmpX;
    delete[]tmpY;
    return true;
}

int main(int argc, char* argv[]) {
    int size;
    int data_num;
    char path[0x30];
    if (argc != 2) {
        printf("Usage: ./a.out num\n");
        exit(EXIT_FAILURE);
    }
    size = atoi(argv[1]);
    snprintf(path, 0x30, "dataset/data_%d.txt", size);
    
    /* open file */
    FILE *fp = fopen(path, "r");
    if(fp == NULL)
        errExit("fp == NULL");
    fscanf(fp, "%d", &data_num);

    PointX* X = new PointX[data_num];

    /* fetch data from file */
    int i = 0;
    for (i=0; (fscanf(fp, "%f%f", &X[i].x, &X[i].y) != EOF);X[i].ID=i,i++);
    assert(i == data_num);

    clock_t begin;
    clock_t end;
    PointX a;
    PointX b;
    float d;
    begin = clock();
    Cpair2(X, data_num, a, b, d);
    end = clock();


    // printf("cost = %ld ms \n", end-begin);
    printf("(%d, %ld) ms \n",data_num, end-begin);
    printf("distance = %f \n", d);
    printf("(%f, %f) <-> (%f, %f) \n\n", a.x, a.y, b.x, b.y);

    fclose(fp);
    return 0;
}
