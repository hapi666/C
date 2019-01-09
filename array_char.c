#include<stdio.h>
int main(){
	// C 语言定义字符数组的两种方式
	char a[5]={'h','e','l','l','o' };
	char b[]="world";
	int i = 0;
	for(i = 0; i < 5; i++){
		printf("%c", a[i]);
	}
	putchar('\n');
	for(i = 0; i < 5; i++){
		printf("%c", b[i]);
	}
	putchar('\n');
	return 0;
}
