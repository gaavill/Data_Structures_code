#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <memory.h> 
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Hash_Map_Plus.h"
#include <vld.h>

//函数

//1.初始化
void Init_HashTable_No_head(HashTable_No_head* pht)
{
	assert(pht != NULL);

	for (int i = 0; i < MAXSIZE; i++)
	{
		pht->table[i] = NULL;
	}
}

//2.插入
bool Insert_HashTable_No_head(HashTable_No_head* pht, ELEMTYPE val)
{
	assert(pht != NULL);

	//1.通过哈希函数 得到对应下标
	int index = Hash_No_head(val);

	//2.申请新节点
	HashNode_No_head* newnode = (HashNode_No_head*)malloc(sizeof(*newnode));
	if (newnode == NULL)
	{
		return false;
	}

	//3.赋值
	newnode->data = val;

	//4.修改指针域  直接将新申请的节点变为哈希表中的第一个节点 并且赋值
	newnode->next = pht->table[index];
	pht->table[index] = newnode;

	return true;
}

//2.5哈希函数
int Hash_No_head(ELEMTYPE val)
{
	return abs(val) % MAXSIZE;
}

//3.查找
HashNode_No_head* Find_Hash(HashTable_No_head* pht, ELEMTYPE val)
{
	assert(pht != NULL);

	int index = Hash_No_head(val);

	HashNode_No_head* cur = pht->table[index];

	for (; cur != NULL; cur = cur->next)
	{
		if (cur->data == val)
		{
			return cur;
		}
	}

	return NULL;
}

//4.删除
bool Del_Hash_val_No_head(HashTable_No_head* pht, ELEMTYPE val)
{
	assert(pht != NULL);

	int index = Hash_No_head(val);

	HashNode_No_head* prev = NULL;
	HashNode_No_head* cur = pht->table[index];

	while (cur != NULL)
	{
		if (cur->data == val)
		{
			//处理头删情况
			if (prev == NULL)
			{
				pht->table[index] = cur->next;
			}
			else
			{
				//非头删情况
				prev->next = cur->next;
			}

			free(cur);
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

/***********************************************
方法二：
bool Del_Hash_val(HashTable* pht, ELEMTYPE val)
{
	assert(pht != NULL);

	int index = Hash(val);

	//创建一个头节点辅助
	HashNode dummy;
	dummy.next = pht->table[index];

	HashNode* prev = &dummy;
	HashNode* cur = pht->table[index];

	while (cur != NULL)
	{
		if (cur->data == val)
		{
			prev->next = cur->next;
			free(cur);
			cur = NULL;

			//更新哈希表入口
			pht->table[index] = dummy.next;
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
**************************************************/

//5.打印
void Print_HashTable_No_head(HashTable_No_head* pht)
{
	assert(pht != NULL);

	for (int i = 0; i < MAXSIZE; i++)
	{
		printf("[%d]:", i);
		for (HashNode_No_head* cur = pht->table[i]; cur != NULL; cur = cur->next)
		{
			printf("%d->", cur->data);
		}
		printf("\n");
	}
	printf("\n");
}

//6.销毁 销毁所有哈希桶中的元素
void Destroy_Hash_No_head(HashTable_No_head* pht)
{
	assert(pht != NULL);

	for (int i = 0; i < MAXSIZE; i++)
	{
		HashNode_No_head* cur = pht->table[i];
		while (cur != NULL)
		{
			HashNode_No_head* next = cur->next;
			free(cur);
			cur = next;
		}
		pht->table[i] = NULL;
	}
}

//int main()
//{
//	int arr[] = { 12,67,56,16,25,37,22,29,15,47,48,34 };
//
//	HashTable_No_head s;
//	Init_HashTable_No_head(&s);
//
//	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
//	{
//		Insert_HashTable_No_head(&s, arr[i]);
//	}
//
//	Print_HashTable_No_head(&s);
//
//	Destroy_Hash_No_head(&s);
//
//	return 0;
//}