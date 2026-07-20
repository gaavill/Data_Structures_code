#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <memory.h> 
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Double_List.h"
#include <vld.h>

//注意
/*
	DNode* p1 = pdlist;
	for (; p1->next != NULL; p1 = p1->next);  
	//判断下一个节点是否为NULL 是则结束
	//最终停在尾节点 常用来插入删除等

	DNode* p2 = pdlist->next;
	for (; p2 != NULL; p2 = p2->next);  
	//判断当前节点是否为NULL 是就退出
	//最终停留在尾节点的后一位 用来打印等
*/
//双向链表函数实现

//初始化
void Init_Double_Link(DNode* pdlist)
{
	assert(pdlist != NULL);
	pdlist->next = NULL;
	pdlist->prior = NULL;
}

//头插
bool Insert_head_DNode(DNode* pdlist, ELEMTYPE val)
{
	assert(pdlist != NULL);
	//购买新节点
	DNode* pnewnode = (DNode*)malloc(sizeof(DNode));
	if (pnewnode == NULL)
	{
		return false;
	}
	//修改数据域
	pnewnode->data = val;
	//找到插入位置 头插肯定在辅助节点后面

	//修改指针域 分情况 通常修改4个指针域 如果链表本身为空则只需要修改3个
	//先修改插入节点
	pnewnode->next = pdlist->next;//新节点next指向原来第一个节点
	pnewnode->prior = pdlist;//新节点prior指向头节点

	//修改原节点
	if (pdlist->next != NULL)
	{
		pdlist->next->prior = pnewnode;//原第一个节点prior指向新节点
		//连续访问结构体成员 
	}
	
	//修改辅助节点
	pdlist->next = pnewnode;//头节点指向新节点 

	return true;
}

//尾插
bool Insert_tail_DNode(DNode* pdlist, ELEMTYPE val)
{
	assert(pdlist != NULL);
	//购买新节点
	DNode* pnewnode = (DNode*)malloc(sizeof(DNode));
	if (pnewnode == NULL)
	{
		return false;
	}
	//修改数据域
	pnewnode->data = val;
	//找到待插入位置
	//找到待插入节点的上一个节点
	DNode* cur = pdlist;
	for (; cur->next != NULL; cur = cur->next);
	//修改指针域 先修改插入节点 再修改原节点 再修改原节点的上一个节点
	pnewnode->next = cur->next;
	pnewnode->prior = cur;
	cur->next = pnewnode;
	return true;
}

//按位置pos插入 pos=0为头插 pos从0开始
bool Insert_pos_DNode(DNode* pdlist, int pos, ELEMTYPE val)
{
	//pos=0为头插 调用头插函数 pos=Lenght为尾插调用尾插函数
	assert(pdlist != NULL);
	if (pos<0 || pos>Get_Lenght_DNode(pdlist))
	{
		return false;
	}
	//排除特殊情况
	if (pos == 0)
	{
		return Insert_head_DNode(pdlist, val);
	}
	if (pos == Get_Lenght_DNode(pdlist))
	{
		return Insert_tail_DNode(pdlist, val);
	}
	//购买新节点
	DNode* pnewnode = (DNode*)malloc(sizeof(DNode));
	if (pnewnode == NULL)
	{
		return false;
	}
	//修改数据域
	pnewnode->data = val;
	//找到插入位置 
	DNode* prev = pdlist;
	while (pos--)
	{
		prev = prev->next;
	}
	//修改插入节点指针域
	pnewnode->next = prev->next;
	pnewnode->prior = prev;
	//修改原节点
	prev->next->prior = pnewnode;
	//修改原节点上一个节点
	prev->next = pnewnode;
	return true;
}

//头删
bool Del_head_DNode(DNode* pdlist)
{
	assert(pdlist != NULL);
	//判空
	if (Empty_DNode(*pdlist))
	{
		return false;
	}
	//找到待删除节点
	DNode* cur = pdlist->next;
	//找到待删除节点的上一个节点

	//指针域跨越指向(分情况)
	pdlist->next = cur->next;
	if (cur->next != NULL)
	{
		cur->next->prior = pdlist;
	}
	//释放待删除节点
	free(cur);
	cur = NULL;
	return true;
}

//尾删
bool Del_tail_DNode(DNode* pdlist)
{
	//只会修改一个指针域
	assert(pdlist != NULL);
	if (Empty_DNode(*pdlist))
	{
		return false;
	}
	//修改指针域 
	DNode* cur = pdlist;
	for (; cur->next != NULL; cur = cur->next);
	cur->prior->next = cur->next;
	//释放待删除节点
	free(cur);
	cur = NULL;
	return true;
}

