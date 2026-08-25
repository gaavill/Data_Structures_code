#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <memory.h> 
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Sort.h"
#include "Link_Queue.h"
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
void Insert_Sort_Plus(int arr[], int len)
{
	for (int i = 1; i < len; i++)
	{
		int tmp = arr[i];

		int left = 0;
		int right = i - 1;
		//二分查找找到插入位置
		while (left <= right)
		{
			int mid = (left + right) / 2;
			if (arr[mid] > tmp)
			{
				right = mid - 1;
			}
			else
			{
				left = mid + 1;
			}
		}
		//最终 left 会走到插入位置
		for (int j = i - 1; j >= left; j--)
		{
			arr[j + 1] = arr[j];
		}

		arr[left] = tmp;
	}
}

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

/************************************************************************************/




/************************************************************************************/
//基数排序
//一般不处理负数

//获取数组中元素最大值的位数
int Get_Max_Digit(int arr[], int len)
{
	//1.找到最大值
	int max = arr[0];
	for (int i = 1; i < len; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}

	//2.得到最大值的位数
	int fig = 0;
	if (max == 0)
	{
		return 1;
	}

	for (int i = max; i != 0; i /= 10)
	{
		fig++;
	}

	return fig;
}

//获取元素某一位的值
int Get_val_Digit(int val, int fig)
{
	for (int i = 0; i < fig; i++)
	{
		val /= 10;
	}
	return val % 10;
}

void Radix_Sort(int arr[], int len)
{
	//创建桶
	Link_Queue bucket[10];
	for (int i = 0; i < 10; i++)
	{
		Init_LQ(&bucket[i]);
	}

	//找出 arr 数组中元素的最大位数 
	int fig = Get_Max_Digit(arr, len);

	//将数据按位放入对应的队列桶中 
	for (int i = 0; i < fig; i++)
	{
		//按顺序将所有值按照其在当前位所对应的值 放入相应的桶中
		for (int j = 0; j < len; j++)
		{
			//获取元素在当前位上的值 放入相应的桶中
			int index = Get_val_Digit(arr[j], i);

			Push_LQ(&bucket[index], arr[j]);
		}

		//收集 出队 再按顺序将数据从桶中取出放回 arr
		int k = 0;
		for (int j = 0; j < 10; j++)
		{
			while (bucket[j].front != NULL)
			{
				arr[k++] = Front_LQ(&bucket[j]);
				Pop_LQ(&bucket[j]);
			}
		}
	}
}

//处理负数情况
//1.增加偏移量 排序时加上最小值偏移量 排序后再减去
//2.将待排序数组进行拆分成负数和正数两部分 负数按照绝对值排序 
//排序完成后进行逆序并恢复符号 最后将正负两部分进行拼接
//3.创建负数桶
void Radix_Sort2(int arr[], int len)
{
	//获取最小值 判断是否有负数
	int min = arr[0];
	for (int i = 1; i < len; i++)
	{
		if (arr[i] < min)
		{
			min = arr[i];
		}
	}

	//有负数 将所有值加上最小值的绝对值
	if (min < 0)
	{
		for (int i = 0; i < len; i++)
		{
			arr[i] += -min;
		}
	}

	//创建桶
	Link_Queue bucket[10];
	for (int i = 0; i < 10; i++)
	{
		Init_LQ(&bucket[i]);
	}

	//找出 arr 数组中元素的最大位数 
	int fig = Get_Max_Digit(arr, len);

	//将数据按位放入对应的队列桶中 
	for (int i = 0; i < fig; i++)
	{
		//按顺序将所有值按照其在当前位所对应的值 放入相应的桶中
		for (int j = 0; j < len; j++)
		{
			//获取元素在当前位上的值 放入相应的桶中
			int index = Get_val_Digit(arr[j], i);

			Push_LQ(&bucket[index], arr[j]);
		}

		//收集 出队 再按顺序将数据从桶中取出放回 arr
		int k = 0;
		for (int j = 0; j < 10; j++)
		{
			while (bucket[j].front != NULL)
			{
				arr[k++] = Front_LQ(&bucket[j]);
				Pop_LQ(&bucket[j]);
			}
		}
	}

	//有负数 再将所有值恢复成原值
	if (min < 0)
	{
		for (int i = 0; i < len; i++)
		{
			arr[i] -= -min;
		}
	}
}

//正负数拆分法
/************************************************************************************/


