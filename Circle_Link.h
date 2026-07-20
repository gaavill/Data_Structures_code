#pragma once

//带头节点单循环链表 
//尾节点指向头节点
//节点结构设计和单链表一样

typedef int ELEMTYPE;

typedef struct CNode
{
	ELEMTYPE data;
	struct CNode* next;
}CNode;

//辅助节点借助有效节点的设计

//函数

//1.初始化
void Init_CLink(CNode* plist);

//2.头插
bool Insert_head_CLink(CNode* plist, ELEMTYPE val);

//3.尾插
bool Insert_tail_CLink(CNode* plist, ELEMTYPE val);

//4.按下标pos插入
bool Insert_pos_CLink(CNode* plist, int pos, ELEMTYPE val);

//5.头删
bool Del_head_CLink(CNode* plist);

//6.尾删
bool Del_tail_CLink(CNode* plist);

//7.按照下标删
bool Del_pos_CLink(CNode* plist, int pos);

//8.按照传入值删 删除第一次出现的位置
bool Del_val_first(CNode* plist, ELEMTYPE val);

//9.按照传入值删 删除出现的所有位置
bool Del_val_all(CNode* plist, ELEMTYPE val);

//10.查找 找到传入值出现的第一个位置 并返回
CNode* Find_first_CLink(CNode* plist, ELEMTYPE val);

//11.销毁1 无限头删
void Destory_CLink1(CNode* plist);

//12.销毁2 双指针
void Destory_CLink2(CNode* plist);

//13.判空
bool Empty_CLink(CNode* plist);

//14.获取有效节点个数
int Get_count_CLink(CNode* plist);

//15.打印
void Print_CLink(CNode* plist);

/*************************************************************************************************/