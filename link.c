#include<stdio.h>
#include<stdlib.h>
typedef struct Link {
	int data;
	struct Link* next;	
}link;

link* initLink(int len){
	link *p = (link*)malloc(sizeof(link));
	link *temp = p;
	int i;
	temp -> data = 1;
	for(i = 2; i <= len; i++){
		link* a = (link*)malloc(sizeof(link));
		a -> data = i;
		a -> next = NULL;
		temp -> next = a;
		temp  = temp -> next;
	}
	return p;
}

link* findLinkNode(link* p, int data){
	while(p != NULL) {
		if(data == p -> data){	
			return p;
		}
		p = p -> next;
	}
	return NULL;
}

link* findlastLinkNode(link* p, int data){
	while(p -> next != NULL){
		if(p -> next ->data == data){
			return p;
		}
		p = p -> next;
	}
	return NULL;
}

link* insertLinkNode(link* p, int data, int positionData){
	link* insertPositionNode = findLinkNode(p, positionData);
	printf("插入位置节点数据域: %d\n", insertPositionNode -> data);
	link* insertNode = (link*)malloc(sizeof(link));
	link* temp = p;
	if(temp == NULL){
		printf("链表为空，无法插入新节点\n");
		return NULL;
	}else if(insertPositionNode == NULL && temp != NULL){
		insertNode -> data = data;
		insertNode -> next = NULL;
		temp -> next = insertNode;
		printf("没有找到插入位置节点\n");
		return NULL;
	}
	insertNode -> data = data;
	insertNode -> next = insertPositionNode -> next;
	insertPositionNode -> next = insertNode;
	return p;
}

link* delLinkNode(link* p, int data){
	link* deletePositionNode = findLinkNode(p, data);
	if(p == NULL){
		printf("链表为空\n");
		return NULL;
	}
	int i = 0;
	link* lastNode = findlastLinkNode(p, data);
	if(lastNode == NULL){// 此时说明要删除的是链表的头节点
		p = deletePositionNode -> next;
		deletePositionNode -> next = NULL;
		return p;
	}
	link* delNode = lastNode -> next;
	printf("delNode: %d\n", delNode -> data);
	lastNode -> next = lastNode -> next -> next;
	printf("lastNode -> next -> data: %d\n", lastNode -> next -> data);
	free(delNode);//释放节点，目的：防止内存泄漏
	return p;
}

link* changeNodeData(link* p, int lastData, int newData){
	if(p == NULL){
		printf("链表为空，无法修改");
		return NULL;
	}	
	link *node = findLinkNode(p, lastData);
	printf("%d\n", node ->data);
	if(node == NULL){
		printf("不存在带有这个数据的节点");
		return NULL;
	}
	node -> data = newData;
	return node;
}

int main(){
	link *p = initLink(5);
	link *temp = p;
	printf("初始化后的链表为\n");
	while(temp -> next != NULL){
		printf("%d -> ", temp -> data);
		temp = temp -> next;
	}
	printf("%d\n", temp -> data);
	link *n = findLinkNode(p, 3);
	printf("数据域为：3的节点：%d\n", n -> data);
	link *ln = findlastLinkNode(p, 3);
	printf("数据域为：3的前身节点：%d\n", ln -> data);
	link *insertn = insertLinkNode(p, 9, 2);
	printf("插入数据域为9的节点到数据域为2的节点的后面...\n打印结果:\n");
	int i = 0;
	while(insertn -> next != NULL){
		printf("%d -> ", insertn -> data);
		insertn = insertn -> next;
	}
	printf("%d\n", insertn -> data);

	link *deleten = delLinkNode(p, 1);
	printf("删除后的链表为:\n");
	if (deleten == NULL){
		printf("请初始化链表，目前您的链表是空的！");
		return 0;
	}
	p = deleten;
	while(deleten -> next != NULL){
		printf("%d -> ", deleten -> data);
		deleten = deleten -> next;
	}
	printf("%d\n", deleten -> data);
	
	link *changen = changeNodeData(p, 2, 6);
	if(changen != NULL){
		printf("改变后的节点：%d\n", changen -> data);
	}
	link *cp = p;
	while(cp -> next != NULL){
		printf("%d -> ", cp -> data);
		cp = cp ->next;
	}
	printf("%d\n", cp -> data);
//	发现的小问题
//	int* w,q;
//	int e = 1;
//	q = &e;
//	w = &e;
	return 0;
}

