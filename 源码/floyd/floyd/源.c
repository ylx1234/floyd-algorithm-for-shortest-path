
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define INFINITY 65535
#define MAXVEX 100
#define NOTEXIST -1
int visited[MAXVEX];
int path[MAXVEX][MAXVEX];
int dist[MAXVEX][MAXVEX];
typedef char VertexType;
typedef int EdgeType;
typedef struct Graph {
	VertexType vex[MAXVEX];
	EdgeType edge[MAXVEX][MAXVEX];
	int vex_num, edge_num;
}Graph;

void init_graph(Graph *g)
{
	int i, j;
	for (i = 0; i < g->vex_num; i++) {
		for (j = 0; j < g->vex_num; j++) {
			if (i == j) {
				g->edge[i][j] = 0;
			}
			else
				g->edge[i][j] = INFINITY;
		}
	}
}

char read_char()
{
	char ch;
	do {
		ch = getchar();
	} while (!isalpha(ch));
	return ch;
}

int get_pos(Graph g, char ch)
{
	int i;
	for (i = 0; i < g.vex_num; i++) {
		if (g.vex[i] == ch)
			return i;
	}
	return -1;
}

void create_graph(Graph *g)
{
	int i, k;
	printf("�����붥���������:\n");  
	scanf("%d%d", &g->vex_num, &g->edge_num);
	init_graph(g);// ��ʼ��  
	printf("�����붥����Ϣ:\n");  
	for (i = 0; i < g->vex_num; i++) {
		//scanf("%c", g->vex[i]);  
		g->vex[i] = read_char();
	}
	printf("������ߵ���Ϣ:\n");  
	char c1, c2;
	int p1, p2, w;
	for (k = 0; k < g->edge_num; k++) {
		c1 = read_char();
		c2 = read_char();
		scanf("%d", &w);
		p1 = get_pos(*g, c1);
		p2 = get_pos(*g, c2);
		g->edge[p1][p2] = w;//����ߵ�Ȩ��  
	}
}

void print_graph(Graph g)
{
	int i, j;
	for (i = 0; i < g.vex_num; i++) {
		for (j = 0; j < g.vex_num; j++) {
			if (g.edge[i][j] == INFINITY)
				printf("%5c", '*');
			else {
				printf("%5d", g.edge[i][j]);
			}
		}
		printf("\n");
	}
}

void Floyd(Graph g)
{
	int i, j;
	//��ʼ��ͼ
	for (i = 0; i < g.vex_num; i++) {
		for (j = 0; j < g.vex_num; j++) {
			dist[i][j] = g.edge[i][j];
			if (g.edge[i][j] == 0 || g.edge[i][j] == INFINITY)
				path[i][j] = NOTEXIST;
			else
				path[i][j] = j;
		}
	}
	int k;
	//Ѱ�����·��
	for (k = 0; k < g.vex_num; k++) {
		for (i = 0; i < g.vex_num; i++) {
			for (j = 0; j < g.vex_num; j++) {
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = k;
				}
			}
		}
	}
}
int dfs(Graph g, int i)
{
	int  j;
	visited[i] = 1;
	for (j = 0; j < g.vex_num; j++) {
		if (!visited[j] && i != j && g.edge[i][j] != INFINITY) {
			dfs(g, j);
		}
	}
}
int is_connected(Graph g, int u, int v)//���� ������������ж�ͼ��u, v�����Ƿ���ͨ
{
	int i, flag;
	for (i = 0; i < g.vex_num; i++) {
		visited[i] = 0;
	}
	dfs(g, u);
	if (visited[v] == 1)
		return 1;
	else
		return 0;
}

void print_path(Graph g, int u, int v)
{
	printf("%c", g.vex[u]);
	if (u != v) {
		printf("->");
		print_path(g, path[u][v], v);
	}
}
void traversal(Graph g)//��ӡ��·��
{
	int i, j;
	for (i = 0; i < g.vex_num; i++) {
		for (j = 0; j < g.vex_num; j++) {
			if (is_connected(g, i, j)) {// ����·��ʱ 
				printf("%c to %c :���·��Ϊ", g.vex[i], g.vex[j]);
				print_path(g, i, j);
				printf(" Ȩ�غ�Ϊ : %d", dist[i][j]);
				printf("\n");
			}
		}
	}
}

int main()
{
	Graph g;
	create_graph(&g);
	int i, j;
	Floyd(g);
	printf("\n");
	traversal(g);
	//print_graph(g);

	return 0;
}

