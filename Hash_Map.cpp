#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <memory.h> 
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Hash_Map.h"
#include <vld.h>



//1.初始化
void Init_HashTable(HashTable* pht)
{
	assert(pht != NULL);

	//将每一个链表的头节点next置为空
	for (int i = 0; i < MAXSIZE; i++)
	{
		pht->table[i].next = NULL;
	}
}

//2.插入 用头插实现 这个哈希表允许插入值重复
bool Insert_HashTable(HashTable* pht, ELEMTYPE val)
{
	assert(pht != NULL);

	//1.通过哈希函数 找到数组下标
	int index = Hash(val);

	//2.申请一个新节点
	HashNode* newnode = (HashNode*)malloc(sizeof(*newnode));
	if (newnode == NULL)
	{
		return false;
	}

	//3.赋值
	newnode->data = val;

	//4.修改节点指针域
	newnode->next = pht->table[index].next;
	pht->table[index].next = newnode;

	return true;
}

//2.5哈希函数
int Hash(ELEMTYPE val)
{
	return abs(val) % MAXSIZE;
}

//3.查找
HashNode* Find_Hash(HashTable* pht, ELEMTYPE val)
{
	assert(pht != NULL);

	//1.通过哈希函数得到相应的单链表
	int index = Hash(val);

	//2.遍历链表 找到对应值并返回
	HashNode* cur = pht->table[index].next;
	while (cur != NULL)
	{
		if (cur->data == val)
		{
			return cur;
		}
		cur = cur->next;
	}
	
	return NULL;
}

//4.删除
bool Del_Hash_val(HashTable* pht, ELEMTYPE val)
{
	assert(pht != NULL);

	//1.通过哈希函数 找到对应哈希桶
	int index = Hash(val);

	//2.遍历整个链表 找到需要删除的节点
	HashNode* prev = &pht->table[index];//头节点
	HashNode* cur = pht->table[index].next;//第一个有效节点
	while (cur != NULL)
	{
		if (cur->data == val)
		{
			prev->next = cur->next;
			free(cur);
			cur = NULL;

			return true;
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}

	return false;
}

//5.打印
void Print_HashTable(HashTable* pht)
{
	assert(pht != NULL);

	for (int i = 0; i < MAXSIZE; i++)
	{
		printf("[%d]:", i);
		for (HashNode* cur = pht->table[i].next; cur != NULL; cur = cur->next)
		{
			printf("%d->", cur->data);
		}
		printf("\n");
	}
	printf("\n");
}

//6.销毁 销毁所有哈希桶中的元素
void Destroy_Hash(HashTable* pht)
{
	assert(pht != NULL);

	for (int i = 0; i < MAXSIZE; i++)
	{
		HashNode* cur = pht->table[i].next;
		while (cur != NULL)
		{
			HashNode* next = cur->next;
			free(cur);
			cur = next;
		}
		pht->table[i].next = NULL;
	}
}

//int main()
//{
//	int arr[] = { 12,67,56,16,25,37,22,29,15,47,48,34 };
//
//	HashTable s;
//	Init_HashTable(&s);
//
//	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
//	{
//		Insert_HashTable(&s, arr[i]);
//	}
//
//	Print_HashTable(&s);
//
//	Destroy_Hash(&s);
//
//	return 0;
//}