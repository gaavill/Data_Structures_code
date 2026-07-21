#pragma once

//队列
/*
//队列是一个插入和删除功能受到限制的线性表
队列和栈受到的限制不一样
栈是只能在一端进行插入和删除
队列是如果在一端进行插入 就要在另一端进行删除
特性：先进先出 First In First Out

例如 ：排队买票 后来的只能排在最后 先买好票的只能从前面出去

队列插入叫做 入队
队列删除叫做 出队

插入的一端叫做队尾
删除的一端叫做队头
尾进头出

//用线性表实现队列
单链表 插入删除 时间复杂度 头插O(1) 尾删O(n)
单链表 插入删除 时间复杂度 头删O(1) 尾插O(n)
这样无法达到两个操作都是O(1)
所以对单链表的节点结构进行改造 让辅助节点保存第一个有效节点和尾节点
//用尾插模拟链式队列的入队操作
//用头删模拟链式队列的出队操作

*/

typedef int ELEMTYPE;

//结构体设计

//辅助节点设计 为了让入队出队操作时间复杂度为O(1)
typedef struct Link_Queue
{
	struct LQNode* front;//队头指针
	struct LQNode* rear;//队尾指针
}Link_Queue;

//有效节点设计
typedef struct LQNode
{
	ELEMTYPE data;
	struct LQNode* next;
}LQNode;

//函数

//初始化
void Init_LQ(Link_Queue* plq);

//入队 用尾插模拟
bool Push_LQ(Link_Queue* plq,ELEMTYPE val);

//出队 用头删模拟
bool Pop_LQ(Link_Queue* plq);

//获取队头元素值
ELEMTYPE Front_LQ(Link_Queue* plq);

//获取当前队列有效元素个数
int Size_LQ(Link_Queue* plq);

//判空
bool Empty_LQ(Link_Queue* plq);

//销毁
void Destroy_LQ(Link_Queue* plq);

//打印
void Print_LQ(Link_Queue* plq);