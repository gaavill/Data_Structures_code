#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <memory.h> 
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Sort.h"
#include <stack>

/**********************************************************************/
//打印函数
void Print(int arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}
/**********************************************************************/



/**********************************************************************/
//1.直接插入排序   时间复杂度O(n^2)    空间复杂度 O(1)
void Insert_Sort(int arr[], int len)
{
	assert(arr);

	for (int i = 1; i < len; i++)//控制执行次数
	{
		//先保存需要插入的值 防止数据移动时被覆盖
		int tmp = arr[i];
		//得到插入数据的前一位 即已经排好序的队列的最后一位
		int j = i-1;
		
		for (; j >= 0 && arr[j] > tmp; j--)//控制对已经排序好的序列从右至左的遍历 给待插入数据留出空位
		{
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = tmp;
	}
}

//优化：将待插入值插入到已经排序好的队列中 则可以用二分的方法来找到待排序值的位置
/**********************************************************************/


/**********************************************************************/
//希尔排序  时间复杂度O(n^1.5)  空间复杂度O(1)
void Shell_Sort(int arr[], int len)
{
	//构建一个缩小增量数组
	int gap[] = { 5,3,1 };

	int len_gap = sizeof(gap) / sizeof(gap[0]);

	//将数组按照缩小增量数组进行分组 先内部进行插入排序
	//一层循环控制gap 即要进行几次分组
	for (int k = 0; k < len_gap; k++)
	{
		//当前增量
		int d = gap[k];//5 3

		//对每一组进行插入排序
		for (int i = d; i < len; i++)//5 3 
		{
			int tmp = arr[i];
			int j;
			for (j = i - d; j >= 0 && arr[j] > tmp; j -= d)
			{ 
				arr[j + d] = arr[j];
			}
			arr[j + d] = tmp;
		}
	}
}

void Shell_Sort_Copy(int* arr, int len)
{
	for (int n = len / 2; n > 0; n /= 2)
	{
		for (int i = n; i < len; i++)
		{
			int tmp = arr[i];
			int j;
			for (j = i - n; j >= 0 && arr[j] > tmp; j -= n)
			{
				arr[j + n] = arr[j];
			}
			arr[j + n] = tmp;
		}
	}
}

/**********************************************************************/



/**********************************************************************/
//选择排序  时间复杂度 O(n^2)  空间复杂度 O(1)
void Select_Sort(int arr[], int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		//保存当前这一趟的第一个值的下标
		int min = i;
		for (int j = i + 1; j < len; j++)
		{
			if (arr[min] > arr[j])
			{
				min = j;
			}
		}
		//判断当前最小值的下标是否为排序前的第一个值 是否真的需要交换
		if (min != i)
		{
			int tmp = arr[i];
			arr[i] = arr[min];
			arr[min] = tmp;
		}
	}
}

/**********************************************************************/



/**********************************************************************/
//冒泡排序
void Bubble_Sort(int arr[], int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		//j 代表的是参与比较的元素下标 从 0 开始到 len-2 结束 左右比较
		for (int j = 0; j < len - 1 - i;j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}

//优化
//思路：如果比较一趟之后发现已经有序 则退出
//实现方法：添加一个标签 如果标签没有发生变化 则证明已经有序 直接退出
void Bubble_Sort_Plus(int arr[], int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		//添加标签
		int flag = 0;
		for (int j = 0; j < len - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;

				//如果发生交换 flag变化 则证明数据还是无序
				flag = 1;
			}
		}

		if (flag == 0)
		{
			break;
		}
	}
}


//二分查找 时间复杂度 O(log n)
int BinarySearch(int arr[], int len, int target)
{
	//1.定义左右边界和中间值
	int left = 0;
	int right = len - 1;
	int mid;

	//2.查找过程
	while (left <= right)
	{
		//更新中间值
		mid = (left + right) / 2;

		if (arr[mid] > target)
		{
			//中间值大于查找值 更新右边界
			right = mid - 1;
		}
		else if (arr[mid] < target)
		{
			//中间值小于查找值 更新左边界
			left = mid + 1;
		}
		else
		{
			//此时即为 arr[mid] == target
			return mid;
		}
	}
	//循环结束 未找到 返回-1
	return -1;
}

//test
int main()
{
	int arr[10] = { 2,5,1,3,8,9,0,4,7,6 };
	Bubble_Sort_Plus(arr, 10);
	int index = BinarySearch(arr, 10, 7);
	Print(arr, 10);
	printf("%d\n", arr[index]);



	return 0;
}

