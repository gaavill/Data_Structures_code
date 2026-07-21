#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Link_Queue.h"





//函数

//初始化
void Init_LQ(Link_Queue* plq);

//入队 用尾插模拟
bool Push_LQ(Link_Queue* plq,ELEMTYPE val);

//出队 用头删模拟
bool Pop_LQ(Link_Queue* plq);

//获取队头元素值
ELEMTYPE Front_LQ(Link_Queue* plq);

//获取当前队列有效元素个数
int Size_LQ(Link_Queue* plq);

//判空
bool Empty_LQ(Link_Queue* plq);

//销毁
void Destroy_LQ(Link_Queue* plq);

//打印
void Print_LQ(Link_Queue* plq);