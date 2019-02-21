#include<stdio.h>
#include<stdlib.h>
#define INF	(~(0x1<<31))
/*
	图
*/
struct BNode
{
	int data;
	int weight;
	struct BNode *next;
};

struct FNode
{
	char ch;
	struct BNode *first_node;
};

struct Graph
{
	int vernum;
	int sidnum;
	struct FNode* node[100];
};

int getPosition(char ch, struct Graph *g){
	int i = 0;
	for(i = 0; i < g->vernum; i++){
		if(g->node[i]->ch == ch){
			return i;
		}
	}
	return -1;
}

void insertNode(struct BNode *g, struct BNode *node){
	struct BNode *temp = g;
	while(temp->next){
		temp = temp->next;
	}
	temp->next = node;
	printf("被插入数据：%d\n", temp->next->data);
}

// 创建有向图
struct Graph* creatGraph(){
	int i = 0;
	struct Graph *g = (struct Graph*)malloc(sizeof(struct Graph));
	if(g == NULL){
		printf("内存空间不足。\n");
		return NULL;
	}
	printf("请输入顶点数：\n");
	scanf("%d", &g->vernum);
	printf("请输入边数：\n");
	scanf("%d", &g->sidnum);
	printf("请输入顶点元素：\n");
	for(i = 0; i < g->vernum; i++){
		getchar();
		g->node[i] = (struct FNode*)malloc(sizeof(struct FNode));
		if(g->node[i] == NULL){
			printf("内存空间不足。\n");
			return NULL;
		}
		g->node[i]->first_node = NULL;
		scanf("%c", &g->node[i]->ch);
		// printf("here!!!: %c\n", g->node[i]->ch);
	}
	// for(i = 0; i < g->vernum; i++){
	// 	printf("%c\n", g->node[i]->ch);
	// }
	printf("请输入顶点之间的关系：（即相连顶点，以逗号分隔）\n");
	for(i = 0; i < g->sidnum; i++){
		char ch1, ch2;
		int w = 0;
		getchar();
		scanf("%c, %c, %d", &ch1, &ch2, &w);
		printf("%c, %c, %d\n", ch1, ch2, w);
		struct BNode *node1, *node2;
		node1 = (struct BNode*)malloc(sizeof(struct BNode));
		if(node1 == NULL){
			printf("内存空间不足。\n");
			return NULL;
		}
		node2 = (struct BNode*)malloc(sizeof(struct BNode));
		if(node2 == NULL){
			printf("内存空间不足。\n");
			return NULL;
		}
		node1->data = getPosition(ch1, g);
		node2->data = getPosition(ch2, g);
		node2->weight = w;
		node1->next = NULL;
		node2->next = NULL;
		if(g->node[node1->data]->first_node == NULL){
			g->node[node1->data]->first_node = (struct BNode*)malloc(sizeof(struct BNode));
			if(g->node[node1->data]->first_node == NULL){
				printf("内存空间不足。\n");
				return NULL;
			}
			g->node[node1->data] -> first_node = node2;
			printf("被插入数据：%d\n", g->node[node1->data]->first_node->data);
		}else{
			insertNode(g->node[node1->data]->first_node, node2);
		}
	}
	return g;
}

void printGraph(struct Graph *g){
	int i;
	struct BNode *n;
	for(i = 0; i < g->vernum; i++){
		if(g->node[i]->first_node == NULL)
			printf("%c\n", g->node[i]->ch);
		else
			printf("%c -> ", g->node[i]->ch);
		n = g->node[i]->first_node;
		while(n != NULL){
			if(n -> next != NULL)
				printf("%d -> ", n->data);
			else
				printf("%d\n", n->data);
			n = n->next;
		}
	}
}

// 深度优先搜索
void DFS(struct Graph *g, int i, int *visited){
	visited[i] = 1;
	printf("%c\n", g->node[i]->ch);
	struct BNode *n = g->node[i]->first_node;
	while(n){
		if(!visited[n->data]){
			DFS(g, n->data, visited);
		}
		n = n->next;
	}
	return;
}

void DFSOutprint(struct Graph *g){
	int i, visited[100];
	for(i = 0; i < g->vernum; i++){
		visited[i] = 0;
	}
	printf("深度优先搜索：\n");
	for(i = 0; i < g->vernum; i++){
		if(!visited[i]){
			DFS(g, i, visited);
		}
	}
	printf("\n");
}

// 首先能够获取权值的 一定是一条边上的的两个顶点
int getWeight(struct Graph *g, int start, int end){
	struct BNode *node;
	if (start == end)
        return 0;
    node = g -> node[start] -> first_node;
    while(node != NULL){
    	if(end == node -> data){
    		return node -> weight;
    	}
    	node = node -> next;
    }
    return INF;
}

// 最短路径
/*
	start -- 起始顶点
	 prev -- 前驱顶点数组
	 dist -- 长度数组（dist[i] 是顶点 start 到顶点 i 的最短路径所经历的全部顶点中，位于顶点 i 之前的那个顶点）
*/
void dijkstra(struct Graph *g, int start, int prev[], int dist[]){
	int i, j, k, min, tmp;
	// flag 数组是用来表示顶点 start 到顶点 i 的最短路径是否已经被成功获取
	int flag[100];
	// 初始化
	for(i = 0; i < g->vernum; i++){
		flag[i] = 0;
		prev[i] = 0;
		// 把每个点到顶点 start 的距离都表示出来， 存储在 dist[i] 数组里
		dist[i] = getWeight(g, start, i);
	}
	flag[start] = 1;
	dist[start] = 0;
	for(i = 1; i < g->vernum; i++){
		min = INF;
		for(j = 1; j < g->vernum; j++){
			if(flag[j] == 0 && dist[j] < min){
				min = dist[j];
				k = j;
			}
		}
		flag[k] = 1;
		for(j = 0; j < g->vernum; j++){
			tmp = getWeight(g, k, j);
			tmp = (tmp==INF ? INF : (min + tmp)); // 防止溢出
			if (flag[j] == 0 && (tmp  < dist[j]) ){
                dist[j] = tmp;
                prev[j] = k;
            }
		}
	}
	printf("dijkstra(%c): \n", g->node[start]->ch);
    for (i = 0; i < g->vernum; i++)
        printf("  shortest(%c, %c)=%d\n", g->node[start]->ch, g->node[i]->ch, dist[i]);
}

int main(){
	struct Graph *g;
	int prev[100] = {0};
    int dist[100] = {0};
	g = creatGraph();
	printGraph(g);
	DFSOutprint(g);
	dijkstra(g, 0, prev, dist);
	return 0;
}




