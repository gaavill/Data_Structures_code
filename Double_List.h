#pragma once
typedef int ELEMTYPE;

//双向链表：
//每一个节点既保存下一个节点的地址 也保存上一个节点的地址

//节点设计
typedef struct DNode
{
	ELEMTYPE data;//数据域
	struct DNode* next;//下一个节点指针域
	struct DNode* prior;//上一个节点指针域
}DNode;

//双向链表辅助节点直接借用有效节点的设计 不使用数据域 只使用指针域

//函数

//初始化
void Init_Double_Link(DNode* pdlist);

//头插
bool Insert_head_DNode(DNode* pdlist,ELEMTYPE val);

//尾插
bool Insert_tail_DNode(DNode* pdlist,ELEMTYPE val);

//按位置pos插入
bool Insert_pos_DNode(DNode* pdlist, int pos,ELEMTYPE val);

//头删
bool Del_head_DNode(DNode* pdlist);

//尾删
bool Del_tail_DNode(DNode* pdlist);

//按位置pos删除
bool Del_pos_DNode(DNode* pdlist, int pos);

//按传入值删除 删除第一次出现的位置
bool Del_val_DNode_first(DNode* pdlist, ELEMTYPE val);

//按照传入值删除 删除这个值出现的所有节点
bool Del_val_DNode_all(DNode* pdlist, ELEMTYPE val);

//查找
DNode* Find_DNode(DNode* pdlist, ELEMTYPE val);

//销毁1 无限头删
void Destroy1_DNode(DNode* pdlist);

//销毁2 双指针
void Destroy_DNode(DNode* pdlist);

//判空函数
bool Empty_DNode(DNode dlist);

//获取有效节点个数
int Get_Lenght_DNode(DNode* pdlist);

//打印函数
void Print_DNode(DNode* pdlist);