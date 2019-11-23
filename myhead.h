/*
 * @Description: 
 * @Author: 
 * @Date: 2019-11-16 10:00:47
 * @Version: 
 * @LastEditTime: 2019-11-23 18:22:05
 * @LastEditors: Liu Kai
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FINITY 5000
#define M 20
#define MAXSTRING 200
typedef int edgetype;
typedef char vertextype;
typedef enum
{
    FALSE,
    TRUE
} boolean;

// 城市信息链表
typedef struct infor
{
    char nameCity[MAXSTRING];
    int sumPersion;
    struct infor *next;
} info;

typedef int dist[M][M];
typedef int path[M][M];

//交通网络图
typedef struct
{
    vertextype vers[M][MAXSTRING];
    edgetype edges[M][M];
    int n, e;
} Mgraph;

// 前向声明块
void creat(Mgraph *g, char *filename, int c);
void dijkstra(Mgraph g, int v0, path p, dist d);
void print(Mgraph g, path p, dist d, int v0);
void floyd(Mgraph g, path p, dist d);
info *init();
info *insert(FILE *pFile, info *head, char *nameCity);
void linkPrint(info *head);