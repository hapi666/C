#include "stdio.h"
#include "stdlib.h"

typedef struct Node{
	struct Node 	*parent;
	struct Node 	*left;
	struct Node 	*right;
	int 	key;
}Node, *BT;

void InsertNode(BT tree, int d){
	if(tree == NULL){
		tree = (BT)malloc(sizeof(Node));
		tree->key = d;
		tree->left = NULL;
		tree->right = NULL;
		return;
	}
	if(d == tree -> key){
		printf("树中存在相同关键字，插入失败！\n");
		return;
	}
	if(d > tree->key){
		if(tree -> right == NULL){
			tree -> right = (BT)malloc(sizeof(Node));
			tree -> right -> key = d;
			tree -> right -> right = NULL;
			tree -> right -> left = NULL;
			return;
		}
		InsertNode(tree -> right, d);
	}
	if(d < tree->key){
		if(tree -> left == NULL){
			tree -> left -> key = d;
			tree -> left -> left = NULL;
			tree -> left -> right = NULL;
			return;
		}
		InsertNode(tree -> left, d);
	}
}

void CreatTree(BT tree, int data[], int len){
	tree = NULL;
	int i = 0;
	for(i = 0; i < len; i++){
		InsertNode(tree, data[i]);
	}
}

Node* searchNode(BT tree, int d){
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
		}else{ // d != temp -> key
			break;
			return temp;
		}
	}
	return NULL;
}

void TransferNode(BT tree, Node *u, Node *v){
	// 允许 v 是 NULL 的情况
	// 如果是 NULL 说明其父结点和根结点均不存在
	if(u -> parent == NULL){ // 说明结点 u 是数 tree 的根结点
		v ->left = u -> left;
		v -> right = u -> right;
	}else if(u -> parent ->left == u){
		u -> parent ->left = v;
	}else{
		u -> parent -> right = v;
	}
	// 反之，如果不是 NULL ，那么我们需要更新 parent
	if(v != NULL){
		// 更新结点 v 的前身，结点 v 的前身变成结点 u 的前身
		v -> parent = u -> parent;
	}
}

Node* TreeMININUM(BT tree){
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

void deleteNode(BT tree, int d){
	Node *deleted = searchNode(tree, d);
	if(deleted == NULL){
		printf("树中没有这个数据！\n");
		return;
	}
	if(deleted -> left == NULL){
		TransferNode(tree, deleted, deleted -> right);
	}else if(deleted -> right == NULL){
		TransferNode(tree, deleted, deleted -> left);
	}else{
		Node *min = TreeMININUM(deleted -> right);
		if(min -> parent != deleted){ // 如果 min 不是 delete 的右孩子
			TransferNode(tree, min, min -> right);
			// 然后把 delete 的右孩子变成 min 的右孩子
			min -> right = deleted -> right;
			min -> right -> parent = min;
			// min -> parent = deleted -> parent;
		}
		TransferNode(tree, deleted, min);
		min -> left = deleted -> left;
		min -> left -> parent = min;
	}
}

int main(void){
	int data[6] = {0, 2, 3, 4, 5, 6};
	BT tree;
	CreatTree(tree, data, 6);
	Node *n = searchNode(tree, 5);
	printf("成功！%d\n", n -> key);
	InsertNode(tree, 1);
	printf("%d %d\n", tree -> key, tree -> left -> key);
}







