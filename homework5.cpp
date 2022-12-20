// Copyright (c) 2022.
// Editor By Chizer

//连接表和连接矩阵的表示方法遍历

#include<iostream>
#include <stack>

#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OVERFLOW (-2)
#define INFINITY INT_MAX //最大值
#define MAX_VERTEX_NUM 20 //最大顶点个数
using namespace std;

typedef int Status;
typedef int VRType; //权值类型
typedef string InfoType;    //弧信息类型
typedef char VertexType;    //顶点类型
typedef enum {DG, DN, UDG, UDN} GraphKind; //有向图，有向网， 无向图，无向网

//邻接矩阵
typedef struct ArcCell{
    VRType adj; //对无权图用1或0表示相邻否，对带权图，则为权值类型
    InfoType *info;
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct {
    VertexType vexs[MAX_VERTEX_NUM];    //顶点向量
    AdjMatrix arcs; //邻接矩阵
    int vexnum, arcnum; //图的顶点数和弧数
    GraphKind kind; //图的种类
}MGraph;

//寻找顶点位置
int LocateMGVex(MGraph G, VertexType v) {
    int i = 0;
    while (G.vexs[i] != v) {
        i++;
    }
    return i;
}

//创建以邻接矩阵为结构的图
Status CreateMGraph(MGraph &G) {
    int kind;
    cout << "Choose the kinds of Graph you need(1 means DG, 2 means DN, 3 means UDG, 4 means UDN):\n";
    cin >> kind;    //图的种类
    switch (kind) {
        case 1:
            G.kind = DG;
            break;
        case 2:
            G.kind = DN;
            break;
        case 3:
            G.kind = UDG;
            break;
        case 4:
            G.kind = UDN;
            break;
        default:
            return ERROR;
    }
    int IncInfo;
    cout << "Enter the vexnum, arcnum and incinfo(1 or 0):";
    cin >> G.vexnum >> G.arcnum >> IncInfo; //IncInfo为0表示弧不含其他信息，1表示弧含其他信息
    cout << "Enter the Vertex:";
    for (int i = 0; i < G.vexnum; ++i) cin >> G.vexs[i]; //输入顶点向量
    int adj;
    if(G.kind == DN || G.kind == UDN) { //图类型为网
        adj = INFINITY;
    }
    else adj = 0;
    for (int i = 0; i < G.vexnum; ++i){
        for (int j = 0; j < G.vexnum; ++j) G.arcs[i][j] = {adj, nullptr};   //初始化邻接矩阵
    }
    cout << "Enter the Arc:\n";
    for(int k = 0; k <G.arcnum; ++k) {
        VertexType v1, v2;
        int w;
        if(G.kind == DN || G.kind == UDN) { //图类型为网
            cin >> v1 >> v2 >> w;   //w为弧的权值
        } else {
            cin >> v1 >> v2;
        }
        int i = LocateMGVex(G, v1);   //v1所在位置
        int j = LocateMGVex(G, v2);   //v2所在位置
        if(G.kind == DN || G.kind == UDN) G.arcs[i][j].adj = w; //若图类型为网则赋权值
        else G.arcs[i][j].adj = 1;  //否则赋1
        if(IncInfo) {
            G.arcs[i][j].info = new string();
            cin >> *G.arcs[i][j].info;  //其余信息
        }
        if(G.kind == UDG ||G.kind == UDN) { //若图的种类是无向的
            G.arcs[j][i].adj = G.arcs[i][j].adj;
            G.arcs[j][i].info = G.arcs[i][j].info;
        }
    }
    return OK;
}

//打印邻接矩阵
void PrintMGraph(MGraph G) {
    for(int i = 0; i < G.vexnum; ++i) {
        for(int j = 0; j < G.vexnum; ++j) {
            cout << G.arcs[i][j].adj << ' ';
        }
        cout << '\n';
    }
}


//邻接表
typedef struct ArcNode{
    int adjvex; //弧指向的顶点位置
    struct ArcNode* nextarc;    //下一条弧指针
    VRType info; //表示权值
    InfoType *otherinfo; //其余信息
}ArcNode;
typedef struct VNode{
    VertexType data;    //顶点向量
    ArcNode *firstarc;  //第一条依附该顶点的弧指针
}VNode, AdjList[MAX_VERTEX_NUM];
typedef struct {
    AdjList vertices;   //邻接表
    int vexnum, arcnum; //顶点数量和弧数量
    GraphKind kind; //图的种类
}ALGraph;

//寻找顶点位置
int LocateALGVex(ALGraph G, VertexType v) {
    int i = 0;
    while (G.vertices[i].data != v) ++i;
    return i;
}

//创建邻接表
Status CreateALGraph(ALGraph &G) {
    int kind;
    cout << "Choose the kinds of Graph you need(1 means DG, 2 means DN, 3 means UDG, 4 means UDN):\n";
    cin >> kind;    //图的种类
    switch (kind) {
        case 1:
            G.kind = DG;
            break;
        case 2:
            G.kind = DN;
            break;
        case 3:
            G.kind = UDG;
            break;
        case 4:
            G.kind = UDN;
            break;
        default:
            return ERROR;
    }
    int IncInfo;
    cout << "Enter the vexnum, arcnum and IncInfo(0 or 1):";
    cin >> G.vexnum >> G.arcnum >> IncInfo; //IncInfo表示其余信息，1表示有，0表示否
    cout << "Enter the Vertex:";
    for(int i = 0; i < G.vexnum; ++i) {   //初始化
        cin >> G.vertices[i].data; //输入顶点向量
        G.vertices[i].firstarc = nullptr;
    }
    cout << "Enter the Arc:\n";
    for(int k = 0; k < G.arcnum; ++k) {
        VertexType v1, v2;
        int w;
        if(G.kind == DN || G.kind == UDN) { //图类型为网
            cin >> v1 >> v2 >> w;   //w为弧的权值
        } else {
            cin >> v1 >> v2;
        }
        int i = LocateALGVex(G, v1);
        int j = LocateALGVex(G, v2);
        ArcNode *p1 = new ArcNode();
        if(G.kind == DN || G.kind == UDN) { //图类型为网
            *p1 = {j, nullptr, w};
        }
        else {
            *p1 = {j, nullptr, 0};
        }
        if(IncInfo) {
            p1->otherinfo = new string();
            cin >> *p1->otherinfo;  //其余信息
        }
        p1->nextarc = G.vertices[i].firstarc;   //连接至邻接表
        G.vertices[i].firstarc = p1;
        //对称弧
        if(G.kind == UDG) {    //图为无向图
            ArcNode *p2 = new ArcNode({i, nullptr, 0});
            p2->nextarc = G.vertices[j].firstarc;
            G.vertices[j].firstarc = p2;
            p2->otherinfo = p1->otherinfo;
        }
        else if(G.kind == UDN){ //图为无向网
            ArcNode *p2 = new ArcNode ({i, nullptr, w});
            p2->nextarc = G.vertices[j].firstarc;
            G.vertices[j].firstarc = p2;
            p2->otherinfo = p1->otherinfo;
        }
    }
    return OK;
}

//销毁邻接表
Status DestroyALGraph(ALGraph &G) {
    for(int i = 0; i < G.vexnum; ++i) {
        ArcNode *p = G.vertices[i].firstarc;
        while (p != nullptr) {
            ArcNode *q = p;
            p = p->nextarc;
            free(q);
        }
    }
    return OK;
}

//打印邻接表
void PrintALGraph(ALGraph G) {
    for(int i = 0; i < G.vexnum; ++i) {
        ArcNode *p = G.vertices[i].firstarc;
        while (p != nullptr) {
            cout << i << ' ' << p->adjvex << '\n';
            p = p->nextarc;
        }
    }
}


//栈结构
#define STACK_INIT_SIZE 100
#define STACKINCREASENT 10

template<typename T>
struct Stack{
    T* base;
    T* top;
    int stacksize;
};
template <typename T>
Status InitStack(Stack<T>& S) {
    S.base = (T*)malloc(STACK_INIT_SIZE*sizeof(T));
    if(!S.base) exit(OVERFLOW);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}
template <typename T>
Status DestroyStack(Stack<T>& S) {
    if(!S.base) return ERROR;
    free(S.base);
    S.base = nullptr;
    S.top = S.base;
    return OK;
}
template <typename T>
Status StackEmpty(Stack<T> S) {
    if(S.base == S.top) return TRUE;
    return FALSE;
}
template <typename T>
T GetTop(Stack<T> S) {
    if(S.base == S.top) return ERROR;
    return *(S.top - 1);
}
template <typename T>
Status Push(Stack<T>& S, T e) {
    if(S.top - S.base >= S.stacksize) {
        S.base = (T*)realloc(S.base, (S.stacksize + STACKINCREASENT) * sizeof (T));
        if(!S.base) exit(OVERFLOW);
        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREASENT;
    }
    *S.top++ = e;
    return OK;
}
template <typename T>
Status Pop(Stack<T>& S, T& e) {
    if(S.top == S.base) return ERROR;
    e = *--S.top;
    return OK;
}

//队列
template <typename T>
struct QNode {
    T data;
    struct QNode<T> *next;
};

template<typename T>
struct LinkQueue{
    QNode<T>* front;
    QNode<T>* rear;
};

template<typename T>
Status InitQueue(LinkQueue<T> &Q) {
    Q.front = Q.rear = (QNode<T>*) malloc(sizeof (QNode<T>));
    if(!Q.front) exit(OVERFLOW);
    Q.front->next = nullptr;
    return OK;
}
template<typename T>
Status DestroyQueue(LinkQueue<T> &Q) {
    while (Q.front) {
        Q.rear = Q.front->next;
        free(Q.front);
        Q.front = Q.rear;
    }
    return OK;
}
template<typename T>
Status QueueEmpty(LinkQueue<T> Q) {
    if(Q.front == Q.rear) return TRUE;
    return FALSE;
}
template<typename T>
Status GetHead(LinkQueue<T> Q, T &e){
    if(Q.front == Q.rear) return ERROR;
    e = Q.front->next->data;
    return OK;
}
template<typename T>
Status EnQueue(LinkQueue<T>& Q, T e) {
    auto* p = (QNode<T> *) malloc(sizeof (QNode<T>));
    if(!p) exit(OVERFLOW);
    p->data = e;
    p->next = nullptr;
    Q.rear->next = p;
    Q.rear = p;
    return OK;
}
template<typename T>
Status DeQueue(LinkQueue<T> &Q, T &e) {
    if(Q.front == Q.rear) return ERROR;
    QNode<T>* p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if(Q.rear == p) Q.rear = Q.front;//防止尾指针成为野指针
    free(p);
    return OK;
}


bool visited[MAX_VERTEX_NUM];   //访问标志数组

//深度优先遍历邻接矩阵无向图G
//递归
void MGDFS(MGraph G, int v) {
    //从第v个顶点出发深度优先遍历
    visited[v] = TRUE;
    cout << G.vexs[v];
    for(int w = 0; w < G.vexnum; ++w) {
        if(G.arcs[v][w].adj && G.arcs[v][w].adj != INFINITY && !visited[w]) MGDFS(G, w);  //对为访问的邻接顶点w递归调用DFS
    }
}
Status DFSMGTraverse_re(MGraph G) {
    for(int i = 0; i < G.vexnum; ++i) visited[i] = FALSE;   //标志数组初始化
    for(int i = 0; i < G.vexnum; ++i) {
        if(!visited[i]) MGDFS(G, i);  //对未访问过的结点进行深度遍历
    }
    return OK;
}
//非递归
Status DFSMGTraverse_un(MGraph G) {
    for(int i = 0; i < G.vexnum; ++i) visited[i] = FALSE;
    Stack<int> stack{};
    InitStack(stack);
    for(int i = 0; i < G.vexnum; ++i) {
        if(!visited[i]) {
            cout << G.vexs[i];
            visited[i] = TRUE;
            Push(stack, i);
            while (!StackEmpty(stack)) {
                bool isPrint = false;
                int v2 = GetTop(stack);
                for(int i = 0; i < G.vexnum; ++i) {
                    if(G.arcs[v2][i].adj && G.arcs[v2][i].adj != INFINITY && !visited[i]){  //对未访问的顶点进行打印
                        cout << G.vexs[i];
                        isPrint = true;
                        visited[i] = TRUE;
                        Push(stack, i);  //当前顶点入栈
                        break;  //输出一个顶点后即退出循环
                    }
                }
                if(!isPrint) {
                    int tmp;
                    Pop(stack, tmp);
                };   //无下一顶点则退栈
            }
        }
    }
    return OK;
}

//广度优先遍历邻接矩阵无向图G
Status BFSMGTraverse(MGraph G) {
    for(int i = 0; i < G.vexnum; ++i) visited[i] = FALSE;   //初始化标志数组
    LinkQueue<int> queue{};
    InitQueue(queue);
    for(int k = 0; k < G.vexnum; ++k) {
        if(!visited[k]) {
            cout << G.vexs[k];
            visited[k] = TRUE;
            EnQueue(queue, k);  //首顶点入队列
            while (!QueueEmpty(queue)) {
                int v;
                DeQueue(queue, v);
                for(int i = 0; i < G.vexnum; ++i) { //对未访问的结点进行广度优先遍历
                    if(G.arcs[v][i].adj && G.arcs[v][i].adj != INFINITY && !visited[i]) {
                        cout << G.vexs[i];
                        visited[i] = TRUE;
                        EnQueue(queue, i);  //访问后入队列
                    }
                }
            }
        }
    }
    return OK;
}

//深度优先遍历邻接表结构无向图G
//递归
//返回v的第一个邻接顶点
int FirstAdjVex(ALGraph G, int v) {
    if(G.vertices[v].firstarc) return G.vertices[v].firstarc->adjvex;
    else return -1;
}
//返回v的且在w点之后的邻接顶点
int NextAdjVex(ALGraph G, int v, int w) {
    ArcNode *p = G.vertices[v].firstarc;
    while (p != nullptr) {
        if(p->adjvex == w && p->nextarc) return p->nextarc->adjvex;
        p = p->nextarc;
    }
    return -1;
}
void ALGDFS(ALGraph G, int v) {
    visited[v] = TRUE;
    cout << G.vertices[v].data;
    for(int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)) {
        if(!visited[w]) ALGDFS(G, w);   //对v的未访问过的邻接结点进行深度遍历
    }
}
Status DFSALGTraverse_re(ALGraph G) {
    for(int i = 0; i < G.vexnum; ++i) visited[i] = FALSE;   //初始化标志数组
    for(int v = 0; v < G.vexnum; ++v) {
        if(!visited[v]) ALGDFS(G, v);   //对未访问的结点进行深度优先遍历
    }
    return OK;
}
//非递归
Status DFSALGTraverse_un(ALGraph G){
    for(int i = 0; i < G.vexnum; ++i) visited[i] = FALSE;   //初始化标志数组
    Stack<int> stack{};
    InitStack(stack);
    for(int i = 0; i < G.vexnum; ++i) {
        if(!visited[i]) {
            cout << G.vertices[i].data;
            visited[i] = TRUE;
            Push(stack, i); //顶点入栈
            while (!StackEmpty(stack)) {
                ArcNode *p = G.vertices[GetTop(stack)].firstarc;
                while (p != nullptr && visited[p->adjvex]) {    //寻找栈顶元素的未被访问的邻接结点
                    p = p->nextarc;
                }
                if(p == nullptr) {  //均已访问
                    int tmp;
                    Pop(stack, tmp);
                }
                else {  //找到未访问的邻接结点
                    cout << G.vertices[p->adjvex].data;
                    visited[p->adjvex] = TRUE;
                    Push(stack, p->adjvex);
                }
            }
        }
    }
    return OK;
}

