/*
 * @Description: 
 * @Author: 
 * @Date: 2019-11-16 09:33:34
 * @Version: 
 * @LastEditTime: 2019-11-19 10:26:25
 * @LastEditors: Liu Kai
 */
#include "myhead.h"
int main(int args, char *argv[])
{
    int c = 1;
    int v0 = 0;
    path p;
    dist d;
    Mgraph g;
    char filename[100] = "Text.txt";
    creat(&g, filename, c);
    dijkstra(g, v0, p, d);  
    print_gpd(g, p, d);
    return 0;
}

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
            fscanf(pFile, "%1s", &g->vers[i]);
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
                g->edges[j][i] = w;
        }
        fclose(pFile);
    }
    else
    {
        g->n = 0;
    }
}

void dijkstra(Mgraph g, int v0, path p, dist d)
{
    boolean final[M];
    int i, j, k, v, min, x;
    printf("start: %c\n", g.vers[v0]);
    for (v = 0; v < g.n; v++)
    {
        final[v] = FALSE;
        d[v] = g.edges[v0][v]; // d中保存的是源点到其他结点的距离
        if (d[v] < FINITY && d[v] != 0)
        {
            p[v] = v0; // p[v]用来保存路径
        }
        else
        {
            p[v] = -1;
        }
    }
    final[v0] = TRUE;
    d[v0] = 0; // 初始时s中只有v0一个结点
    // 选出v0到其他顶点的距离最小, 依次加入
    for (i = 1; i < g.n; i++) // i从1开始是因为少了v0, v0已经被选择入s中
    {
        min = FINITY;
        for (k = 0; k < g.n; k++)
        {
            if (!final[k] && d[k] < min) // final表示结点是否被选入s中
            {
                v = k;
                min = d[k];
            }
        }
        // 输出本次入选的顶点距离
        printf("%c---%d\n", g.vers[v], min);
        if (min == FINITY)
        {
            return;
        }
        final[v] = TRUE;
        for (k = 0; k < g.n; k++)
        {
            if (!final[k] && (min + g.edges[v][k] < d[k]))
            {
                d[k] = min + g.edges[v][k];
                p[k] = v; // 寻找当前结点的前驱
            }
        }
    }
    for(int i = 0; i < g.n; i++){
        printf("%d ", p[i]);
    }
    printf("\n");
    for(int i = 0; i < g.n; i++){
        printf("%d ", d[i]);
    }
}

void print_gpd(Mgraph g, path p, dist d){
    int st[M], i, pre, top = -1;
    for(int i = -1; i < g.n; i++){
        printf("\nDistancd: %7d, path: ",d[i]);
        st[++top] = i;
        pre = p[i];
        while(pre != -1){
            st[++top] = pre;
            pre = p[pre];
        }
        while(top > 0){
            printf("%2d", st[top--]);
        }
    }
}