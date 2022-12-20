// Copyright (c) 2022.
// Editor By Chizer


//单向链表

#include<iostream>
#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OVERFLOW (-2)
using namespace std;

typedef int Status;
typedef int ElemType;

//单向链表
typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;

//初始化新结点
LNode* MakeLNode() {
    LNode *p = (LNode*) malloc(sizeof (LNode));
    if(!p) exit(OVERFLOW);
    p->next = nullptr;
    return p;
}
//创建单向链表
LinkList CreateLinkList(int n) {
    LinkList linkList = MakeLNode();    //创建头结点
    linkList->data = 0; //头结点元素充当计数位
    for(int i = 0; i < n; ++i) {
        LNode *p = MakeLNode();
        cin >> p->data;
        p->next = linkList->next;
        linkList->next = p;
        linkList->data++;   //链表元素个数加一
    }
    return linkList;
}

//销毁单向链表
Status DestroyLinkList(LinkList &L) {
    LNode *p = L->next;
    while (p != nullptr) {
        LNode *q = p;
        p = p->next;
        free(q);
    }
    free(L);    //释放头结点指针
    L = nullptr;
    return OK;
}

//输出单向链表
Status PrintLinkList(LinkList L) {
    LNode *p = L->next;
    while (p != nullptr) {
        cout << p->data << ' ';
        p = p->next;
    }
    return OK;
}

//在单向链表中,给定序号i,返回该位置下的结点指针
LNode* GetLNodeElem(LinkList L, int i) {
    LNode *p = L->next;
    int j = 1;
    while (j != i) {
        p = p->next;
        j++;
    }
    return p;
}

//单向链表排序(选择排序),按升序排序
Status LinkListSort(LinkList &L) {
    LNode *p = L->next; //第一个元素
    while (p != nullptr) {
        LNode *minNode = p; //最小元素结点
        LNode *q = p;
        while (q->next != nullptr) {    //选择自q及之后的最小元素
            if(minNode->data > q->next->data) {
                minNode = q->next;
            }
            q = q->next;
        }
        ElemType temp = minNode->data;  //交换元素
        minNode->data = p->data;
        p->data = temp;
        p = p->next;
    }
    return OK;
}

//单项链表的各种操作
void Test01() {
    //创建单向链表
    LinkList linkList{};
    int n; //单向链表长度
    cout << "Enter the length of LinkList:";
    cin >> n;
    cout << "Enter the elements(reverse input):";  //逆序输入元素
    linkList = CreateLinkList(n);

    //输出
    cout << "The elements are:";
    PrintLinkList(linkList);
    cout << endl;

    //给定i寻找结点
    int i;
    cout << "Choose the number of Node you want to get:";
    cin >> i;
    LNode *p1 = GetLNodeElem(linkList, i);
    cout << "The " << i << " Node is:" << p1->data << '\n';

    //按升序进行排序
    LinkListSort(linkList);
    cout << "LinkList is sorted.\n";
    cout << "Now the elements are:";
    PrintLinkList(linkList);

    //销毁单向链表
    DestroyLinkList(linkList);
}

int main() {
    Test01();
};
