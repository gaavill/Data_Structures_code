#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <memory.h> 
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"






//顺序表：通过一片连续的空间 有序的存储数据 如数组
//逻辑上连续 物理上也连续
//链表：是一种通过指针将多个节点连接起来的数据结构  等于节点+指针
//逻辑上连续 物理上不一定连续
//数组靠连续内存存储数据 链表靠指针将数据串联起来  
//链表的组成：每个节点(Node)包含两部分
//每一个节点都保存着下一个节点的地址
//typedef struct Node
//{
//	int data;//数据域 保存当前节点的关键字
//	struct Node* next;//指针域  保存下一个有效节点的地址
//}Node;
//1->2->3->NULL
//带头单链表 head->1->2->3->NULL 头节点不存有效数据
//单链表的辅助节点：有一个指针域 用来保存第一个有效节点的地址 不存有效数据
 

//函数
//初始化

//插入：
//1.头插
//2.尾插
//中间插入(根据传递进来的pos下标进行插入)

//删除：
//1.头删
//2.尾删
//3.中间位置删除(根据传递进来的pos下标进行删除)
//4.按值删除(只删除这个值出现的第一个节点)
//5.按值删除(删除这个值出现的所有节点)

//查找：
//查找(函数)：查找一个值是否存在 存在的话返回其节点

//改：找到对应节点 将值更改

//销毁：
//1.无限头删，需要借助辅助节点
//2.不需要借助辅助节点，只需要两个指针p和q配合

//判空函数

//获取有效节点个数

//打印函数

//函数
//初始化
void Init_List(Node* plist)
{
	assert(plist != NULL);
	//plist->data;//不使用
	plist->next = NULL;
}

//插入：
// 步骤：1.开辟一个新节点 2.找到插入位置(找插入在哪一个节点后面) 3.修改指针域
//1.头插
bool Insert_head(Node* plist, ELEMTYPE val)
{
	assert(plist != NULL);
	//1.购买新节点 修改其成员
	Node* pnewnode = (Node*)malloc(sizeof(Node));
	if (pnewnode == NULL)
	{
		return false;
	}
	pnewnode->data = val;
	//2.找到插入位置(相当于需要找到在哪一个节点后插入 这个节点用p指向他)
	pnewnode->next = plist->next;
	//这一步比较特殊 因为是头插 一定在辅助节点之后 可以直接用辅助节点
	//3.插入(修改两个指针域 先修改插入数据的指针域)
	plist->next = pnewnode;
	return true;
}

//2.尾插
bool Insert_tail(Node* plist, ELEMTYPE val)
{
	assert(plist != NULL);
	//1.购买新节点
	Node* pnewnode = (Node*)malloc(sizeof(Node));
	if (pnewnode == NULL)
	{
		return false;
	}
	pnewnode->data = val;//修改数据域
	//2.找插入位置
	Node* p;//让指针从辅助节点走到要插入位置 这里是最后一位
	for (p = plist; p->next != NULL; p = p->next);
	//3.修改指针域 先修改新加入的
	pnewnode->next = p->next;//p->next== NULL
	p->next = pnewnode;
	return true;
}

/*************************************************************************/
//对于需要找到当前节点的上一个节点位置的函数例如插入删除 
//如果需要让指针向后跑 统一从辅助节点出发
//for (Node* p = plist; p->next != NULL; p = p->next);
//对于不需要找到当前节点的上一个节点位置的函数例如查找 获取长度 打印 
//如果需要让指针向后跑 统一从第一个有效节点节点出发
//for (Node* p = plist->next; p != NULL; p = p->next);
/*************************************************************************/
//中间插入(根据传递进来的pos下标进行插入) 0 <= pos <= 有效节点个数
//需要将辅助指针p指向pos的位置 pos等于多少 则让p从辅助节点出发向后走pos步即可
bool Insert_pos(Node* plist, int pos, ELEMTYPE val)
{
	assert(plist != NULL);
	assert(pos >= 0 && pos <= Get_Lenght(plist));
	Node* pnewnode = (Node*)malloc(sizeof(Node));
	if (pnewnode == NULL)
	{
		return false;
	}
	pnewnode->data = val;
	pnewnode->next = NULL;
	Node* p = plist;
	for (int i = 0; i < pos; i++)
	{
		p = p->next;
	}
	pnewnode->next = p->next;
	p->next = pnewnode;
	return true;
}

