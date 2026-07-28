#pragma once

//链地址法实现哈希表

typedef int ELEMTYPE;

#define MAXSIZE 12

//有效节点设计
typedef struct HashNode
{
	ELEMTYPE data;
	struct HashNode* next;
}HashNode;

//哈希表设计 这里采用有头节点的链表 即每一个数组单元中存的是链表的头节点(辅助节点)
typedef struct HashTable
{
	HashNode table[MAXSIZE];
}HashTable;

//即链地址法就是将很多个链表的头节点存放在一个数组中 将冲突的数据不断添加在
//链表的后面 这里的头节点步存储数据 只存储一个头节点 


//函数

//1.初始化
void Init_HashTable(HashTable* pht);

//2.插入
bool Insert_HashTable(HashTable* pht, ELEMTYPE val);

//2.5哈希函数
int Hash(ELEMTYPE val);

//3.查找
HashNode* Find_Hash(HashTable* pht, ELEMTYPE val);

//4.删除
bool Del_Hash_val(HashTable* pht, ELEMTYPE val);

//5.打印
void Print_HashTable(HashTable* pht);

//6.销毁 销毁所有哈希桶中的元素
void Destroy_Hash(HashTable* pht);