// Copyright (c) 2022.
// Editor By Chizer

//堆排序（大顶堆）

#include<iostream>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW (-2)
using namespace std;

typedef int Status;
typedef int ElemType;

typedef struct {
    ElemType* elem;
    int length;
    int listsize;
}SqList;

//初始化线性表
Status InitSqList(SqList &L, int n) {
    L.elem = (ElemType*) malloc((n + 1) * sizeof (ElemType));   //0号元素留空
    if(!L.elem) exit(OVERFLOW);
    L.length = 0;
    L.listsize = n + 1;
}
//创建长度为n的线性表
Status CreateSqList(SqList &L, int n) {
    InitSqList(L, n);
    for(int i = 1; i <= n; ++i) {
        cin >> L.elem[i];
        L.length++;
    }
    return OK;
}

typedef SqList HeapType;

//将H.elem[s..m]成为大顶堆
void HeapAdjust(HeapType &H, int s, int m) {
    ElemType rc = H.elem[s];
    for(int j = 2 * s; j <= m; j *= 2) {
        if(j < m && H.elem[j] < H.elem[j + 1]) ++j;
        if(rc >= H.elem[j]) break;
        H.elem[s] = H.elem[j];
        s = j;
    }
    H.elem[s] = rc;
}

//堆排序
void HeapSort(HeapType &H) {
    for(int i = H.length/2; i > 0; --i) {
        HeapAdjust(H, i, H.length); //将1到H.length建成大顶堆
    }
    for(int i = H.length; i > 1; --i) {
        ElemType tmp = H.elem[1];
        H.elem[1] = H.elem[i];
        H.elem[i] = tmp;
        HeapAdjust(H, 1, i - 1);    //将1到i-1重新调整为大顶堆
    }
}

//打印线性表
void PrintSqList(SqList L) {
    for(int i = 1; i <= L.length; ++i) {
        cout << L.elem[i] << ' ';
    }
}

int main() {
    SqList list{};
    int n;
    cout << "Enter the length of SqList:\n";
    cin >> n;
    cout << "Enter the elems:\n";
    CreateSqList(list, n);
    cout << "Init Success!\nThe elems are:\n";
    PrintSqList(list);
    HeapSort(list);
    cout << "\nHeapSort Success!\nNow the SqList:\n";
    PrintSqList(list);
}