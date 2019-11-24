/*
 * @Description: 
 * @Author: 
 * @Date: 2019-11-16 10:00:47
 * @Version: 
 * @LastEditTime: 2019-11-24 12:47:15
 * @LastEditors: Liu Kai
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <io.h>
#include <stdbool.h>
#include <string.h>
#define FINITY 5000
#define SELATION 4 // help
#define M 20
#define MAXSTRING 200
#define FLAG_FALL_PRICE 5
#define PRICE 1.2
typedef int edgetype;
typedef char vertextype;
// typedef enum
// {
//     FALSE,
//     TRUE
// } boolean;

// ������Ϣ����
typedef struct infor
{
    char nameCity[MAXSTRING];
    int sumPersion;
    struct infor *next;
} info;

typedef int dist[M][M];
// path�������浱ǰ����ǰ��, ���ʱҪ����ջ�����
typedef int path[M][M];

//��ͨ����ͼ
typedef struct
{
    vertextype vers[M][MAXSTRING];
    edgetype edges[M][M];
    int n, e;
} Mgraph;

// ǰ��������
void creatM(Mgraph *g, char *filename, int c);
void dijkstra(Mgraph g, int v0, path p, dist d);
void print(Mgraph g, path p, dist d, int v0, int vEnd);
void floyd(Mgraph g, path p, dist d);
info *init();
info *insert(FILE *pFile, info *head, char *nameCity);
void linkPrint(info *head);
float fareCal(int distance);
void help();

// �˵�������
char selarr[SELATION][MAXSTRING] = {"help", "dijkstra", "floyd", "exit"};
// ���м�����
char cities[M][MAXSTRING];