/************************************************************************************/
//并归排序
//合并函数 将已经有序的两个子区间进行合并
//通过两个指针移动 每次比较两个值 最终将剩余的元素再放进临时数组
//两个区间进行比较时 最终一定会有一个区间有剩余值 另一个区间为空
//有剩余值的区间不一定只剩一个值 也可能多个 但是在进行两个区间比
//较前 两个区间已经是有序的 所以两个区间比较结束后 直接将剩余区间
//的元素放进临时数组的末尾即可 
void Merge(int arr[], int left, int mid, int right)
{
	//创建临时数组 保存合并结果
	int* tmp = (int*)malloc(sizeof(int) * (right - left + 1));
	if (tmp == NULL)
	{
		return;
	}

	int L = left;//左区间起点
	int R = mid+1;//右区间起点
	int k = 0;//tmp数组下标

	//两个区间同时比较
	while (L <= mid && R <= right)
	{
		//如果左边小 就将其放入临时数组
		if (arr[L] <= arr[R])
		{
			tmp[k] = arr[L];
			k++;
			L++;
		}
		else
		{
			//如果右边小 就将其放入临时数组
			tmp[k] = arr[R];
			k++;
			R++;
		}
	}

	//左区间剩余元素放入 tmp 即将比较时较大的元素放入
	while (L <= mid)
	{
		tmp[k] = arr[L];
		k++;
		L++;
	}

	//右区间剩余元素放入 tmp
	while (R <= right)
	{
		tmp[k] = arr[R];
		k++;
		R++;
	}

	//将 tmp 数组中排好的结果放回原数组正在
	//处理的那个区间
	for (int i = 0; i < k; i++)
	{
		arr[left + i] = tmp[i];
	}

	free(tmp);
}

//排序函数
void Merge_Sort(int arr[], int left, int right)
{
	//归并排序 思想：分治 将一个大问题分为若干个互相独立的小问题 
	//将小问题解决之后 合并成大问题的结果

	//1.设置递归出口
	if (left >= right)
	{
		return;
	}

	//2.修改参数
	int mid = left + (right - left) / 2;//防止数据溢出

	//3.递归调用

	//左边继续分
	Merge_Sort(arr, left, mid);
	//右边继续分
	Merge_Sort(arr, mid + 1, right);

	//4.合并有序区间
	Merge(arr, left, mid, right);
}

/************************************************************************************/



/************************************************************************************/
//快速排序 
//1.递归版本
//partition单次划分函数 返回基准值的下标
int Partition(int arr[], int left, int right)
{
	//挖空法
	//1.将区间的第一个值作为基准值
	int tmp = arr[left];
	
	while (left < right)
	{
		//从右至左找比基准值小的值 放在左边空位(基准值的位置)
		while (left < right && arr[right] >= tmp)
		{
			right--;
		}
		arr[left] = arr[right];

		//从左至右找比基准值大的值 放在右边空位
		while (left < right && arr[left] <= tmp)
		{
			left++;
		}
		arr[right] = arr[left];
	}

	//将基准值放回
	arr[left] = tmp;
	//返回基准值下标
	return left;
}
//递归函数
void Quick_Sort(int arr[], int left, int right)
{
	//设置递归出口  left<right多个值  left==right 一个值  left>right 没有有效值
	if (left >= right)
	{
		return;
	}
	//调用三值取中法优化数据顺序
	//Three_Num_Get_Mid(arr, left, right);
	int par = Partition(arr, left, right);
	//以基准值所在下标par将原本的范围分成两部分
	//左边部分[left,par-1]
	//右边部分[par+1,right]
	Quick_Sort(arr, left, par - 1);
	Quick_Sort(arr, par + 1, right);

	/*
	写法2
	if(left<part-1)  Quick(arr,left,par-1);
	if(right>par+1) Quick(arr,par+1,right);
	*/
}

//快速排序非递归版本  时间复杂度 O(nlogn) 空间复杂度 O(n)
//思想：将递归时所创建的函数栈帧中的信息实现自主保存 方便维护 以防止递归时栈溢出

//设置左右区间结构体
struct Range
{
	int left;
	int right;
};
void Quick_Sort_2(int* arr, int len)
{
	//1.申请一个栈 并将初始状态下的 0 len-1
	std::stack<Range>st;
	st.push({ 0,len - 1 });
	//2.while循环 条件为栈不空 即还需要进行划分
	while (!st.empty())
	{
		//3.取出一组数据 传入Partition 函数进行划分排序
		Range cur = st.top();
		st.pop();

		int left = cur.left;
		int right = cur.right;

		//4.判断区间是否合法
		if (left < right)
		{
			//利用Partition函数找到基准值的下标
			int index = Partition(arr, left, right);

			//判断 Partition 后产生的左右子区间是否还值得继续排序 
			//即划分之后的左右区间有2个以上的元素个数 需要则将区间入栈
			
			//判断左区间
			if (left < index - 1)
			{
				//将新边界压入栈中
				st.push({ left,index - 1 });
			}
			//判断右区间
			if (right > index + 1)
			{
				st.push({ index + 1,right });
			}
		}
	}
}

