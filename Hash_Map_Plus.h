#pragma once


//此处实现哈希表的另一个版本 即数组中存储哈希桶的第一个有效节点

typedef int ELEMTYPE;

#define MAXSIZE 12

//哈希桶节点设计
typedef struct HashNode_No_head
{
	ELEMTYPE data;
	struct HashNode_No_head* next;

}HashNode_No_head;


//哈希表设计
typedef struct HashTable_No_head
{
	HashNode_No_head* table[MAXSIZE];

}HashTable_No_head;


//函数

//1.初始化
void Init_HashTable_No_head(HashTable_No_head* pht);

//2.插入
bool Insert_HashTable_No_head(HashTable_No_head* pht, ELEMTYPE val);

//2.5哈希函数
int Hash_No_head(ELEMTYPE val);

//3.查找
HashNode_No_head* Find_Hash_No_head(HashTable_No_head* pht, ELEMTYPE val);

//4.删除
bool Del_Hash_val_No_head(HashTable_No_head* pht, ELEMTYPE val);

//5.打印
void Print_HashTable_No_head(HashTable_No_head* pht);

//6.销毁 销毁所有哈希桶中的元素
void Destroy_Hash_No_head(HashTable_No_head* pht);