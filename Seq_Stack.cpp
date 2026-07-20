#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <memory.h> 
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Seq_Stack.h"
#include <stack>


//初始化
void Init_SS(Seq_Stack* pss)
{
	assert(pss != NULL);
	pss->arr = (ELEMTYPE*)malloc(INITSIZE * sizeof(ELEMTYPE));
	if (pss->arr == NULL)
	{
		return;
	}
	pss->length = 0;
	pss->capacity = INITSIZE;
}

//入栈(尾插)
bool Push_SS(Seq_Stack* pss,ELEMTYPE val)
{
	assert(pss != NULL);
	//判满并扩容 判满操作包含在了扩容函数中
	if (Full_SS(*pss))
	{
		if (!Increase_SS(pss))
		{
			return false;
		}
	}
	pss->arr[pss->length] = val;
	pss->length++;
	return true;
}

//出栈(尾删)
bool Pop_SS(Seq_Stack* pss)
{
	assert(pss != NULL);
	if (Empty_SS(*pss))
	{
		return false;
	}
	pss->length--;
	return true;
}

//获取栈顶元素 (获取尾节点)
ELEMTYPE Top_SS(Seq_Stack ss)
{
	assert(!Empty_SS(ss));
	return ss.arr[ss.length - 1];
}

//获取当前栈的有效元素个数
int Size_SS(Seq_Stack ss)
{
	return ss.length;
}

//判空
bool Empty_SS(Seq_Stack ss)
{
	return ss.length == 0;
}

//判满
bool Full_SS(Seq_Stack ss)
{
	return ss.length == ss.capacity;
}

//扩容
bool Increase_SS(Seq_Stack* pss)
{
	assert(pss != NULL);
	//判满
	if (!Full_SS(*pss))
	{
		return true;
	}
	//更新容量
	int new_capacity = pss->capacity * 2;
	//realloc扩容
	ELEMTYPE* tmp = (ELEMTYPE*)realloc(pss->arr, new_capacity * sizeof(ELEMTYPE));
	if (tmp == NULL)
	{
		return false;
	}
	pss->arr = tmp;
	//更新容量
	pss->capacity = new_capacity;
	return true;
}

//清空栈中元素
void Clear_SS(Seq_Stack* pss)
{
	assert(pss != NULL);
	pss->length = 0;
}

//销毁
void Destroy_SS(Seq_Stack* pss)
{
	assert(pss != NULL);
	free(pss->arr);
	pss->arr = NULL;
	pss->length = 0;
	pss->capacity = 0;
}

//打印 按照出栈顺序打印
void Print_SS(Seq_Stack ss)
{
	for (int i = ss.length-1; i >= 0; i--)
	{
		printf("%d ", ss.arr[i]);
	}
	printf("\n");
}


//text
//int main()
//{
//	Seq_Stack stack;
//	Init_SS(&stack);
//	
//	for (int i = 0; i < 15; i++)
//	{
//		Push_SS(&stack, i);
//	}
//
//	Print_SS(stack);
//
//	printf("%d\n", Top_SS(stack));
//	printf("%d\n", Size_SS(stack));
//	Clear_SS(&stack);
//	Print_SS(stack);
//	printf("%d\n", Size_SS(stack));
//	printf("%d\n", stack.capacity);
//	Destroy_SS(&stack);
//	
//
//	return 0;
//}