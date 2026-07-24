#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <memory.h> 
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Dynamic.h"
#include <vld.h>

//typedef struct Dynamic
//{
//	ELEMTYPE* data;//指向顺序表的指针
//	int size;//当前有效元素个数
//	int capacity;//当前容量
//}Dynamic;

//说明 顺序表的数组下标从0开始 但是元素个数size从1开始

//初始化
void Init_Dynamic(Dynamic* pd)
{
	assert(pd != NULL);
	pd->data = NULL;
	pd->size = 0;
	pd->capacity = 0;
}

//头插
bool Insert_head(Dynamic* pd,ELEMTYPE val)
{
	assert(pd != NULL);
	Check_capacity(pd);
	//将待插入元素放在第一位 后面所有元素向后移动一位
	//为了避免移动时覆盖旧数据 从后往前挪动数据
	for (int i = pd->size; i > 0; i--)
	{
		pd->data[i] = pd->data[i-1];
	}
	pd->data[0] = val;
	pd->size++;
	//也可以使用memmove函数
	//memmove(pd->data+1,pd->data,sizeof(ELEMTYPE)*pd->size)
	return true;
}

//销毁
void Stroy_Dynamic(Dynamic* pd)
{
	assert(pd != NULL);
	free(pd->data);
	pd->data = NULL;
	pd->size = 0;
	pd->capacity = 0;
}

//打印
void Print_Dynamic(Dynamic* pd)
{
	assert(pd != NULL);
	for (int i = 0; i < pd->size; i++)
	{
		printf("%d ", pd->data[i]);
	}
	printf("\n");
}

//尾插
void Insert_tail(Dynamic* pd,ELEMTYPE val)
{
	assert(pd != NULL);
	//判断是否超出容量
	Check_capacity(pd);
	//让指针指向size+1位
	pd->data[pd->size] = val;
	pd->size++;
}

//扩容
bool Check_capacity(Dynamic* pd)
{
	assert(pd != NULL);
	//判断是否需要扩容
	if (pd->size >= pd->capacity)
	{
		//设置capacity 三目运算
		int new_capacity = (pd->capacity == 0) ? 4 : pd->capacity * 2;
		ELEMTYPE* pnew = (ELEMTYPE*)realloc(pd->data, sizeof(ELEMTYPE) * new_capacity);
		if (pnew == NULL)
		{
			return false;
		}
		pd->data = pnew;
		pd->capacity = new_capacity;
	}
	return true;
}

//尾删
bool Del_tail(Dynamic* pd)
{
	//size--即可
	assert(pd != NULL);
	if (Empty_Dynamic(pd))
	{
		return false;
	}
	pd->size--;
	return true;
}

//判空(表中是否有元素)
bool Empty_Dynamic(Dynamic* pd)
{
	assert(pd != NULL);
	if (pd->size == 0)
	{
		return true;
	}
	return false;
}

//按位置pos删除 pos代表数组下标 从0开始
bool Del_pos(Dynamic* pd, int pos)
{
	//将数组下标为pos位置的数值删除 将后面的元素整体往前挪动
	assert(pd != NULL);
	if (Empty_Dynamic(pd)||pos < 0||pos >= pd->size)
	{
		return false;
	}
	for (int i = pos; i < pd->size-1; i++)
	{
		pd->data[i] = pd->data[i+1];
	}
	pd->size--;
	return true;
}

//按位置插 pos代表数组下标 从0开始
bool Insert_pos(Dynamic* pd, int pos,ELEMTYPE val)
{
	//1.先找到插入位置 将从pos位置开始后面的元素整体向后挪动 
	//2.将pos位置的值设为插入值
	assert(pd != NULL);
	if (pos < 0 || pos > pd->size)
	{
		return false;
	}
	Check_capacity(pd);
	for (int i = pd->size; i > pos; i--)
		//整体向后挪动 为了避免元素被覆盖 从后往前挪动
	{
		pd->data[i] = pd->data[i - 1];
	}
	pd->data[pos] = val;
	pd->size++;
	return true;
}

