#pragma once
#include<iostream>
#include<string>
#include<process.h>
#include<stdlib.h>
using namespace std;
#define INF 5555
#define MAX 15

//创建弧结构
typedef struct ArcNode
{
    int adject;    //指向顶点位置
    ArcNode *near; //指向下一条弧的指针
    int length;    //相邻两地相隔距离
}ArcNode;

//单个城市信息结构
typedef struct VNode
{
    string name;  //城市名称
    int num;      //城市代号
    string syn;   //简介synopsis
    ArcNode *firstarc; //指向第一条弧
}VNode, AdjList[MAX];

//图结构
typedef struct
{
    AdjList City;
    int vexnum, arcnum;  //该图当前顶点数和弧数
}G_City;


//定义队列基本单元
typedef struct QNode {
    int *base;
    int front;
    int rear;
}QNode;

//————————————————————————————————————————————————————————————————————————————
void InitQueue(QNode &Q);//创建一个对列
int Push_Q(QNode &Q, int e);//元素e进队,采用先挖坑在栽萝卜的做法
int Pop_Q(QNode &Q, int &e);//队列元素出队,e记录出队元素
int Empty_Q(QNode Q);//判空队列
//————————————————————————————————————————————————————————————————————————————
void Init_A(AdjList v1, VNode &v2, string na, int n);//编辑弧边的函数
void Print(G_City g); //打印城市线路信息
void Init_G(G_City &g);//新建湖南城市图结构
void Find_C(G_City &g);//查询城市信息
void Rev(G_City &g);//修改现有信息
int Find_T(G_City g, string na1, string na2, int &a, int &b);//查找两个城市是否相邻
void Add_Arc(G_City &g,string na1,string na2); //增加线路
void Del_Arc(G_City &g, string na1, string na2);//删除线路
void Add_C(G_City &g);//增加城市
void Del_C(G_City &g); //删除城市
void Find_S1(G_City g);  //查找指定城市的最短路径
void Find_S2(G_City g);  //查找指定城市到任意城市的最短路径
//——————————————————————————————————————————————————————————————————————————————————————
void Handle();//操作界面
void User();//用户操作界面
void Adm();//操作者界面