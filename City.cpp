#include"G_City.h"
//#include<windows.h>
#include <stdlib.h>

int P[MAX], D[MAX];//P存储最短路径信息，D存储最短的距离


//创建一个队列
void InitQueue(QNode &Q) {

    Q.base = (int*)malloc(MAX * sizeof(int));//开辟空间
    if (!Q.base)exit(-1);
    Q.front = Q.rear = 0;
}


//元素e进队,采用先挖坑再栽萝卜的做法
int Push_Q(QNode &Q, int e) {
    if (Q.rear == MAX - 1) //判满
    {
        return 0;
    }
    Q.base[Q.rear] = e;//入队
    Q.rear++;
    return 1;
}


//队列元素出队,e记录出队元素
int Pop_Q(QNode &Q, int &e)
{
    if (Q.front == Q.rear)//判空
    {
        return 0;
    }
    e = Q.base[Q.front];
    Q.front++;
    return 1;
}


//判空队列
int Empty_Q(QNode Q)
{
    if (Q.front == Q.rear)
        return 1;
    else
        return 0;
}


//编辑弧边的函数
void Init_A(AdjList v1, VNode &v2, string na, int n)
{
    //头插法
    int i = 0;
    ArcNode *a;
    a = (ArcNode*)malloc(sizeof(ArcNode));//给边开辟内存空间
    while (na != v1[i].name)i++;//遍历找到对应的顶点
    a->adject = i;
    a->length = n;
    a->near = v2.firstarc;
    v2.firstarc = a;
}


//修改对应弧的信息
void Re_A(G_City g, VNode &v, string na, int n)
{
    int i = 0, j = 0;
    ArcNode *p;
    p = v.firstarc;
    while (g.City[p->adject].name != na)
    {
        p = p->near;
    }
    p->length = n;
}


//新建湖南城市图结构
void Init_G(G_City &g)
{
    int n, count = 0, i = 0, j = 0, V, W;
    cout << "**********欢迎使用余越开发的网络交通查询系统！V1.0**********" << endl << endl;
    cout << "请输入需要构建的城市个数和边的总数：";
    cin >> V >> W;
    cout << "请依次输入城市名、代号及城市信息：" << endl;
    string na, s;
    //构建结点信息
    while (i < V)
    {
        cin >> na;
        cin >> n >> s;
        g.City[i].name = na;
        g.City[i].num = n;
        g.City[i].syn = s;
        i++;
    }
    g.arcnum = i;//结点数目
    //所有结点的弧置空
    for (j = 0; j<MAX; j++)
        g.City[j].firstarc = NULL;
    j = 0; i = 0;
    cout << "输入所有相邻的城市及之间的距离：" << endl;

    while (count<W)
    {
        cin >> na;
        cin >> s;
        cin >> n;

        while (j < g.arcnum&&g.City[j].name != na) j++;//

        Init_A(g.City, g.City[j], s, n);//

        while (i < g.arcnum&&g.City[i].name != s) i++;//

        Init_A(g.City, g.City[i], na, n);//

        count++;
        i = 0;
        j = 0;
    }
    g.arcnum = count;
}


//查询城市信息
void Find_C(G_City &g)
{
    cout << "**********欢迎使用余越开发的网络交通查询系统！V1.0**********" << endl << endl;
    string na;
    int i = 0;
    cout << "请输入需要查找的城市的名称：" << endl;
    cin >> na;
    //在结点顺序表中查找
    while (i < g.arcnum&&g.City[i].name != na)
    {
        i++;
    }

    if (g.City[i].name != na)
    {
        cout << "该城市并不存在于该网络图中！" << endl;
    }else
    {
        cout << "城市名：" << g.City[i].name << '\t';
        cout << "序号：" << g.City[i].num << endl;
        cout << "城市信息：" << g.City[i].syn << endl;
        cout << "与"<<g.City[i].name<<"相邻的城市有：" << endl;
        ArcNode *a = g.City[i].firstarc;
        while (a != NULL)
        {
            cout << g.City[a->adject].name << "相距" << a->length << endl;
            a = a->near;
        }
    }
}