//按照pos位置修改
bool Update_pos(Dynamic* pd,int pos, ELEMTYPE val)
{
	//将pos位置的数值进行修改
	assert(pd != NULL);
	if (Empty_Dynamic(pd) || pos < 0 || pos >= pd->size)
	{
		return false;
	}
	pd->data[pos] = val;
	return true;
}

//查找指定元素第一次出现的位置 数组下标
int Find_Dynamic(Dynamic* pd, ELEMTYPE val)
{
	//遍历数组 找到等于val的位置 将下标进行返回
	assert(pd != NULL);
	for (int i = 0; i < pd->size; i++)
	{
		if (pd->data[i] == val)
		{
			return i;
		}
	}
	return -1;
}

//查找指定元素出现的所有位置 需要调用着提供一个数组保存返回值
int Find_Dynamic_All(Dynamic* pd, ELEMTYPE val, int pos[], int maxsize)
{
	assert(pd != NULL);
	int count = 0;//记录满足要求pos的个数
	for (int i = 0; i < pd->size; i++)
	{
		if (pd->data[i] == val)
		{
			if (count == maxsize)
			{
				break;
			}
			pos[count] = i;
			count++;
		}
	}
	return count;
}

//按值删除 删除某个值第一次出现的位置
bool Del_val(Dynamic* pd, ELEMTYPE val)
{
	assert(pd != NULL);
	if (Empty_Dynamic(pd))
	{
		return false;
	}
	//1.找到val第一次出现的位置
	//2.将待删除元素以后的所有元素整体向前挪动一位
	//3.size--
	int pos = Find_Dynamic(pd, val);
	if (pos == -1)
	{
		return false;
	}
	return Del_pos(pd, pos);
}

//按值删除 删除某个值出现的所有位置
bool Del_val_All(Dynamic* pd, ELEMTYPE val)
{
	assert(pd != NULL);
	if (Empty_Dynamic(pd))
	{
		return false;
	}
	for (int i = pd->size-1; i >= 0; i--)
	{
		if (pd->data[i] == val)
		{
			Del_pos(pd, i);
		} 
	}
	return true;
}
bool Del_val_ALL_Plus(Dynamic* pd, ELEMTYPE val)
{
	assert(pd != NULL);
	if (Empty_Dynamic(pd))
	{
		return false;
	}
	int slow = 0;
	for (int fast = 0; fast < pd->size; fast++)
	{
		if (pd->data[fast] != val)
		{
			pd->data[slow] = pd->data[fast];
			slow++;
		}
	}
	pd->size = slow;
	return true;
}

//头删
bool Del_head(Dynamic* pd)
{
	//将所有元素整体向前挪动一位 size--
	assert(pd != NULL);
	if (Empty_Dynamic(pd))
	{
		return false;
	}
	for (int i = 0; i < pd->size - 1; i++)
	{
		pd->data[i] = pd->data[i + 1];
	}
	pd->size--;
	return true;
}

//获取元素个数
int Getcount(Dynamic* pd)
{
	assert(pd != NULL);
	return pd->size;
}

/*************************************************************************************************************/
//Test
//int main()
//{
//	Dynamic s;
//
//	Init_Dynamic(&s);
//
//	Insert_tail(&s,9);
//	Insert_tail(&s, 9);
//	//9 10
//	Print_Dynamic(&s);
//	Insert_head(&s, 1);
//	Insert_head(&s, 1);
//	//1 2 9 10
//	Print_Dynamic(&s);
//	Insert_pos(&s, 3, 9);
//	Insert_pos(&s, 4, 9);
//	//1 2 3 4 9 10
//	Print_Dynamic(&s);
//	//Del_head(&s);
//	//Print_Dynamic(&s);
//	//Del_tail(&s);
//	//Print_Dynamic(&s);
//
//	//Del_pos(&s, 2);
//	//Print_Dynamic(&s);
//	//Del_val(&s, 9);
//	//Print_Dynamic(&s);
//	
//	Del_val_All(&s, 9);
//	Print_Dynamic(&s);
//
//	return 0;
//}

