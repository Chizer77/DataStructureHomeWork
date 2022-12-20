// Copyright (c) 2022.
// Editor By Chizer

//邻接矩阵和邻接表的相互转换

#include<iostream>
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

//邻接矩阵转换为邻接表
Status MGtoALG(MGraph G, ALGraph &newGraph) {
    newGraph.kind = G.kind;
    newGraph.vexnum = G.vexnum;
    newGraph.arcnum = G.arcnum;
    for(int i = 0; i < G.vexnum; ++i) {
        newGraph.vertices[i].data = G.vexs[i];    //赋值顶点向量
        newGraph.vertices[i].firstarc = nullptr;
    }
    //赋值弧
    for(int i = 0; i < G.vexnum; ++i) {
        for(int j = 0; j < G.vexnum; ++j) {
            if(G.kind == DN || G.kind == UDN) { //图类型为网
                if(G.arcs[i][j].adj != INFINITY) {  //弧不为空
                    ArcNode *p = new ArcNode ({j, nullptr, G.arcs[i][j].adj, G.arcs[i][j].info});
                    p->nextarc = newGraph.vertices[i].firstarc;
                    newGraph.vertices[i].firstarc = p;
                }
            }
            else {  //图类型为图
                if(G.arcs[i][j].adj) {  //弧不为空
                    ArcNode *p = new ArcNode ({j, nullptr, 0, G.arcs[i][j].info});
                    p->nextarc = newGraph.vertices[i].firstarc;
                    newGraph.vertices[i].firstarc = p;
                }
            }
        }
    }
    return OK;
}

//邻接表转换为邻接矩阵
Status ALGtoMG(ALGraph G, MGraph &newGraph) {
    newGraph.kind = G.kind;
    newGraph.vexnum = G.vexnum;
    newGraph.arcnum = G.arcnum;
    for(int i = 0; i < G.vexnum; ++i) newGraph.vexs[i] = G.vertices[i].data;    //赋值顶点向量
    int adj;
    if(G.kind == DN || G.kind == UDN) { //图类型为网
        adj = INFINITY;
    }
    else adj = 0;
    for (int i = 0; i < G.vexnum; ++i){ //初始化邻接矩阵的弧
        for (int j = 0; j < G.vexnum; ++j) newGraph.arcs[i][j] = {adj, nullptr};
    }
    for(int i = 0; i < G.vexnum; ++i) { //赋值弧
        ArcNode *p = G.vertices[i].firstarc;
        while (p != nullptr) {
            if(G.kind == DN ||G.kind == UDN) {  //图类型为网则赋值权值，否则赋值1表示相邻
                newGraph.arcs[i][p->adjvex].adj = p->info;
                newGraph.arcs[i][p->adjvex].info = p->otherinfo;    //其余信息
            }
            else {
                newGraph.arcs[i][p->adjvex].adj = 1;
                newGraph.arcs[i][p->adjvex].info = p->otherinfo;
            }
            p = p->nextarc;
        }
    }
    return OK;
}

Status Test() {
    int structure;
    cout << "What structure of graph you want to create?(0 means MGraph, 1 means ALGraph)\n";
    cin >> structure;
    int kind;
    cout << "Choose the kinds of Graph you need(1 means DG, 2 means DN, 3 means UDG, 4 means UDN):\n";
    cin >> kind;    //图的种类
    if(structure) {
        //创建邻接表为结构的图
        ALGraph graph{};
        switch (kind) {
            case 1:
                graph.kind = DG;
                break;
            case 2:
                graph.kind = DN;
                break;
            case 3:
                graph.kind = UDG;
                break;
            case 4:
                graph.kind = UDN;
                break;
            default:
                return ERROR;
        }
        CreateALGraph(graph);

        //打印
        cout << "The ALGraph is:\n";
        PrintALGraph(graph);

        //转换为邻接矩阵
        cout << "Now ALG to MG.\n";
        MGraph newGraph{};
        ALGtoMG(graph, newGraph);

        //打印新图
        cout << "Now MGraph is:\n";
        PrintMGraph(newGraph);

        //销毁邻接表
        DestroyALGraph(graph);
    }
    else {
        //创建邻接矩阵为结构的图
        MGraph graph{};
        switch (kind) {
            case 1:
                graph.kind = DG;
                break;
            case 2:
                graph.kind = DN;
                break;
            case 3:
                graph.kind = UDG;
                break;
            case 4:
                graph.kind = UDN;
                break;
            default:
                return ERROR;
        }
        CreateMGraph(graph);
        cout << "MGraph is inited.\n";

        //打印
        cout << "The MGraph is:\n";
        PrintMGraph(graph);

        //转换为邻接表
        cout << "Now MG to ALG.\n";
        ALGraph newGraph{};
        MGtoALG(graph, newGraph);

        //打印新图
        cout << "Now ALGraph is:\n";
        PrintALGraph(newGraph);

        //销毁邻接表
        DestroyALGraph(newGraph);
    }
    return OK;
}
int main() {
    Test();
}

