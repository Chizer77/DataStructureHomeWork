// Copyright (c) 2022.
// Editor By Chizer


//线性表

#include<iostream>
#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OVERFLOW (-2)
using namespace std;

typedef int Status;
typedef int ElemType;

//线性表
typedef struct {
    ElemType *elem;
    int length;
    int listsize;
}SqList;

//初始化线性表
Status InitSqList(SqList &L, int n) {
    L.elem = (ElemType*) malloc((n + 1) * sizeof (ElemType));
    if(!L.elem) exit(OVERFLOW);
    L.length = 0;
    L.listsize = n + 1;
    return OK;
}

//销毁线性表
Status DestroySqList(SqList &L) {
    free(L.elem);
    L.length = L.listsize = 0;
    return OK;
}

//创建一个长度为n的线性表
Status CreateSqList(SqList &L, int n) {
    InitSqList(L, n);
    for(int i = 1; i <= n; ++i) {   //0号元素留空
        cin >> L.elem[i];
        L.length++;
    }
    return OK;
}

//给定i返回该位置下的元素
ElemType GetSqListElem(SqList L, int i) {
    return L.elem[i];
}

//线性表排序(直接插入排序)
Status SqListSort(SqList &L) {
    for(int i = 2; i <= L.length; ++i) {
        if(L.elem[i] < L.elem[i - 1]) {
            L.elem[0] = L.elem[i];  //0号元素作哨兵，防止数组下标出界
            L.elem[i] = L.elem[i - 1];  //元素后移
            int j;
            for(j = i - 2; L.elem[0] < L.elem[j]; --j) {    //元素后移
                L.elem[j + 1] = L.elem[j];
            }
            L.elem[j + 1] = L.elem[0];
        }
    }
    return OK;
}

//打印线性表
Status PrintSqList(SqList L) {
    for(int i = 1; i <= L.length; ++i) {
        cout << L.elem[i] << ' ';
    }
    return OK;
}


//创建长度为n的线性表
void Test01() {
    //创建线性表
    SqList sqlist{};
    int n;  //线性表长度n
    cout << "Enter the length of SqList:";
    cin >> n;
    cout << "Enter the elements:";
    CreateSqList(sqlist, n);

    //打印
    cout << "The SqList elements are:";
    PrintSqList(sqlist);
    cout << endl;

    //获取元素
    int i;
    cout << "Choose the number of elem you want to get:";
    cin >> i;
    ElemType elem = GetSqListElem(sqlist, i);
    cout << "The " << i << " elem is:" << elem << '\n';

    //线性表排序
    SqListSort(sqlist); //非递减排序
    cout << "SqList is sorted.\n";
    cout << "Now the elements:";
    PrintSqList(sqlist);
    cout << endl;

    //销毁线性表
    DestroySqList(sqlist);
}

int main() {
    Test01();
};
