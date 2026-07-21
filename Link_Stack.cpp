#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Link_Stack.h"


//函数实现

//初始化
void Init_LS(LSNode* pls)
{
	assert(pls != NULL);
	pls->next = NULL;
}

//入栈 (单链表的头插)
bool Push_LS(LSNode* pls, ELEMTYPE val)
{
	assert(pls != NULL);
	//申请新节点
	LSNode* pnewnode = (LSNode*)malloc(sizeof(*pnewnode));
	if (pnewnode == NULL)
	{
		return false;
	}
	pnewnode->data = val;
	//修改指针域
	pnewnode->next = pls->next;
	pls->next = pnewnode;
	return true;
}

//出栈 (单链表的头删)
bool Pop_LS(LSNode* pls)
{
	assert(pls != NULL);
	if (Empty_LS(pls))
	{
		return false;
	}
	//修改指针域 跨越指向
	LSNode* del = pls->next;
	pls->next = del->next;
	free(del);
	return true;
}

//获取栈顶元素值 获取第一个节点的值
ELEMTYPE Top_LS(LSNode* pls)
{
	assert(pls != NULL);
	assert(!Empty_LS(pls));
	return pls->next->data;
}

//获取当前栈的有效元素个数
int Size_LS(LSNode* pls)
{
	assert(pls != NULL);
	int count = 0;
	for (LSNode* cur = pls->next; cur != NULL; cur = cur->next)
	{
		count++;
	}
	return count;
}

//判空
bool Empty_LS(LSNode* pls)
{
	assert(pls != NULL);
	return pls->next == NULL;
}

//销毁 双指针
void Destroy_LS(LSNode* pls)
{
	assert(pls != NULL);
	LSNode* del = pls->next;
	LSNode* next = NULL;
	while (del != NULL)
	{
		//保存下一个节点
		next = del->next;
		free(del);
		del = next;
	}
	pls->next = NULL;
}

//打印
void Print_LS(LSNode* pls)
{
	assert(pls != NULL);
	for (LSNode* cur = pls->next; cur != NULL; cur = cur->next)
	{
		printf("%d ", cur->data);
	}
	printf("\n");
}


//text
//int main()
//{
//	LSNode s;
//	Init_LS(&s);
//	//入栈
//	for (int i = 0; i < 10; i++)
//	{
//		Push_LS(&s, i);
//	}
//	Print_LS(&s);
//	Pop_LS(&s);
//	Print_LS(&s);
//	printf("%d\n", Top_LS(&s));
//	printf("%d\n", Size_LS(&s));
//	Destroy_LS(&s);
//	return 0;
//}