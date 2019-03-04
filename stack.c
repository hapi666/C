#include<stdio.h>
#include<stdlib.h>
typedef struct Stack
{
	int data;
	Stack 	*next;
	int length;
}Stack;

Stack* initStack(int len){
	Stack *S;
	S = (Stack*)malloc(sizeof(Stack));
	if (S == NULL){
		printf("内存不足\n");
		return NULL;
	}
	S->next = NULL;
	S->length = len;
	return S;
}

bool isEmpty(Stack *S){
	return S->length == 0;
}

// 向栈顶插入元素（压栈）
void Push(int d, Stack *S){
	Stack *temp = (Stack*)malloc(sizeof(Stack));
	if (temp == NULL){
		printf("内存不足\n");
		return;
	}
	temp -> data = d;
	temp -> next = S -> next;
	S -> next = temp;
	S->length++;
}

// 向栈顶删除元素（弹出）
void Pop(Stack *S){
	printf("%d\n", S->next->data);
	if (isEmpty(S)) {
		printf("空栈！\n");
		return;
	}
	S->next = S->next->next;
	S->length--;
}




int main(void){
	Stack *S = initStack(10);
	int i = 0;
	for (i = 0; i < 10; i++) {
		Push(i, S);
	}
	for (i = 0; i < 10; i++) {
		Pop(S);
	}
	return 0;
}