//快速排序优化
//数据越有序速度越慢 数据越Partition函数划分的次数越多
//理想状态是每次数据按照基准值均分 这样划分的次数越少

//一个比较有序的序列
//方法一：数据量小的情况 转而使用插入排序
void Quick_Sort_3(int arr[], int len)
{
	if (len < 100)
	{
		Insert_Sort(arr, len);
		return;
	}
}
//方法二：三数取中法选择基准值 可以放在调用Partition函数前 
//即传入Partition函数的数据已经是通过三值取中法优化后的序列
//找到给定区间的左右区间 找到中间值 将三个数中的中位数作为基准值 
//交换到基准位置 即原left位置
//思路：先将三个值中的最大值 放在最右端 然后再判断前面两个值 
//将较大值 放在第一位
void Three_Num_Get_Mid(int* arr, int left, int right)
{
	//数学关系 ：arr[left] <= arr[mid] <= arr[right]
	int mid = left + (right - left) / 2;

	//保证 arr[left]<=arr[mid]
	if (arr[left] > arr[mid])
	{
		int tmp = arr[left];
		arr[left] = arr[mid];
		arr[mid] = tmp;
	}
	//此时left 和mid 较大值一定在中间
	//保证 arr[mid]<arr[right]
	if (arr[mid] > arr[right])
	{
		int tmp = arr[mid];
		arr[mid] = arr[right];
		arr[right] = tmp;
	}
	//此时 三个位置的最大值一定在 右端位置
	//再判断左 和 中间值  将两个中的较大值放在第一位
	if (arr[left] < arr[mid])
	{
		int tmp = arr[left];
		arr[left] = arr[mid];
		arr[mid] = tmp;
	}
	//经过交换 此时的left位置已经是三个值中的较大值
}
//方法三：随机数法 利用随机函数获取下标将两个的值进行交换




/************************************************************************************/




/************************************************************************************/
//堆排序
//默认升序 需要用到 大顶堆(根节点 >= 子节点)
//流程：构建大顶堆->将根与待排序列的最后一个元素交换->重新调整大顶堆
//用数组存储完全二叉树：
//root      left         right        parent
// i        i*2+1        i*2+2        (i-1)/2
//最后一个非叶子节点  (n/2)-1

//构建大顶堆流程：
//1.找到左右孩子的最大值->
//2.和根进行比较 如果比根大就交换->
//3.再向下调整 让父节点变为上一次被交换的孩子
//注意：构建大顶堆需要从最后一个非叶子节点开始 (n/2)-1
//原因：叶子节点默认符合大顶堆结构 需要从下往上逐层建立 
//AdjustDown函数处理的节点需要其子树已经满足堆结构
//说明：n 表示参与调整的节点范围   parent 表示开始调整的节点指针
void AdjustDown(int* arr, int n, int parent)
{
	//1.找到当前较大的孩子
	//先找到左孩子 右孩子就可以表示为arr[child+1]
	int child = parent * 2 + 1;
	while (child < n)
	{
		if (child + 1 < n && arr[child + 1] > arr[child])
		{
			child++;
		}

		//2.和根比较 如果比根大交换 根大则退出 已经是堆结构了
		if (arr[parent] >= arr[child])
		{
			break;
		}
		//父子交换
		int tmp = arr[child];
		arr[child] = arr[parent];
		arr[parent] = tmp;

		//3.继续调整被交换下去的节点
		parent = child;
		child = parent * 2 + 1;
	}
}

void Heap_Sort(int* arr, int len)
{
	//1.建立大顶堆 从最后一个非叶子节点开始向前建立 n/2-1
	for (int i = len / 2 - 1; i >= 0; i--)
	{
		AdjustDown(arr, len, i);
	}

	for (int end = len - 1; end > 0; end--)
	{
		//2.将根与待排序序列最后一个值交换
		//[0,end)为堆 [end,len]是已经排好的部分
		int tmp = arr[0];
		arr[0] = arr[end];
		arr[end] = tmp;

		//3.重新[0,end]为堆结构 修复被替换过的堆顶
		AdjustDown(arr, end, 0);
	}
}





//test
//int main()
//{
//	int arr[11] = { -18,97,58,91,72,-59,84,71,-95,71,128 };
//	//Merge_Sort(arr,0,10);
//	Heap_Sort(arr,11);
//	int index = BinarySearch(arr, 11, 71);
//	Print(arr, 11);
//	printf("%d\n",index);
//
//
//
//	return 0;
//}

