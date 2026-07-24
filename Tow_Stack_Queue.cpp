#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <memory.h> 
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Tow_Stack_Queue.h"
#include <vld.h>


#if 0
//1.入队
bool Push_TSTQ(TowStackToQueue* ptstq, ELEMTYPE val)
{
	assert(ptstq != NULL);
	ptstq->S1.push(val);
	return true;
}

//2.出队
bool Pop_TSTQ(TowStackToQueue* ptstq)
{
	assert(ptstq);
	//先查找S2中是否有元素
	if (ptstq->S1.empty() && ptstq->S2.empty())
	{
		return false;
	}

	if (!ptstq->S2.empty())
	{
		ptstq->S2.pop();
	}
	else
	{
		//如果S2为空 则将S1中的元素依次复制到S2
		while (!ptstq->S1.empty())
		{
			ptstq->S2.push(ptstq->S1.top());
			ptstq->S1.pop();
		}
		//出队S2中数据
		ptstq->S2.pop();
	}

	return true;
}

//3.获取队头元素
ELEMTYPE Front_TSTQ(TowStackToQueue* ptstq)
{
	assert(ptstq != NULL);
	if (ptstq->S1.empty() && ptstq->S2.empty())
	{
		exit(EXIT_SUCCESS);
	}

	if (!ptstq->S2.empty())
	{
		return ptstq->S2.top();
	}

	while (!ptstq->S1.empty())
	{
		ptstq->S2.push(ptstq->S1.top());
		ptstq->S1.pop();
	}
	return ptstq->S2.top();
}

//test
//int main()
//{
//	TowStackToQueue s;
//	Push_TSTQ(&s, 91);
//	Push_TSTQ(&s, 78);
//	Push_TSTQ(&s, 13);
//
//	Pop_TSTQ(&s);
//	Pop_TSTQ(&s);
//
//	
//	return 0;
//}

#endif // 0


//1.入栈 向Q1中插入数据
bool Push_TQTS(TowQueueToStack* ptqts, ELEMTYPE val)
{
	assert(ptqts != NULL);
	ptqts->Q1.push(val);
	return true;
}

//2.出栈 通过交换两个栈中的数据保留要出队的数据
bool Pop_TQTS(TowQueueToStack* ptqts)
{
	assert(ptqts != NULL);
	if (ptqts->Q1.empty() && ptqts->Q2.empty())
	{
		return false;
	}
	//检查Q1是否为空 不为空则将Q1中的数据除最后一位放入Q2
	if (!ptqts->Q1.empty())
	{
		while (ptqts->Q1.size() > 1)
		{
			ptqts->Q2.push(ptqts->Q1.front());
			ptqts->Q1.pop();
		}
		ptqts->Q1.pop();
	}
	else
	{
		//如果Q1为空 则证明数据都在Q2 则将Q2中除最后一个元素外都存入Q1
		while (ptqts->Q2.size() > 1)
		{
			ptqts->Q1.push(ptqts->Q2.front());
			ptqts->Q2.pop();
		}
		ptqts->Q2.pop();
	}

	return true;
}

//3.获取栈顶元素
ELEMTYPE Front_TQTS(TowQueueToStack* ptqts)
{
	assert(ptqts != NULL);
	if (ptqts->Q1.empty() && ptqts->Q2.empty())
	{
		exit(EXIT_FAILURE);
	}
	ELEMTYPE front;
	//检查Q1是否为空 不为空则将Q1中的数据除最后一位放入Q2
	if (!ptqts->Q1.empty())
	{
		while (ptqts->Q1.size() > 1)
		{
			ptqts->Q2.push(ptqts->Q1.front());
			ptqts->Q1.pop();
		}
		front = ptqts->Q1.front();

		ptqts->Q2.push(ptqts->Q1.front());
		ptqts->Q1.pop();
	}
	else
	{
		//如果Q1为空 则证明数据都在Q2 则将Q2中除最后一个元素外都存入Q1
		while (ptqts->Q2.size() > 1)
		{
			ptqts->Q1.push(ptqts->Q2.front());
			ptqts->Q2.pop();
		}
		front = ptqts->Q2.front();

		ptqts->Q1.push(ptqts->Q2.front());
		ptqts->Q2.pop();
	}

	return front;
}