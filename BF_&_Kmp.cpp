#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "BF_&_Kmp.h"

//说明：这里的BF KMP只针对字符串匹配 默认参与匹配的字符串长度 >=2 
//所以对边界问题不做特殊处理
//实现的BF KMP函数查找成功会返回在主串中的位置下标

//暴力枚举
int BF_Search(const char* str, const char* sub, int index)
{
	if (str == NULL || sub == NULL)
	{
		return -1;
	}
	//主串开始位置
	int i = index;
	//子串开始位置
	int j = 0;

	int str_len = (int)strlen(str);
	int sub_len = (int)strlen(sub);

	while (i < str_len && j < sub_len)
	{
		//如果字符相等 则同时向后走
		if (str[i] == sub[j])
		{
			i++;
			j++;
		}
		else
		{
			//如果字符不相等 则让子串回到开始位置 
			//主串回到开始匹配的下一个字符位置 重新开始比较
			i = i - j + 1;
			j = 0;
		}
	}
	//只有子串走出了 才会匹配成功
	if (j == sub_len)
	{
		return i-j;
	}

	return -1;
}

/********************************************************************************************************/

//KMP
//求next数组函数
int* Get_Next(const char* sub)
{
	int len_sub = (int)strlen(sub);
	if (sub == NULL||len_sub == 0)
	{
		return NULL;
	}

	//申请一个等长数组
	int* next = (int*)malloc(len_sub * sizeof(int));
	if (next == NULL)
	{
		return NULL;
	}

	//直接将前两个格子赋值为-1 0
	next[0] = -1;
	if (len_sub > 1)
	{
		next[1] = 0;
	}
	//指向当前已知其回退位置的最新字符的指针
	int j = 1;
	//保存当前字符回退位置(同时也是前面字符的最长公共前后缀值)
	int tmp = 0;

	while (j + 1 <= len_sub -1)
	{
		//当当前字符与回退位置字符相等 或者当前字符的回退位置为-1时 就给下一个next值进行赋值
		if (sub[j] == sub[tmp]||tmp == -1)
		{
			j++;//指向下一个位置
			tmp++;//当前字符回退位置也是最长公共前后缀 +1 得到下一个字符的回退位置
			next[j] = tmp;
		}
		else
		{
			//当当前回退位置的字符和当前字符不相等 就继续比较回退位置的回退位置的字符和当前j的字符
			tmp = next[tmp];
		}
	}
	return next;
}

//next数组的优化：-> nextval数组
//思想：如果回退1次和回退2次字符都是相同的 那么回退1次失败 则回退两次也一定会失败
//通过next数组得到nextval数组->
//得到next数组 申请一个nextval数组和next数组等长
//将第一个字符对应的nextval数组的值赋值为-1
//通过循环对后续字符依次赋值
//如果当前字符和其next数组保存的回退位置不相同 则next数组中保存的回退位置字符有可能成功匹配
//将其直接赋值给nextval数组
//如果当前字符和其next数组保存的回退位置相同 则next数组中保存的回退位置字符一定匹配不成功
//将其回退位置字符的最优解(当前回退位置在nextval数组中的保存的值)赋值给nextval下一个位置

//  A A A A A A A A A B
// -1 0 1 2 3 4 5 6 7 8
// -1-1-1-1-1-1-1-1-1 8

//求nextval数组函数
int* Get_Nextval(const char* sub)
{
	int len_sub = (int)strlen(sub);
	if (sub == NULL || len_sub == 0)
	{
		return NULL;
	}

	//申请一个等长数组
	int* next = (int*)malloc(len_sub * sizeof(int));
	if (next == NULL)
	{
		return NULL;
	}

	//直接将前两个格子赋值为-1 0
	next[0] = -1;
	if (len_sub > 1)
	{
		next[1] = 0;
	}
	//指向当前已知其回退位置的最新字符的指针
	int j = 1;
	//保存当前字符回退位置(同时也是前面字符的最长公共前后缀值)
	int tmp = 0;

	while (j + 1 <= len_sub - 1)
	{
		//当当前字符与回退位置字符相等 或者当前字符的回退位置为-1时 就给下一个next值进行赋值
		if (sub[j] == sub[tmp] || tmp == -1)
		{
			j++;//指向下一个位置
			tmp++;//当前字符回退位置也是最长公共前后缀 +1 得到下一个字符的回退位置
			next[j] = tmp;
		}
		else
		{
			//当当前回退位置的字符和当前字符不相等 就继续比较回退位置的回退位置的字符和当前j的字符
			tmp = next[tmp];
		}
	}

	//申请一个等长数组
	int* nextval = (int*)malloc(len_sub * sizeof(int));
	if (nextval == NULL)
	{
		return NULL;
	}
	nextval[0] = -1;

	for (int j = 1; j < len_sub; j++)
	{
		if (sub[j] != sub[next[j]])
		{
			nextval[j] = next[j];
		}
		else
		{
			nextval[j] = nextval[next[j]];
		}
	}

	free(next);
	return nextval;
}

int KMP_Search(const char* str, const char* sub, int index)
{
	if (str == NULL || sub == NULL)
	{
		return -1;
	}
	//主串开始位置
	int i = index;
	//子串开始位置
	int j = 0;

	int str_len = (int)strlen(str);
	int sub_len = (int)strlen(sub);
	//获得next 数组
	int* next = Get_Nextval(sub);

	while (i < str_len && j < sub_len)
	{
		//如果字符相等 或者 j== -1 则同时向后走
		if (str[i] == sub[j]||j == -1)
		{
			i++;
			j++;
		}
		else
		{
			//如果字符不相等 则让子串回到开始位置 
			//调用Get_next函数
			j = next[j];
		}
	}

	free(next);
	//只有子串走出了 才会匹配成功
	if (j == sub_len)
	{
		return i - j;
	}

	return -1;
}


int main()
{
	char str[] = "abcdef";

	int k = KMP_Search(str, "def",0);

	printf("%d\n", k);
	
	return 0;
}