//按位置pos删除
bool Del_pos_DNode(DNode* pdlist, int pos)
{
	assert(pdlist != NULL);
	assert(pos > 0 && pos < Get_Lenght_DNode(pdlist));
	//头删有特殊情况 所以调用头删函数特殊处理
	if (pos == 0)
	{
		return Del_head_DNode(pdlist);
	}
	if (pos == Get_Lenght_DNode(pdlist)-1)
	{
		return Del_tail_DNode(pdlist);
	}
	//找到待删除节点
	DNode* cur = pdlist;
	while (pos--)
	{
		cur = cur->next;
	}
	//修改指针域
	cur->prior->next = cur->next;
	cur->next->prior = cur->prior;
	//释放待删除节点
	free(cur);
	cur = NULL;
	return true;
}

//按传入值删除 删除第一次出现的位置
bool Del_val_DNode_first(DNode* pdlist, ELEMTYPE val)
{
	assert(pdlist != NULL);
	if (Empty_DNode(*pdlist))
	{
		return false;
	}
	//调用查找函数 找到待删节点位置
	DNode* cur = Find_DNode(pdlist, val);
	if (cur == NULL)
	{
		return false;
	}
	//修改指针域
	cur->prior->next = cur->next;
	if(cur->next!=NULL)
	{
		cur->next->prior = cur->prior;
	}
	free(cur);
	cur = NULL;
	return true;
}

//按照传入值删除 删除这个值出现的所有节点
bool Del_val_DNode_all(DNode* pdlist, ELEMTYPE val)
{
	assert(pdlist != NULL);
	if (Empty_DNode(*pdlist))
	{
		return false;
	}
	//找到待删除节点
	DNode* cur = pdlist->next;
	while (cur!= NULL)
	{
		if (cur->data == val)
		{
			//保存待删除节点的下一个节点
			DNode* next = cur->next;
			//修改待删除节点的前驱节点
			cur->prior->next = cur->next;
			//修改待删除节点的后继节点
			if (cur->next != NULL)
			{
				cur->next->prior = cur->prior;
			}
			free(cur);
			//继续检查下一个节点
			cur = next;
		}
		else
		{
			//不符合要求 指针向后移动
			cur = cur->next;
		}
	}
	return true;
}

//查找
DNode* Find_DNode(DNode* pdlist, ELEMTYPE val)
{
	assert(pdlist != NULL);
	for (DNode* cur = pdlist->next; cur != NULL; cur = cur->next)
	{
		if (cur->data == val)
		{
			return cur;
		}
	}
	return NULL;
}

//销毁1 无限头删
void Destroy1_DNode(DNode* pdlist)
{
	assert(pdlist != NULL);
	while (pdlist->next != NULL)
	{
		Del_head_DNode(pdlist);
	}
}

//销毁2 不借助头节点
void Destroy_DNode(DNode* pdlist)
{
	assert(pdlist != NULL);
	DNode* cur = pdlist->next;
	DNode* next = NULL;
	while (cur!= NULL)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	pdlist->next = NULL;
}

//判空函数
bool Empty_DNode(DNode dlist)
{
	return dlist.next == NULL;
}

//获取有效节点个数
int Get_Lenght_DNode(DNode* pdlist)
{
	assert(pdlist != NULL);
	int count = 0;
	for (DNode* cur = pdlist->next; cur != NULL; cur = cur->next)
	{
		count++;
	}
	return count;
}

//打印函数
void Print_DNode(DNode* pdlist)
{
	assert(pdlist != NULL);
	for (DNode* cur = pdlist->next; cur != NULL; cur = cur->next)
	{
		printf("%d ", cur->data);
	}
	printf("\n");
}




//Text
//int main()
//{
//	DNode s;
//	Init_Double_Link(&s);
//
//	Insert_head_DNode(&s, 34);
//	Insert_head_DNode(&s, 90);
//
//	Print_DNode(&s);
//
//	Insert_tail_DNode(&s, 12);
//	Insert_tail_DNode(&s, 89);
//
//	Print_DNode(&s);
//
//	Insert_pos_DNode(&s, 4, 91);
//	Insert_pos_DNode(&s, 2, 91);
//	Insert_pos_DNode(&s, 1, 91);
//
//	Print_DNode(&s);
//
//	//Del_head_DNode(&s);
//	//Print_DNode(&s);
//	//Del_tail_DNode(&s);
//	//Print_DNode(&s);
//	//Del_pos_DNode(&s, 2);
//	//Print_DNode(&s);
//	Del_val_DNode_first(&s, 91);
//	Print_DNode(&s);
//	Del_val_DNode_all(&s, 91);
//	Print_DNode(&s);
//
//	Destroy1_DNode(&s);
//
//	return 0;
//}