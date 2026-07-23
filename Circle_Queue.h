#pragma once


//顺序表实现循环队列

/*
1.在使用顺序表实现队列时 会因为控制有效元素个数而浪费空间 所以一般设置为
循环队列 数组的尾节点又指回头节点

2.顺序表循环队列是一种逻辑结构 在真实的物理储存中还是以数组形式存在

3.为了满足判空和判满操作不冲突 约定会浪费一个数组空间 
  即对头指针等于队尾指针的下一位
  实际储存空间 = MAXSIZE - 1

4.判空条件：front == rear  当队头指针等于队尾指针时代表队列中没有元素
  判满条件：(rear+1)% MAXSIZE == front 当队头指针等于队尾指针的下一位

5.获取有效元素个数 (rear - front + MAXSIZE)% MAXSIZE 
  说明：
      当队尾指针大于队头指针时 相减为正数 加上MAXSZIE 再对结果 % MAXSIZE
  以消除加MAXSIZE 的影响
      当队尾指针小于队头指针时 相减为负数 加上MAXSIZE 刚好为有效元素个数
	  并且不受 % MAXSIZE 的影响 

6.顺序表循环队列无法扩容

*/








//结构体设计
typedef int ELEMTYPE;

//最大队列长度
#define MAXSIZE 100 

typedef struct Circle_Queue
{
	ELEMTYPE* arr;//接收malloc 返回值
	int front;//队头指针 指向起始有效元素
	int rear;//队尾指针 指向最后一个有效元素的下一个位置
}Circle_Queue;

//说明：对头指针和队尾指针只是用来说明指针的位置

//函数

//1.初始化
void Init_Circle_Queue(Circle_Queue* pcq);

//2.入队 
bool Push_CQ(Circle_Queue* pcq, ELEMTYPE val);

//3.出队
bool Pop_CQ(Circle_Queue* pcq);

//4.获取队头元素
ELEMTYPE Front_CQ(Circle_Queue* pcq);

//5.获取当前队列有效元素个数
int Get_Size_CQ(Circle_Queue* pcq);

//6.判空
bool Empty_CQ(Circle_Queue* pcq);

//7.判满
bool Full_CQ(Circle_Queue* pcq);

//8.清空队列
void Clear_CQ(Circle_Queue* pcq);

//9.销毁
void Destroy_CQ(Circle_Queue* pcq);

//10.打印
void Print_CQ(Circle_Queue* pcq);

//11.扩容
void Increase_CQ(Circle_Queue* pcq);