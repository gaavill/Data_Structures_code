#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <memory.h> 
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Circle_Queue.h"
#include <vld.h>


//函数

//1.初始化
void Init_Circle_Queue(Circle_Queue* pcq)
{
	assert(pcq != NULL);
	pcq->arr = (ELEMTYPE*)malloc(MAXSIZE * sizeof(ELEMTYPE));
	if (pcq->arr == NULL)
	{
		exit(EXIT_FAILURE);
	}
	pcq->front = 0;
	pcq->rear = 0;
}

//2.入队 
bool Push_CQ(Circle_Queue* pcq, ELEMTYPE val)
{
	assert(pcq != NULL);
	if (Full_CQ(pcq))
	{
		return false;
	}
	//正常情况下 有数据
	pcq->arr[pcq->rear] = val;
	pcq->rear = (pcq->rear + 1) % MAXSIZE;
	return true;
}

//3.出队
bool Pop_CQ(Circle_Queue* pcq)
{
	assert(pcq != NULL);
	if (Empty_CQ(pcq))
	{
		return false;
	}
	pcq->front = (pcq->front + 1) % MAXSIZE;
	return true;
}

//4.获取队头元素
ELEMTYPE Front_CQ(Circle_Queue* pcq)
{
	assert(pcq != NULL);
	assert(!Empty_CQ(pcq));
	return pcq->arr[pcq->front];
}

//5.获取当前队列有效元素个数
int Get_Size_CQ(Circle_Queue* pcq)
{
	assert(pcq != NULL);
	return (pcq->rear - pcq->front + MAXSIZE) % MAXSIZE;
}

//6.判空
bool Empty_CQ(Circle_Queue* pcq)
{
	assert(pcq != NULL);
	return pcq->front == pcq->rear;
}

//7.判满
bool Full_CQ(Circle_Queue* pcq)
{
	assert(pcq != NULL);
	return (pcq->rear + 1) % MAXSIZE == pcq->front;
}

//8.清空队列
void Clear_CQ(Circle_Queue* pcq)
{
	assert(pcq != NULL);
	pcq->front = pcq->rear = 0;
}

//9.销毁
void Destroy_CQ(Circle_Queue* pcq)
{
	assert(pcq != NULL);
	free(pcq->arr);
	pcq->arr = NULL;
	pcq->front = 0;
	pcq->rear = 0;
}

//10.打印
void Print_CQ(Circle_Queue* pcq)
{
	assert(pcq != NULL);
	//需要通过取余的方法 让指针可以在数组尾处重新回到数组起始位置
	for (int i = pcq->front; i != pcq->rear; i = (i + 1) % MAXSIZE)
	{
		printf("%d ", pcq->arr[i]);
	}
	printf("\n");
}





//text
//int main()
//{
//	Circle_Queue s;
//	Init_Circle_Queue(&s);
//
//	for (int i = 0; i < 10; i++)
//	{
//		Push_CQ(&s, i);
//	}
//	Print_CQ(&s);
//
//	Pop_CQ(&s);
//	Pop_CQ(&s);
//	Print_CQ(&s);
//
//	printf("%d\n", Get_Size_CQ(&s));
//
//	printf("%d\n", Front_CQ(&s));
//
//	Clear_CQ(&s);
//	Print_CQ(&s);
//	printf("%d\n", Get_Size_CQ(&s));
//
//	Destroy_CQ(&s);
//	return 0;
//}