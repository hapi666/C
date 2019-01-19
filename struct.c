#include<stdio.h>
// 讨论一下C语言里定义 struct 的方式。
// 以及对比一下go语言里面的 struct 跟C有什么共性和异同

// 基本定义模式：
// struct [structure tag]
// {
// 		member definition;
// } [one or more struicture variables];
// 带[]是可选的参数，比方说那个 structure tag 是可选的

// 第一种定义方式
// 定义一个结构体 tag 为 A
struct A
{
	int a;
	char b;
	float c;
	double d;
};

// 第二种定义方式 
// 定义一个结构体 不加标签 同时为这个结构体定义变量 st
struct
{
	int e;
} st;

// 第三种定义方式
// typedef 关键字是给已有类型定义别名
// 在这里我们给 struct { char m;} 定义一个别名 tyst
// 在这之后为这个 struct 定义结构体变量的时候，只需要用 tyst定义就好了
typedef struct
{
	char m;
} tyst;

int main(){
	// 为第一种定义定义结构体
	A t1, t2;
	// 使用第二种方式的结构体变量 st
	st.e = 6;
	// 给结构体变量字段赋值
	t1.a = 2;
	// 定义第三种结构体变量
	tyst t3;
	// 为定三种结构体变量赋值
	t3.m = '3';
	printf("%d\n", t1.a);
	printf("%d\n", st.e);
	printf("%c\n", t3.m);
}

