#pragma once
/*
 单链表实现栈
 如果将单链表的头部设置为栈顶 时间复杂度 入栈O(1) 出栈O(1)
 如果将单链表的尾部设置为栈顶 时间复杂度 入栈O(n) 出栈O(n)
*/

//单链表实现栈
//为了统一接口 统一使用指针传参

typedef int ELEMTYPE;

typedef struct LSNode
{
	ELEMTYPE data;
	struct LSNode* next;
}LSNode;

//函数实现

//初始化
void Init_LS(LSNode* pls);

//入栈 (单链表的头插)
bool Push_LS(LSNode* pls, ELEMTYPE val);

//出栈
bool Pop_LS(LSNode* pls);

//获取栈顶元素值
ELEMTYPE Top_LS(LSNode* pls);

//获取当前栈的有效元素个数
int Size_LS(LSNode* pls);

//判空
bool Empty_LS(LSNode* pls);

//销毁
void Destroy_LS(LSNode* pls);

//打印
void Print_LS(LSNode* pls);