//修改现有信息
void Rev(G_City &g)
{
    cout << "**********欢迎使用余越开发的交通查询系统！V1.0**********" <<endl << endl;

    int n, i = 0;
    string na, s;
    ArcNode *p;
    cout << "请输入需要修改的城市名称：" << endl;
    cin >> na;
    while (i < g.arcnum&&g.City[i].name != na) i++;
    if (g.City[i].name != na)
    {
        cout << "所输入城市并不存在！" << endl;
        return;
    }else
    {
        cout << "请重新输入该城市相应信息:" << endl;
        cin >> na >> n >> s;
        g.City[i].name = na;
        g.City[i].num = n;
        g.City[i].syn = s;
        cout << "请确认是否修改？（y/n）";
        char ch;
        cin >> ch;
        if (ch == 'Y' || ch == 'y')
        {
            p = g.City[i].firstarc;
            //
            while (p)
            {
                cout << g.City[i].name << " 到" << g.City[p->adject].name << " 距离为： " << p->length << endl;
                cout << "现修改为：";
                cin >> p->length;
                Re_A(g, g.City[p->adject], g.City[i].name, p->length);
                p = p->near;
            }
        }
    }
    cout << "修改成功！" << endl;
}


//查找两个城市是否相邻
int Find_T(G_City g, string na1, string na2, int &a, int &b)
{
    int i = 0, j = 0;
    ArcNode *p;
    //定位第一个城市
    while (i < g.arcnum&&g.City[i].name != na1)
    {
        i++;
    }
    if (g.City[i].name != na1)
    {
        return 0;
    }
    //定位第二个城市
    while (j < g.arcnum&&g.City[j].name != na2)
    {
        j++;
    }
    if (g.City[j].name != na2)
    {
        return 0;
    }

    a = i; b = j;
    p = g.City[i].firstarc;
    //第一个城市有后继，则指向下一个城市
    while (p&&p->adject != j)
    {
        p = p->near;
    }
    if (!p)//城市2不在城市1的邻接表里
    {
        return 1;
    }
    else
        return 0;
}


//增加线路
void Add_Arc(G_City &g, string na1, string na2)
{
    int s;
    ArcNode *p;//
    int i = 0, j = 0;
    //
    if (!Find_T(g, na1, na2, i, j))//两个城市相连不能增加平行边
    {
        cout << "不能添加路线！" << endl;
        getchar();
        return;
    }
    cout << "请输入要增加的连通路径距离：";
    cin >> s;
    p = (ArcNode*)malloc(sizeof(ArcNode));
    p->length = s;
    //插入结点操作
    //新节点后继为j
    p->adject = j;
    p->near = g.City[i].firstarc;
    g.City[i].firstarc = p;
    //两处修改
    p = (ArcNode*)malloc(sizeof(ArcNode));
    p->length = s;
    p->adject = i;

    p->near = g.City[j].firstarc;
    g.City[j].firstarc = p;
}


//删除线路
void Del_Arc(G_City &g, string na1, string na2)
{
    ArcNode *p, *q;
    int i = 0, j = 0;
    while (i < g.arcnum&&g.City[i].name != na1)i++;
    while (j < g.arcnum&&g.City[j].name != na2)j++;
    //删除城市越界了
    if (i == g.arcnum || j == g.arcnum)
    {
        cout << "找不到该线路！" << endl;
        getchar();
        return;
    }

    p = g.City[i].firstarc;
    if (p == NULL)
    {
        cout << "不能进行相应操作！" << endl;
        getchar();
        return;
    }

    if (g.City[i].firstarc->adject == j)
    {
        g.City[i].firstarc = p->near;//拆链
        free(p);
    }else{
        q = p;
        while (p&&p->adject != j)
        {
            q = p;
            p = p->near;
        }
        if (p == NULL)
        {
            cout << "不能进行相应操作！" << endl;
            getchar();
            return;
        }
        q->near = p->near;
        free(p);
    }
    //对称删除
    p = g.City[j].firstarc;
    if (p == NULL)
    {
        cout << "不能进行相应操作！" << endl;
        getchar();
        return;
    }
    if (g.City[j].firstarc->adject == i)
    {
        g.City[j].firstarc = p->near;
        free(p);
    }
    else
    {
        q = p;
        while (p&&p->adject != i)
        {
            q = p;
            p = p->near;
        }
        if (p == NULL)
        {
            cout << "不能进行相应操作！" << endl;
            getchar();
            return;
        }
        q->near = p->near;
        free(p);
    }
    g.arcnum--;
    cout << endl << "删除完成！" <<endl;
}


