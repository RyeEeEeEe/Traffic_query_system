/*
 * @Description: 
 * @Author: 
 * @Date: 2019-11-16 09:33:34
 * @Version: 
 * @LastEditTime: 2019-11-23 18:32:24
 * @LastEditors: Liu Kai
 */
#include "myhead.h"
info *myinfo;
int main(int args, char *argv[])
{
    int c = 1;
    // 源点
    int v0 = 0;
    path p;
    path mypathDijk;
    dist d;
    Mgraph g;
    char filename[100] = "Text.txt";
    myinfo = init();
    creat(&g, filename, c);
    // dijkstra(g, v0, p, d);
    // print(g, p, d, v0);
    floyd(g, p, d);
    printf("\n");
    print(g, p, d, 1);
    printf("\n");
    print(g, p, d, v0);
    linkPrint(myinfo);
    return 0;
}

/**
 * @description: 交通网络图的创建
 * @param {type} 
 * @return: 
 */
void creat(Mgraph *g, char *filename, int c)
{
    int i, j, k, w;
    FILE *pFile;
    pFile = fopen(filename, "r");
    if (pFile)
    {
        fscanf(pFile, "%d%d", &g->n, &g->e);
        for (i = 0; i < g->n; i++)
        {
            fscanf(pFile, "%s", g->vers[i]);
            myinfo = insert(pFile, myinfo, g->vers[i]);
        }
        for (i = 0; i < g->n; i++)
        {
            for (j = 0; j < g->n; j++)
            {
                if (i == j)
                {
                    g->edges[i][j] = 0;
                }
                else
                {
                    g->edges[i][j] = FINITY;
                }
            }
        }
        for (k = 0; k < g->e; k++)
        {
            fscanf(pFile, "%d%d%d", &i, &j, &w);
            g->edges[i][j] = w;
            if (c == 0)
            {
                g->edges[j][i] = w;
            }
        }
        fclose(pFile);
    }
    else
    {
        g->n = 0;
    }
}

/**
 * @description: dijk
 * @param {type} 
 * @return: 
 */
void dijkstra(Mgraph g, int v0, path p, dist d)
{
    boolean final[M];
    int i, j, k, v, min, x;
    printf("start: %s\n", g.vers[v0]);
    for (v = 0; v < g.n; v++)
    {
        final[v] = FALSE;
        d[0][v] = g.edges[v0][v]; // d中保存的是源点到其他结点的距离
        if (d[0][v] < FINITY && d[0][v] != 0)
        {
            p[0][v] = v0; // p[v]用来保存路径
        }
        else
        {
            p[0][v] = -1;
        }
    }
    final[v0] = TRUE;
    d[0][v0] = 0; // 初始时s中只有v0一个结点
    // 选出v0到其他顶点的距离最小, 依次加入
    for (i = 1; i < g.n; i++) // i从1开始是因为少了v0, v0已经被选择入s中
    {
        min = FINITY;
        for (k = 0; k < g.n; k++)
        {
            if (!final[k] && d[0][k] < min) // final表示结点是否被选入s中
            {
                v = k;
                min = d[0][k];
            }
        }
        // 输出本次入选的顶点距离
        printf("%s---%d\n", g.vers[v], min);
        if (min == FINITY)
        {
            return;
        }
        final[v] = TRUE;
        for (k = 0; k < g.n; k++)
        {
            if (!final[k] && (min + g.edges[v][k] < d[0][k]))
            {
                d[0][k] = min + g.edges[v][k];
                p[0][k] = v; // 寻找当前结点的前驱
            }
        }
    }
    for (int i = 0; i < g.n; i++)
    {
        printf("%d ", p[0][i]);
    }
    printf("\n");
    for (int i = 0; i < g.n; i++)
    {
        printf("%d ", d[0][i]);
    }
    printf("\n");
}

/**
 * @description: 源点到其他结点的最短路径,最小运费, v0表示当前源点
 * @param {type} 
 * @return: 
 */
void print(Mgraph g, path p, dist d, int v0)
{
    int st[M], i, pre, top = -1;
    for (int i = 0; i < g.n; i++)
    {
        printf("\nDistancd: %d, path: ", d[v0][i]);
        st[++top] = i;
        pre = p[v0][i];
        while (pre != -1)
        {
            st[++top] = pre;
            pre = p[v0][pre];
        }
        while (top > 0)
        {
            printf("%s ", g.vers[st[top--]]);
        }
    }
    printf("\n");
}

/**
 * @description: 任意一对结点的最短路径,最小费用
 * @param {type} 
 * @return: 
 */
void floyd(Mgraph g, path p, dist d)
{
    int i, j, k;
    for (i = 0; i < g.n; i++)
    {
        for (j = 0; j < g.n; j++)
        {
            d[i][j] = g.edges[i][j];
            if (i != j && d[i][j] < FINITY)
            {
                p[i][j] = i;
            }
            else
            {
                p[i][j] = -1;
            }
        }
    }
    for (k = 0; k < g.n; k++)
    {
        for (i = 0; i < g.n; i++)
        {
            for (int j = 0; j < g.n; j++)
            {
                if (d[i][j] > (d[i][k] + d[k][j]))
                {
                    d[i][j] = d[i][k] + d[k][j];
                    p[i][j] = k;
                }
            }
        }
    }
}

/**
 * @description: 带头结点链表初始化
 * @param {type} void
 * @return: head
 */
info *init()
{
    info *head;
    head = (info *)malloc(sizeof(info));
    head->next = NULL;
    return head;
}

/**
 * @description: 链表尾插
 * @param {type: node_stu*} head
 * @return:head
 */
info *insert(FILE *pFile, info *head, char *nameCity)
{
    info *p, *pre;
    pre = head;
    p = head->next;
    while (p)
    {
        pre = p;
        p = p->next;
    }
    p = (info *)malloc(sizeof(info));
    strcpy(p->nameCity, nameCity);
    fscanf(pFile, "%d", &p->sumPersion);
    p->next = pre->next;
    pre->next = p;
    return head;
}

void linkPrint(info *head)
{
    info *p, *pre;
    p = head->next;
    if (!p)
    {
        printf("no City Infomation\n");
        return;
    }
    while (p)
    {
        printf("nameCity:%s sumPersion:%d\n", p->nameCity, p->sumPersion);
        p = p->next;
    }
    return;
}