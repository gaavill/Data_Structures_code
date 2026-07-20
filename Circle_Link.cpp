#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <memory.h> 
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Circle_Link.h"
#include <vld.h>

//1.初始化
void Init_CLink(CNode* plist)
{
	assert(plist != NULL);
	//数据域
	plist->next = plist;
}

//2.头插
bool Insert_head_CLink(CNode* plist, ELEMTYPE val)
{
	assert(plist != NULL);
	//购买新节点
	CNode* pnewCNode = (CNode*)malloc(sizeof(CNode));
	if (pnewCNode == NULL)
	{
		return false;
	}
	//添加数据域
	pnewCNode->data = val;
	//跨越指向
	pnewCNode->next = plist->next;
	plist->next = pnewCNode;
	return true;
}

//3.尾插
bool Insert_tail_CLink(CNode* plist, ELEMTYPE val)
{
	assert(plist != NULL);
	//购买新节点
	CNode* pnewCNode = (CNode*)malloc(sizeof(CNode));
	if (pnewCNode == NULL)
	{
		return false;
	}
	//添加数据域
	pnewCNode->data = val;
	//将指针从头节点移动到最后一个元素
	CNode* cur = plist;
	for (cur; cur->next != plist; cur = cur->next);
	//修改指针域
	pnewCNode->next = cur->next;
	cur->next = pnewCNode;
	return true;

}

//4.按下标pos插入
bool Insert_pos_CLink(CNode* plist, int pos, ELEMTYPE val)
{
	assert(plist != NULL);
	if (pos<0 || pos>Get_count_CLink(plist))
	{
		return false;
	}
	//购买新节点
	CNode* pnewCNode = (CNode*)malloc(sizeof(CNode));
	if (pnewCNode == NULL)
	{
		return false;
	}
	//添加数据域
	pnewCNode->data = val;
	//找到插入位置 
	CNode* prev = plist;
	while (pos--)
	{
		prev = prev->next;
	}
	//修改指针域
	pnewCNode->next = prev->next;
	prev->next = pnewCNode;
	return true;
}

//5.头删
bool Del_head_CLink(CNode* plist)
{
	assert(plist != NULL);
	if (Empty_CLink(plist))
	{
		return false;
	}
	//跨越指向
	CNode* cur = plist->next;
	plist->next = cur->next;
	//释放待删除节点
	free(cur);
	cur = NULL;
	return true;
}

//6.尾删
bool Del_tail_CLink(CNode* plist)
{
	assert(plist!= NULL);
	if (Empty_CLink(plist))
	{
		return false;
	}
	//找到待删除节点的前一个节点 双指针
	CNode* prev = plist;
	CNode* cur = plist->next;
	while (cur->next != plist)
	{
		prev = cur;
		cur = cur->next;
	}
	//修改指针域
	prev->next = cur->next;
	free(cur);
	cur = NULL;
	return true;
}

//7.按照下标删
bool Del_pos_CLink(CNode* plist, int pos)
{
	assert(plist != NULL);
	if (pos<0 || pos>=Get_count_CLink(plist))
	{
		return false;
	}
	//找到待删除节点 双指针
	CNode* prev = plist;
	CNode* cur = plist->next;
	while (pos--)
	{
		prev = cur;
		cur = cur->next;
	}
	//修改指针域
	prev->next = cur->next;
	//释放待删除节点
	free(cur);
	cur = NULL;
	return true;
}

//8.按照传入值删 删除第一次出现的位置
bool Del_val_first(CNode* plist, ELEMTYPE val)
{
	assert(plist != NULL);
	//利用查找函数 找到待删除节点的位置
	CNode* cur = Find_first_CLink(plist, val);
	if (cur == NULL)
	{
		return false;
	}
	//找到待删除节点的上一个节点
	CNode* prev = plist;
	for (prev; prev->next != cur; prev = prev->next);
	//跨越指向
	prev->next = cur->next;
	//释放待删除节点
	free(cur);
	cur = NULL;
	return true;
}

//9.按照传入值删 删除出现的所有位置
bool Del_val_all(CNode* plist, ELEMTYPE val)
{
	//双指针
	assert(plist != NULL);
	if (Empty_CLink(plist))
	{
		return false;
	}
	CNode* prev = plist;
	CNode* cur = plist->next;
	while (cur!=plist)
	{
		if (cur->data == val)
		{
			prev->next = cur->next;
			free(cur);
			cur = prev->next;
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
	return true;
}

//10.查找 找到传入值出现的第一个位置 并返回
CNode* Find_first_CLink(CNode* plist, ELEMTYPE val)
{
	assert(plist != NULL);
	if (Empty_CLink(plist))
	{
		return NULL;
	}
	for (CNode* cur = plist->next; cur != plist; cur = cur->next)
	{
		if (cur->data == val)
		{
			return cur;
		}
	}
	return NULL;
}

//11.销毁1 无限头删
void Destory_CLink1(CNode* plist)
{
	assert(plist != NULL);
	while (!Empty_CLink(plist))
	{
		Del_head_CLink(plist);
	}
}

//12.销毁2 双指针
void Destory_CLink2(CNode* plist)
{
	assert(plist != NULL);
	CNode* cur = plist->next;
	CNode* next = NULL;
	while (cur!=plist)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	plist->next = plist;
}

//13.判空
bool Empty_CLink(CNode* plist)
{
	assert(plist != NULL);
	return plist->next == plist;
}

//14.获取有效节点个数
int Get_count_CLink(CNode* plist)
{
	assert(plist != NULL);
	int count = 0;
	for (CNode* cur = plist->next; cur != plist; cur = cur->next)
	{
		count++;
	}
	return count;
}

//15.打印
void Print_CLink(CNode* plist)
{
	assert(plist != NULL);
	for (CNode* cur = plist->next; cur != plist; cur = cur->next)
	{
		printf("%d ", cur->data);
	}
	printf("\n");
}


/************************************************************************************************/
//Text
//int main()
//{
//	CNode s;
//	//初始化
//	Init_CLink(&s);
//	//头插
//	Insert_head_CLink(&s,2);
//	Insert_head_CLink(&s, 1);
//	//尾插
//	Insert_tail_CLink(&s, 3);
//	Insert_tail_CLink(&s, 4);
//	Print_CLink(&s);
//	//按照下标插入
//	Insert_pos_CLink(&s, 2, 91);
//	Print_CLink(&s);
//	//头删除
//	//Del_head_CLink(&s);
//	//尾删
//	//Del_tail_CLink(&s);
//	//按位置删除
//	//Del_pos_CLink(&s, 2);
//	//按值删
//	//Del_val_first(&s, 3);
//	Insert_tail_CLink(&s, 4);
//	Insert_head_CLink(&s, 4);
//	Print_CLink(&s);
//	Del_val_all(&s, 4);
//	
//	Print_CLink(&s);
//	Destory_CLink1(&s);
//
//	return 0;
//}