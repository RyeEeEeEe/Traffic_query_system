/*
 * @Description: 
 * @Author: 
 * @Date: 2019-11-16 09:33:34
 * @Version: 
 * @LastEditTime: 2019-11-22 22:45:41
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
    print(g, p, d);
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
        d[0][v] = g.edges[v0][v]; // d�б������Դ�㵽�������ľ���
        if (d[0][v] < FINITY && d[v] != 0)
        {
            p[0][v] = v0; // p[v]��������·��
        }
        else
        {
            p[0][v] = -1;
        }
    }
    final[v0] = TRUE;
    d[0][v0] = 0; // ��ʼʱs��ֻ��v0һ�����
    // ѡ��v0����������ľ�����С, ���μ���
    for (i = 1; i < g.n; i++) // i��1��ʼ����Ϊ����v0, v0�Ѿ���ѡ����s��
    {
        min = FINITY;
        for (k = 0; k < g.n; k++)
        {
            if (!final[k] && d[0][k] < min) // final��ʾ����Ƿ�ѡ��s��
            {
                v = k;
                min = d[0][k];
            }
        }
        // ���������ѡ�Ķ������
        printf("%c---%d\n", g.vers[v], min);
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
                p[0][k] = v; // Ѱ�ҵ�ǰ����ǰ��
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
}

void print(Mgraph g, path p, dist d)
{
    int st[M], i, pre, top = -1;
    for (int i = 0; i < g.n; i++)
    {
        printf("\nDistancd: %7d, path: ", d[0][i]);
        st[++top] = i;
        pre = p[0][i];
        while (pre != -1)
        {
            st[++top] = pre;
            pre = p[0][pre];
        }
        while (top > 0)
        {
            printf("%2d", st[top--]);
        }
    }
}

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