//增加城市
void Add_C(G_City &g)
{
    if (g.arcnum == 15)//城市结点顺序表已满
    {
        cout << "该网络图已经不能添加城市了！" << endl;
        system("pause");
        return;
    }
    VNode c;
    int n;
    int i = 0, j = 0;
    string na, s;
    cout << "请输入需要增加的城市的名称：";
    cin >> na;
    while (i < g.arcnum)
    {
        if (na == g.City[i].name)
        {
            cout << "该城市已经在网络图中存在！" << endl;
            return;
        }
        i++;
    }

    cout << "请输入新增城市的代号及简介：" << endl;
    cin >> n >> s;
    c.name = na;
    c.num = n;
    c.syn = s;
    c.firstarc = NULL;
    //新城市在顺序表中的位置在已有结点之后
    g.City[g.arcnum++] = c;
    cout << "输入相邻的城市,相邻距离(用@号表示结束)：" << endl;
    while (1)
    {
        j = 0;
        cin >> na;
        if (na == "@")
            break;
        cin >> n;

        Init_A(g.City, g.City[i], na, n);

        while (j < g.arcnum&&g.City[j].name != na)j++;

        Init_A(g.City, g.City[j], c.name, n);

        g.vexnum++;
    }
}


//删除城市
void Del_C(G_City &g)
{
    cout << "请输入需要删除的城市的名称：" << endl;
    string na;
    cin >> na;
    int i = 0, j = 0;
    while (i < g.arcnum && na != g.City[i].name)i++;  //顶点顺序表中遍历查找对应城市
    if (i == g.arcnum)
    {
        cout << "该城市在图中不存在！" << endl;
        system("pause");
        return;
    }
    ArcNode *p, *q, *r;
    p = g.City[i].firstarc;//暂存被删结点
    while (p)
    {
        q = g.City[p->adject].firstarc;
        if (g.City[p->adject].firstarc->adject == i)
        {
            g.City[p->adject].firstarc = q->near;
            free(q);
        }else {
            r = q;
            while (q && q->adject != i) //查找包含要删除城市信息的弧边信息
            {
                r = q;
                q = q->near;
            }
            r->near = q->near;
            free(q);
        }
        p = p->near;
    }
    g.arcnum--;
    free(g.City[i].firstarc);
    j = i;
    //将后面的城市向上移动
    while (i < g.arcnum + 1)
    {
        g.City[i].name = g.City[i + 1].name;
        g.City[i].num = g.City[i + 1].num;
        g.City[i].syn = g.City[i + 1].syn;
        g.City[i].firstarc = g.City[i + 1].firstarc;
        i++;
    }
    //
    for (int k = 0; k < g.arcnum; k++)//修改相应的弧边记录的下标值
    {
        p = g.City[k].firstarc;
        while (p)
        {
            if (p->adject > j){
                p->adject--;
            }
            p = p->near;
        }
    }
    cout << endl << "删除完成！" <<endl;
}


//打印城市线路信息
void Print(G_City g)
{
    int i;
    ArcNode *p;
    for (i = 0; i < g.arcnum; i++)
    {
        p = g.City[i].firstarc;
        if (!p)
        {
            cout << g.City[i].name << endl;
            continue;
        }
        while (p != NULL)
        {
            //cout << g.City[i].name << "  - " << p->length << " ->  " << g.City[p->adject].name << '\t';
            cout << g.City[i].name << " 到 " << g.City[p->adject].name << " 距离为：" << p->length << '\t'<<'\t';
            p = p->near;
        }
        cout << endl << endl ;
    }
}


