#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int data;
    struct Node  *next;
}Node;

typedef struct Queue {
	Node *front;
	Node *rear;
}Queue;

void initQueue(Queue* queue){
	queue -> front = (Node*)malloc(sizeof(Node));
	queue -> rear = (Node*)malloc(sizeof(Node));
	queue -> front = queue -> rear;
	queue -> front -> next = NULL;
}

// 入队列
void enQueue(Queue *queue, int newData){
	// printf("%d\n", newData);
	Node *node = (Node*)malloc(sizeof(Node));
	node -> data = newData;
	node -> next = NULL;
	queue -> rear -> next = node;
	queue -> rear = node;
}

// 出队列
int deQueue(Queue *queue){
	if(queue -> front == queue -> rear){
		printf("队列为空！\n");
		return -1;
	}
	Node *n = queue -> front -> next;
	int val = n -> data;
	queue -> front -> next = n -> next;
	if(queue -> rear == n){
		queue -> rear = queue -> front;
	}
	free(n);
	n = NULL;
	// printf("%d\n", val);
	return val;
}

int main(void){
	Queue *queue;
	int i=0;
	initQueue(queue);
	for(i = 1; i <= 10; i++){
		enQueue(queue, i);
	}
	int t;
	for(i = 0; i < 10; i++){
		t = deQueue(queue);
		printf("%d\n", t);
	}
	return 0;
}



