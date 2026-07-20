#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <memory.h> 
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Link_Stack.h"


//函数实现

//初始化
void Init_LS(LSNode* pls)
{
	assert(pls != NULL);
	pls->next = NULL;
}

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


//text
int main()
{


	return 0;
}