//最短线路
void Find_A(G_City g, string na, int P[MAX], int D[MAX])//P[]记录当前城市的前一个城市的线路，D[]记录指定城市到该城市的最短路径
{
    int final[MAX];//标识是否已经遍历数组，0表示未遍历，1表示已遍历
    QNode Q;
    int v, min, i = 0, j = 0;
    ArcNode *p;

    for (v = 0; v < g.arcnum; v++)
    {
        D[v] = INF;
        final[v] = 0;
        P[v] = 0;
    }

    while (i < g.arcnum&&g.City[i].name != na) i++; //查找目标城市

    v = i;
    D[i] = 0; final[i] = 1; P[i] = INF;//初始城市先赋值
    InitQueue(Q);
    Push_Q(Q, i);//下标入队列
    while (!Empty_Q(Q))
    {
        v = 0;
        Pop_Q(Q, i);
        p = g.City[i].firstarc;
        min = D[i];
        while (p)
        {
            if (!final[p->adject]) //判断是否遍历过该顶点
            {
                Push_Q(Q, p->adject);
                final[p->adject] = 1;
            }
            if ((D[i] + p->length) < D[p->adject])//判断是否需要修改最短距离和路径
            {
                D[p->adject] = D[i] + p->length;
                P[p->adject] = i;
            }
            p = p->near;
        }
    }
    i = v;
    for (int k = 0; k < g.arcnum; k++)//最后修正上述操作可能出错的路径信息
    {
        if (D[k] == INF)
            continue;
        if (P[k] != INF)
        {
            p = g.City[k].firstarc;
            min = D[P[k]];
            while (p&&p->adject != P[k]) p = p->near;
            if (D[k] >(min + p->length))
                D[k] = min + p->length;
        }
    }
}


//查找指定城市的最短路径
void Find_S1(G_City g)
{
    QNode Q;
    InitQueue(Q);
    string na1, na2;
    int j = 0, i = 0, v;
    cout << "请输入需要查询线路的两个城市的名称:" << endl;
    cin >> na1 >> na2;
    while (i < g.arcnum&&g.City[i].name != na1)
    {
        i++;
    }
    if (g.City[i].name != na1)
    {
        cout << "没有找到相应城市" << endl;
        getchar();
        return;
    }

    Find_A(g, na1, P, D);

    while (j < g.arcnum&&g.City[j].name != na2) j++;

    if (D[j] == INF)
    {
        cout << na1 << "与" << na2 << "之间无路可走" << endl;
        getchar();
        return;
    }
    cout << na1 << "与" << na2 << "最短距离为" << D[j] << endl;
    cout << "具体路线为：" << endl;
    v = P[j];
    while (v != INF)//找到初始城市
    {
        Push_Q(Q, v);
        v = P[v];//记录前一个城市
    }
    while (!Empty_Q(Q))
    {
        v = Q.base[--Q.rear];//队列队尾出列，类似栈操作
        cout << g.City[v].name << "<--->";
    }
    cout << na2 << endl;
}


//查找指定城市到任意城市的最短路径
void Find_S2(G_City g)
{
    QNode Q;
    InitQueue(Q);
    int v, i = 0;
    string na;
    cout << "请输入需要定点的城市名称：";
    cin >> na;
    while (i < g.arcnum&&g.City[i].name != na)
    {
        i++;
    }
    if (g.City[i].name != na)
    {
        cout << "没有找到相应城市" << endl;
        getchar();
        return;
    }

    Find_A(g, na, P, D);

    for (int i = 0; i < g.arcnum; i++)
    {
        if (D[i] == INF)
        {
            cout << na << "与" << g.City[i].name << "之间无通路" << endl << endl;
        }else {
            cout << na << "到" << g.City[i].name << "最短距离为" << D[i] << endl;
            cout << "具体路线为：" << endl;
            v = P[i];
            while (v != INF)
            {
                Push_Q(Q, v);
                v = P[v];
            }
            while (!Empty_Q(Q))
            {
                v = Q.base[--Q.rear];
                cout << g.City[v].name << "<--->";
            }
            cout << g.City[i].name << endl << endl;
        }
    }
}