/*
 * @Description: 
 * @Author: 
 * @Date: 2019-11-16 10:00:47
 * @Version: 
 * @LastEditTime: 2019-11-16 10:27:15
 * @LastEditors: Liu Kai
 */
#include <stdio.h>
#define FINITY 5000
#define M 20
typedef int edgetype;
typedef char vertextype;
typedef enum{
    FALSE,
    TRUE
}boolean;
typedef int dist[M];
typedef int path[M];
typedef struct{
    vertextype vers[M];
    edgetype edges[M][M];
    int n,e;
}Mgraph;
// Ç°ÏòÉùÃ÷¿é

void creat(Mgraph *g, char *filename, int c);