//广度优先遍历邻接表结构无向图G
Status BFSALGTraverse(ALGraph G) {
    for(int i = 0; i < G.vexnum; ++i) visited[i] = FALSE;   //标志数组初始化
    LinkQueue<int> queue{};
    InitQueue(queue);
    for(int i = 0; i < G.vexnum; ++i) {
        if (!visited[i]) {
            cout << G.vertices[i].data;
            visited[i] = TRUE;
            EnQueue(queue, i);  //首顶点入队列
            while (!QueueEmpty(queue)) {
                int v;
                DeQueue(queue, v);  //取队首顶点
                ArcNode *p = G.vertices[v].firstarc;
                while (p != nullptr && !visited[p->adjvex]) {   //邻接结点未访问
                    cout << G.vertices[p->adjvex].data;
                    visited[p->adjvex] = TRUE;
                    EnQueue(queue, p->adjvex);
                    p = p->nextarc;
                }
            }
        }
    }
    return OK;
}


void Test() {
    //邻接矩阵
    cout << "1. MGraph:\n";
    MGraph graph1{};
    CreateMGraph(graph1);
    cout << "DFSMGTraverse_re: ";
    DFSMGTraverse_re(graph1);
    cout << "\nDFSMGTraverse_un: ";
    DFSMGTraverse_un(graph1);
    cout << "\nBFSMGTraverse: ";
    BFSMGTraverse(graph1);

    //邻接表
    cout << "\n2. ALGraph:\n";
    ALGraph graph2{};
    CreateALGraph(graph2);
    cout << "DFSALGTraverse_re: ";
    DFSALGTraverse_re(graph2);
    cout << "\nDFSALGTraverse_un: ";
    DFSALGTraverse_un(graph2);
    cout << "\nBFSALGTraverse: ";
    BFSALGTraverse(graph2);
    DestroyALGraph(graph2);
}

int main() {
    Test();
}