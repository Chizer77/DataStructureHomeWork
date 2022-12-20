// Copyright (c) 2022.
// Editor By Chizer


//二叉排序树的生成和删除

#include<iostream>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW (-2)
using namespace std;

typedef int Status;
typedef int ElemType;

//二叉排序树
typedef struct BSTNode {
    ElemType data;
    struct BSTNode *lchild;
    struct BSTNode *rchild;
}BSTNode, *BSTree;


//查找元素等于e的结点，若查找成功，p则指向该元素结点，否则p指向T的双亲，f指向T的双亲，初始为nullptr
Status SearchBST(BSTree T, ElemType e, BSTree f, BSTree &p) {
    if(!T) {    //查找失败
        p = f;
        return FALSE;
    }
    else if (T->data == e) {    //查找成功
        p = T;
        return TRUE;
    }
    else if (e < T->data) { //元素小于T中元素，则向左子树查找
        return SearchBST(T->lchild, e, T, p);
    }
    else {  //元素大于T中元素，则向右子树查找
        return SearchBST(T->rchild, e, T, p);
    }
}
//二叉排序树的生成
Status InsertBST(BSTree &T, ElemType e) {
    BSTree p;
    if(!SearchBST(T, e, nullptr, p)) {  //查找失败
        BSTree s = (BSTree) malloc(sizeof (BSTNode));   //初始化结点
        s->data = e;
        s->lchild = s->rchild = nullptr;
        if(!p) T = s;   //T为空树
        else if(e < p->data){   //e更小
            p->lchild = s;
        }
        else {  //e更大
            p->rchild = s;
        }
        return TRUE;
    } else{
        return FALSE;
    }
}

Status DeleteNode(BSTree &p) {
    BSTree q;
    if(!p->rchild) {    //右子树为空，仅需重接左子树
        q = p;
        p = p->lchild;
        free(q);
    }
    else if (!p->lchild) {   //仅需重接右子树
        q = p;
        p = p->rchild;
        free(q);
    }
    else {  //左右子树均不空
        q = p;
        BSTree s = p->lchild;   //进入左子树
        while (s->rchild) { //左子树下的右子树尽头
            q = s;
            s = s->rchild;
        }
        p->data = s->data;  //将要删除的结点值赋给根结点p
        //此时s指向要删除的结点"前驱",q指向s的前驱
        if(q != p) q->rchild = s->lchild;   //根节点p的左子树有右孩子,此时s指向最后一个右孩子,q指向s的前驱
        else q->lchild = s->lchild; //根结点p的左子树无右孩子,此时q指向p, s指向p的左子树
        free(s);
    }
    return OK;
}
//二叉排序树的删除
Status DeleteBST(BSTree &T, ElemType e) {
    if(!T)  return FALSE;
    else {
        if(T->data == e) DeleteNode(T);   //找到e所在位置
        else if (e < T->data) { //e小，进左子树
            DeleteBST(T->lchild, e);
        }
        else {  //e大，进右子树
            DeleteBST(T->rchild, e);
        }
    }
}


//凹入表遍历
Status PrintAsTree(BSTree T, int i) {
    if(T) {
        PrintAsTree(T->rchild, i + 1);
        for(int k = 1; k < i; ++k) cout << '\t';
        cout << T->data << '\n';
        PrintAsTree(T->lchild, i + 1);
    }
    return OK;
}

void Test() {
    //二叉排序树的生成
    BSTree tree{};
    int n;
    cout << "Enter the num of BSTNode:\n";
    cin >> n;
    cout << "Enter elements: \n";
    for(int i = 0; i < n; i++) {
        ElemType e;
        cin >> e;
        if(!InsertBST(tree, e)) cout << "Elem " << e << " already exists!";
    }

    //打印
    cout << "The BSTree is:\n";
    PrintAsTree(tree, 1);

    //二叉排序树的删除
    cout << "Enter the elem you need to delete:\n";
    ElemType e;
    cin >> e;
    if(!DeleteBST(tree, e)) cout << "The elem is not exist!\n";
    else cout << "Delete Success!\n";

    //打印
    cout << "Now The BSTree is:\n";
    PrintAsTree(tree, 1);
}
int main() {
    Test();
}
