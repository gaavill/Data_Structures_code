#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Link_Queue.h"





//函数

//初始化 不带辅助头节点
void Init_LQ(Link_Queue* plq)
{
	assert(plq != NULL);
	plq->front = NULL;
	plq->rear = NULL;
}

//入队 用尾插模拟
bool Push_LQ(Link_Queue* plq, ELEMTYPE val)
{
	assert(plq != NULL);

	//申请新节点
	LQNode* pnewnode = (LQNode*)malloc(sizeof(*pnewnode));
	if (pnewnode == NULL)
	{
		return false;
	}
	pnewnode->data = val;

	//特殊情况 队列为空
	if (Empty_LQ(plq))
	{
		pnewnode->next = NULL;
		plq->front = plq->rear = pnewnode;
		return true;
	}

	//正常情况 找到插入位置
	
	//修改指针域
	pnewnode->next = plq->rear->next;
	//保存尾节点
	plq->rear->next = pnewnode;
	plq->rear = pnewnode;
	return true;
}

//出队 用头删模拟
bool Pop_LQ(Link_Queue* plq)
{
	assert(plq != NULL);
	if (Empty_LQ(plq))
	{
		return false;
	}

	//特殊情况 队列中只有一个有效节点
	if (plq->front == plq->rear)
	{
		free(plq->front);
		plq->front = plq->rear = NULL;
		return true;
	}

	//正常情况
	LQNode* del = plq->front;
	//修改指针域
	plq->front = del->next;
	//释放删除节点
	free(del);
	return true;
}

//获取队头元素值
ELEMTYPE Front_LQ(Link_Queue* plq)
{
	assert(plq != NULL);
	assert(!Empty_LQ(plq));
	return plq->front->data;
}

//获取当前队列有效元素个数
int Size_LQ(Link_Queue* plq)
{
	assert(plq != NULL);
	int size = 0;
	for (LQNode* cur = plq->front; cur != NULL; cur = cur->next)
	{
		size++;
	}
	return size;
}

//判空
bool Empty_LQ(Link_Queue* plq)
{
	assert(plq != NULL);
	return plq->front == NULL;
}

//销毁
void Destroy_LQ(Link_Queue* plq)
{
	assert(plq != NULL);
	//双指针
	LQNode* del = plq->front;
	LQNode* next = NULL;
	while (del!=NULL)
	{
		next = del->next;
		free(del);
		del = next;
	}
	plq->front = NULL;
	plq->rear = NULL;
}

//打印
void Print_LQ(Link_Queue* plq)
{
	assert(plq != NULL);
	for (LQNode* cur = plq->front; cur != NULL; cur = cur->next)
	{
		printf("%d ", cur->data);
	}
	printf("\n");
}



//text
int main()
{
	Link_Queue head;
	Init_LQ(&head);
	for (int i = 0; i < 10; i++)
	{
		Push_LQ(&head, i);
	}
	Print_LQ(&head);
	printf("%d\n",Front_LQ(&head));
	printf("%d\n", Size_LQ(&head));
	Destroy_LQ(&head);
	return 0;
}