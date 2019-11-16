/*
 * @Description: 
 * @Author: 
 * @Date: 2019-11-16 09:33:34
 * @Version: 
 * @LastEditTime: 2019-11-16 11:53:12
 * @LastEditors: Liu Kai
 */
#include "myhead.h"
int main(int args, char *argv[])
{
    int c = 0;
    Mgraph g;
    char filename[100] = "Text.txt";
    creat(&g, filename, c);
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
        for (i < 0; i < g->n; i++)
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
    for (v = 0; v < g.n; v++)
    {
        final[v] = FALSE;
        d[v] = g.edges[v0][v];
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
    for (i = 1; i < g.n; i++)
    {
        min = FINITY;
        for (k = 0; k < g.n; k++)
        {
            if (!final[k] && d[k] < min) // final表示结点是否被选入s中
            {
                v = k;
                min = d[k];
            }
            printf("%c---%d\n", g.vers[v], min);
            if (min == FINITY)
            {
                return;
            }
            final[v] = TRUE;
        }
    }
    for (k = 0; k < g.n; k++)
    {
        if (!final[k] && (min + g.edges[v][k] < d[k]))
        {
            d[k] = min + g.edges[v][k];
            p[k] = v;
        }
    }
}