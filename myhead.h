/*
 * @Description: 
 * @Author: 
 * @Date: 2019-11-16 10:00:47
 * @Version: 
 * @LastEditTime: 2019-11-22 22:28:34
 * @LastEditors: Liu Kai
 */
#include <stdio.h>
#define FINITY 5000
#define M 20
#define MAXSTRING 200
typedef int edgetype;
typedef char vertextype;
typedef enum{
    FALSE,
    TRUE
}boolean;
typedef int dist[M][M];
typedef int path[M][M];
typedef struct{
    vertextype vers[MAXSTRING];
    edgetype edges[M][M];
    int n,e;
}Mgraph;
// 前向声明块

void creat(Mgraph *g, char *filename, int c);
void dijkstra(Mgraph g, int v0, path p, dist d);
// 源点到其他结点的最短路径,最小运费
void print(Mgraph g, path p, dist d);
// 任意一对结点的最短路径,最小费用
void floyd(Mgraph g,path p, dist d);
