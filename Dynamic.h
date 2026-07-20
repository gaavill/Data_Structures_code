#pragma once
//数据类型声名
typedef int ELEMTYPE;

/*******************************************************************************************************/
//顺序表 

//静态顺序表(无法扩容)
#define MAXSIZE 20
typedef struct Static
{
	ELEMTYPE Data[MAXSIZE];//存放数据
	int CURSIZE;//当前元素个数
}Static;

//动态顺序表(可以进行扩容)
typedef struct Dynamic
{
	ELEMTYPE* data;//指向顺序表的指针
	int size;//当前有效元素个数
	int capacity;//当前容量
}Dynamic;

//函数实现

//初始化
void Init_Dynamic(Dynamic* pd);

//头删
bool Del_head(Dynamic* pd);

//尾删
bool Del_tail(Dynamic* pd);

//按位置pos删除
bool Del_pos(Dynamic* pd, int pos);

//按值删除 删除某个值第一次出现的位置
bool Del_val(Dynamic* pd, ELEMTYPE val);

//按值删除 删除某个值出现的所有位置
bool Del_val_All(Dynamic* pd, ELEMTYPE val);
bool Del_val_ALL_Plus(Dynamic* pd, ELEMTYPE val);

//头插
bool Insert_head(Dynamic* pd);

//尾插
void Insert_tail(Dynamic* pd, ELEMTYPE val);

//按位置插 pos代表数组下标 从0开始
bool Insert_pos(Dynamic* pd, int pos, ELEMTYPE val);

//查找指定元素第一次出现的位置
int Find_Dynamic(Dynamic* pd, ELEMTYPE val);

//查找指定元素出现的所有位置 需要调用着提供一个数组保存返回值
int Find_Dynamic_All(Dynamic* pd, ELEMTYPE val, int pos[], int maxsize);

//按照pos位置修改
bool Updata_pos(Dynamic* pd,int pos,ELEMTYPE val);

//判空
bool Empty_Dynamic(Dynamic* pd);

//扩容
bool Check_capacity(Dynamic* pd);

//打印
void Print_Dynamic(Dynamic* pd);
//检查容量

//销毁
void Stroy_Dynamic(Dynamic* pd);

//获取元素个数
int Getcount(Dynamic* pd);

/*******************************************************************************************************/