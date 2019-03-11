#include "stdio.h"
#include "stdlib.h"

typedef struct Node{
	struct Node* 	parent;
	struct Node* 	left;
	struct Node*	right;
	int 			key;
}Node;

void InsertNode(Node **tree, int d){
	Node *temp = (Node*)malloc(sizeof(Node));
	if(temp == NULL){
		printf("内存不足\n");
	}
	temp -> key = d;
	temp -> left = NULL;
	temp -> right = NULL;
	if((*tree) == NULL){
		*tree = (Node*)malloc(sizeof(Node));
		*tree = temp;
		// printf("%d\n", (*tree) -> key);
		return;
	}
	if(d == (*tree) -> key){
		printf("树中存在相同关键字，插入失败！\n");
		// printf("%d\n", d);
		return;
	}
	if(d > (*tree) -> key){
		InsertNode(&((*tree) -> right), d);
	}
	if(d < (*tree) -> key){
		InsertNode(&((*tree) -> left), d);
	}
}

void CreatTree(Node **tree, int data[], int len){
	int i = 0;
	for(i = 0; i < len; i++){
		InsertNode(tree, data[i]);
	}
}

void MiddleOrderTree(Node *tree){
	if(tree == NULL){
		return;
	}
	MiddleOrderTree(tree -> left);
	printf("%d\n", tree -> key);
	MiddleOrderTree(tree -> right);
}

Node* searchNode(Node *tree, int d){
	if(tree == NULL){
		printf("空树！\n");
		return NULL;
	}
	if(d == tree -> key){
		return tree;
	}
	Node *temp = NULL;
	temp = tree;
	while(temp != NULL){
		if(d > temp ->key){
			temp = temp -> right;
		}else if(d < temp -> key){
			temp = temp -> left;
		}else{ // d == temp -> key
			// printf("%d\n", temp -> key);
			break;
		}
	}
	if(temp == NULL){
		return NULL;
	}
	return temp;
}

void TransferNode(Node **tree, Node **u, Node **v){
	// 允许 v 是 NULL 的情况
	// 如果是 NULL 说明其父结点和根结点均不存在
	if((*u) -> parent == NULL){ // 说明结点 u 是数 tree 的根结点
		(*v) ->left = (*u) -> left;
		(*v) -> right = (*u) -> right;
	}else if((*u) -> parent -> left == *u){
		(*u) -> parent ->left = *v;
	}else{
		(*u) -> parent -> right = *v;
	}
	// 反之，如果不是 NULL ，那么我们需要更新 parent
	if(*v != NULL){
		// 更新结点 v 的前身，结点 v 的前身变成结点 u 的前身
		(*v) -> parent = (*u) -> parent;
	}
}

Node* TreeMININUM(Node *tree){
	if(tree == NULL){
		printf("这是一棵空树，无法找到该棵树上最小结点！\n");
		return NULL;
	}
	Node *temp = tree -> left;
	while(temp != NULL){
		temp = temp -> left;
	}
	return temp;
}

void deleteNode(Node **tree, int d){
	Node *deleted = searchNode(*tree, d);
	if(deleted == NULL){
		printf("树中没有这个数据！\n");
		return;
	}
	if(deleted -> left == NULL){
		TransferNode(tree, &deleted, &(deleted -> right));
	}else if(deleted -> right == NULL){
		TransferNode(tree, &deleted, &(deleted -> left));
	}else{
		Node *min = TreeMININUM(deleted -> right);
		if(min -> parent != deleted){ // 如果 min 不是 delete 的右孩子
			TransferNode(tree, &min, &(min -> right));
			// 然后把 delete 的右孩子变成 min 的右孩子
			min -> right = deleted -> right;
			min -> right -> parent = min;
		}
		TransferNode(tree, &deleted, &min);
		min -> left = deleted -> left;
		min -> left -> parent = min;
	}
}

int main(void){
	int data[6] = {0, 2, 3, 4, 5, 6}, i = 0;
	Node *tree = NULL;
	CreatTree(&tree, data, 6);
	MiddleOrderTree(tree);
	Node *n = (Node*)malloc(sizeof(Node));
	if(n == NULL){
		printf("内存不足\n");
	}
	n = searchNode(tree, 5);
	if(n == NULL){
		printf("NULL!\n");
	}
	printf("成功找到！%d\n", n -> key);
	InsertNode(&tree, 1);
	MiddleOrderTree(tree);
	// printf("%d %d\n", tree -> key, tree -> right -> left -> key);
}







