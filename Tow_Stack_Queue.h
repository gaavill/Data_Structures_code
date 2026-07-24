#pragma once

/*
1.两个栈如何模拟出一个队列
	核心：数据进出规则
	假设两个栈为 S1 S2
	入队：向S1中插入
	出队：先查看S2中是否有数据 有数据则出一个
		  没有则先从S1出栈 再入栈进S2 再从S2出栈

2.两个队列如何模拟出一个栈
	假设两个队列为Q1 Q2
	插入：向Q1中插入
	删除：先检查Q1中有没有数据 如果有则将除最后一个元素(队尾)外所有元素
	      出队 进入Q2中 此时将Q1中剩下的元素出队
		  如果Q1中没有数据 则说明数据都在Q2 则将Q2除最后一个元素外的
		  所有元素存进Q1中 再将Q2最后一个元素出队
*/


#if 0



//1.两个栈模拟一个队列
typedef int ELEMTYPE;

#include <stack>
typedef struct TowStackToQueue
{
	std::stack<ELEMTYPE>S1;
	std::stack<ELEMTYPE>S2;
}TowStackToQueue;


//1.入队
bool Push_TSTQ(TowStackToQueue* ptstq, ELEMTYPE val);

//2.出队
bool Pop_TSTQ(TowStackToQueue* ptstq);

//3.获取队头元素
ELEMTYPE Front_TSTQ(TowStackToQueue* ptstq);
#endif




//2.两个队列模拟一个栈
typedef int ELEMTYPE;
#include<queue>
typedef struct TowQueueToStack
{
	std::queue<ELEMTYPE>Q1;
	std::queue<ELEMTYPE>Q2;
}TowQueueToStack;

//1.入栈 向Q1中插入数据
bool Push_TQTS(TowQueueToStack*ptqts,ELEMTYPE val);

//2.出栈 通过交换两个栈中的数据保留要出队的数据
bool Pop_TQTS(TowQueueToStack* ptqts);

//3.获取栈顶元素
ELEMTYPE Front_TQTS(TowQueueToStack* ptqts);