//删除：
//1.找到待删除节点用指针q指向 2.找到待删除节点的上一个节点用指针p指向 3.跨越待删除节点并释放待删除节点
//1.头删
bool Del_head(Node* plist)
{
	assert(plist != NULL);
	//判空
	if (plist->next == NULL)
	{
		return false;
	}
	//1.找到待删除节点 用指针q指向
	Node* q = plist->next;
	//2.找到待删除节点的上家 用指针p指向
	
	//3.跨越指向(待删除节点上家指向待删除节点下家)
	plist->next = q->next;
	//4.释放
	free(q);
	q = NULL;
	return true;
}

//2.尾删
bool Del_tail(Node* plist)
{
	assert(plist != NULL);
	if (plist->next == NULL)
	{
		return false;
	}
	//1.找到删除位置
	//Node* q;
	//for (q = plist; q->next != NULL; q = q->next);
	//Node* p;
	//for (p = plist; p->next != q; p = p->next);
	Node* prev = plist;
	Node* cur = plist->next;
	//2.跨越待删除节点 并释放待删除节点
	while (cur->next != NULL)
	{
		prev = cur;
		cur = cur->next;
	}
	prev->next = cur->next;
	free(cur); cur = NULL;
	return true;
}

//3.中间位置删除(根据传递进来的pos下标进行删除) pos代表第几个有效节点 从0开始 相当于数组下标
//prev代表前驱 也是要操作节点的上一个节点 cur代表要操作节点
bool Del_pos(Node* plist, int pos)
{
	assert(plist != NULL);
	assert(pos >= 0 && pos < Get_Lenght(plist));
	Node* prev = plist;
	Node* cur = plist->next;
	while (pos--)
	{
		prev = cur;
		cur = cur->next;
	}
	//for (int i = 0; i < pos; i++)
	//{
	//	prev = prev->next;
	//}
	//cur = prev->next;
	prev->next = cur->next;
	free(cur); cur = NULL;
	return true;
}

//4.按值删除(只删除这个值出现的第一个节点)
bool Del_val_First(Node* plist, ELEMTYPE val)
{
	//0.assert
	assert(plist != NULL);
	//1.先判断val是否存在 调用 search 函数判断
	Node* cur = Search(plist, val);
	if (cur == NULL)
	{
		return false;
	}
	//2.若p==NULL 直接返回 false 若!=NULL 则说明要进行删除
	//3.找到待删除节点的上一个节点 用指针p指向
	Node* prev = plist;
	for (; prev->next != cur; prev = prev->next);
	//4.跨越指向加释放
	prev->next = cur->next;
	free(cur); cur = NULL;
	return true;
}

//5.按值删除(删除这个值出现的所有节点)
bool Del_val_All(Node* plist, ELEMTYPE val)
{
	assert(plist != NULL);
	//利用双指针 依次删除
	Node* prev = plist;
	Node* cur = plist->next;
	if (Empty_Node(plist))
	{
		return false;
	}
	while (cur)
	{
		if (cur->data == val)
		{
			prev->next = cur->next;//跨越指向
			free(cur);
			cur = prev->next;//prev不能移动
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
	return true;
}

//查找：
//查找(函数)：查找一个值是否存在 存在的话返回其节点
Node* Search(Node* plist, ELEMTYPE val)
{
	assert(plist != NULL);
	for (Node* cur = plist->next; cur != NULL;cur=cur->next)
	{
		if (cur->data == val)
		{
			return cur;
		}
	}
	return NULL;
}

//改：找到对应节点 将值更改

//销毁：
//1.无限头删，需要借助辅助节点
void Destroy1(Node* plist)
{
	//1.进入while循环 循环条件是单链表是否为NULL 不为空就进行一次头删
	assert(plist != NULL);
	while (!Empty_Node(plist))
	{
		Del_head(plist);
	}
}

//2.不需要借助辅助节点，只需要两个指针p和q配合
void Destroy2(Node* plist)
{
	//让next保存当前节点的下一个节点 再释放当前节点 cur移动到下一个节点  
	assert(plist != NULL);
	Node* cur = plist->next;
	Node* next = NULL;
	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	plist->next = NULL;
}

//判空函数
bool Empty_Node(Node* plist)
{
	assert(plist != NULL);
	return plist->next == NULL;
}

//获取有效节点个数
int Get_Lenght(Node* plist)
{
	assert(plist != NULL);
	int count = 0;
	for (Node* p = plist->next; p != NULL; p = p->next)
	{
		count++;
	}
	return count;
}

//打印函数
void Show(Node* plist)
{
	for (Node* p = plist->next; p != NULL; p = p->next)
	{
		printf("%d ", p->data);
	}
	printf("\n");
}

/******************************************************************************************************************/


/******************************************************************************************************************/


