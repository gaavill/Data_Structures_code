#pragma once

//栈和队列：
//栈是一种数据结构 不同于内存储存中的栈区 但是两者的工作方式相同
//栈是一个功能受到限制的线性表
/*
 只能在一端进行插入/删除操作
 一般将插入和删除的这一端称为栈顶Top 相反另一端称为栈低Bottom

 插入操作：入栈/压栈
 删除操作：出栈/弹栈
 
 特性：后进先出 Last In First Out 
 通过栈特性实现 ctrl + Z ctrl + Y
 
 //根据储存结构可分：
 顺序表实现栈：顺序栈
 单链表实现栈：链栈

 //栈是在表尾进行插入和删除的线性表 表尾这一端被称为栈顶

 顺序表实现栈
 如果将线性表头部设置为栈顶 时间复杂度 入栈O(n) 出栈O(n)
 如果将线性表尾部设置为栈顶 时间复杂度 入栈O(1) 出栈O(1) 

 单链表实现栈
 如果将单链表的头部设置为栈顶 时间复杂度 入栈O(1) 出栈O(1)
 如果将单链表的尾部设置为栈顶 时间复杂度 入栈O(n) 出栈O(n) 

*/

//顺序表实现栈

typedef int ELEMTYPE;
//初始分配空间大小(以格子为单位)
#define INITSIZE 10 

typedef struct Seq_Stack
{
	ELEMTYPE* arr;//存储空间地址 
	int length;//当前元素个数
	int capacity;//当前栈的容量
}Seq_Stack;


//初始化
void Init_SS(Seq_Stack* pss);

//入栈
bool Push_SS(Seq_Stack* pss,ELEMTYPE val);

//出栈
bool Pop_SS(Seq_Stack* pss);

//获取栈顶元素
ELEMTYPE Top_SS(Seq_Stack ss);

//获取当前栈的有效元素个数
int Size_SS(Seq_Stack ss);

//判空
bool Empty_SS(Seq_Stack ss);

//判满
bool Full_SS(Seq_Stack ss);

//扩容
bool Increase_SS(Seq_Stack* pss);

//清空栈中元素
void Clear_SS(Seq_Stack* pss);

//销毁
void Destroy_SS(Seq_Stack* pss);

//打印
void Print_SS(Seq_Stack ss);
