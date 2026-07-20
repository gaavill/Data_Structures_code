#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <memory.h> 
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"
#include <stack>
//单链表的相关问题
//注意：节点插入修改指针域时先修改插入节点 再修改原节点 最后修改前驱节点

//1.逆置 借助头节点
void Reversal_head(Node* plist)
{
	assert(plist != NULL);
	//无限头插
	//相当于创建一个新链表 将原来链表中的元素一个一个进行头插
	//申请一个指针用来遍历整个链表
	Node* cur = plist->next;
	plist->next = NULL;
	while (cur != NULL)
	{
		//申请一个新的指针用来保存cur的下一个节点
		Node* next = cur->next;
		//进行头插
		cur->next = plist->next;
		plist->next = cur;
		//更新待插入节点
		cur = next;
	}
}

//不借助头节点 三指针
void Reversal(Node* plist)
{
	assert(plist != NULL);
	if (Empty_Node(plist))
	{
		return;
	}
	//三指针 prev cur next
	Node* prev = NULL;
	Node* cur = plist->next;
	Node* next = NULL;
	while (cur != NULL)
	{
		//先保存下一个节点
		next = cur->next;
		//修改节点的指向
		cur->next = prev;
		//更新节点
		prev = cur;
		cur = next;
	}
	//单独处理头节点
	plist->next = prev;//此时prev保存的是最后一个节点信息
}

//2.判断两个单链表是否存在交点 如果存在 找到相交的第一个交点
//核心是判断两个单链表的节点是否相同 也就是判断两个指针是否相等

//双重遍历暴力求解         
Node* Get_IntersectionNode1(Node* plist1, Node* plist2)
{
	assert(plist1 != NULL && plist2 != NULL);
	Node* curA = plist1->next;
	//双重遍历两个链表 找到相交节点
	while (curA != NULL)
	{
		Node* curB = plist2->next;
		while (curB != NULL)
		{
			if (curA == curB)
			{
				return curA;
			}
			curB = curB->next;
		}
		curA = curA->next;
	}
	return curA;
}

//双指针交换链表法
//申请两个指针 让两个指针走相同的路程之后 一定会在交点处相遇 就会得到交点
Node* Get_IntersectionNode2(Node* plist1, Node* plist2)
{
	assert(plist1 != NULL && plist2 != NULL);
	Node* curA = plist1->next;
	Node* curB = plist2->next;
	while (curA != curB)
	{
		//if (curA == NULL)
		//{
		//	curA = plist2->next;
		//}
		//else
		//{
		//	curA = curA->next;
		//}

		//if (curB == NULL)
		//{
		//	curB = plist1->next;
		//}
		//else
		//{
		//	curB = curB->next;
		//}

		curA = (curA == NULL) ? plist2->next : curA->next;
		curB = (curB == NULL) ? plist1->next : curB->next;
	}
	return curA;
}

//长度差法
//先消除两个链表相交前的长度差 然后让两个链表同时向后走 直到走到相交节点
Node* Get_IntersectionNode3(Node* plist1, Node* plist2)
{
	assert(plist1 != NULL && plist2 != NULL);
	Node* fast = plist1;
	Node* slow = plist2;
	//先让两个链表走到各自的尾节点 判断是否相交 若尾节点不相等 
	// 则证明两个链表没有交点
	for (; fast->next != NULL; fast = fast->next);
	for (; slow->next != NULL; slow = slow->next);
	if (fast != slow)
	{
		return NULL;
	}
	//长链表指针先走两个链表的差值步 使两个链表距离交点距离相等
	int len1 = Get_Lenght(plist1);
	int len2 = Get_Lenght(plist2);
	
	fast = len1 >= len2 ? plist1 : plist2;
	slow = len1 >= len2 ? plist2 : plist1;

	for (int i = 0; i < abs(len1 - len2); i++)//abs 取绝对值
	{
		fast = fast->next;
	}

	while (fast != slow)
	{
		fast = fast->next;
		slow = slow->next;
	}
	return slow;
}



//3.删除任意一个节点 (要求时间复杂度为O(1)) 给的这个节点的位置不能是尾节点
//普通删除：需要找到前驱节点 因此时间复杂度是 O(n)
//已知待删节点且不是尾节点：复制后继节点数据 再删除后继节点 时间复杂度是 O(1)
void Del_Node(Node* node)
{
	assert(node != NULL);
	assert(node->next != NULL);
	//将Node下一个节点的数据赋值到Node节点
	Node* del = node->next;
	node->data = del->data;
	//修改node指针域
	node->next = del->next;
	//释放del
	free(del);
}

//4.判断一个单链表是否存在环 如果存在 找到入环点
bool Is_circle_List(Node* plist)
{
	assert(plist != NULL);
	//快慢指针 判断是否有环
	Node* slow = plist->next;
	Node* fast = plist->next;
	while (fast != NULL && fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
		{
			return true;
		}
	}
	return false;
}

//如果存在 找到入环点
//设起始位置到入环点距离为X 入环点到相遇点距离为Y 相遇点到入环点距离为Z
//根据数学关系有 2(X+Y)=X+n(Z+Y)+Y  化简得到 X=(n-1)(X+Z)+Z 
//即当链表有环时 让一个指针从起点出发 另一个指针从相遇点出发 相同速度前进
//最终会在入环点相遇
Node* Get_MeetNode(Node* plist)
{
	assert(plist != NULL);
	//先判断是否有环
	//快慢指针
	Node* slow = plist;
	Node* fast = plist;
	while (fast != NULL && fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
		{
			break;
		}
	}
	//无环情况
	if (fast == NULL || fast->next == NULL)
	{
		return NULL;
	}
	//寻找入环点
	Node* meet = slow;
	Node* start = plist;
	while (meet != start)
	{
		meet = meet->next;
		start = start->next;
	}
	return start;
}

//5.确定一个单链表是否回文
//1.数组法：将链表中的数据存入一个数组中 然后双指针进行比较 
//时间复杂度O(n) 空间复杂度O(n)
bool Is_Palindrome(Node* plist)
{
	assert(plist != NULL);
	//将链表中的数据先存入数组
	Node* cur = plist->next;
	int len = Get_Lenght(plist);

	//申请数组空间
	ELEMTYPE* arr = (ELEMTYPE*)malloc(len * sizeof(ELEMTYPE));
	if (arr == NULL)
	{
		return false;
	}
	for (int i = 0;i < len; i++)
	{
		arr[i] = cur->data;
		cur = cur->next;
	}
	//判断数组是否为回文数组
	int left = 0;
	int right = len - 1;
	bool ret = true;
	while (left < right)
	{
		if (arr[left] != arr[right])
		{
			ret = false;
			break;
		}

		left++;
		right--;
	}
	free(arr); arr = NULL;
	return ret;
}

//2.快慢指针+中点逆置法 找到中节点 逆置后半部分 然后逐个比较 
//1.找到链表的中点 用快慢指针 时间复杂度O(n)  空间复杂度O(1)
//   2.逆置后半部分   3.比较前后部分
bool Is_Palindrome_Plus(Node* plist)
{
	assert(plist != NULL);

	//空链表 或者链表中只有一个元素 就是回文链表 直接返回
	if (plist->next == NULL || plist->next->next == NULL)
	{
		return true;
	}

	//双指针找到链表中点 偶数链表最终slow会停留在两个中间值的后一位
	Node* slow = plist->next;
	Node* fast = plist->next;
	while (fast != NULL && fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
	}

	//逆置后半部分链表 三指针
	Node* prev = NULL;
	Node* cur = slow;
	Node* next = NULL;
	while (cur != NULL)
	{
		//保存cur的下一个节点
		next = cur->next;
		//修改指针域指向
		cur->next = prev;
		//更新节点
		prev = cur;
		cur = next;
	}

	//比较前后链表
	//逆置之后 prev是逆置后链表的头节点 cur=NULL
	Node* left = plist->next;
	Node* right = prev;
	bool ret = true;
	while (right != NULL)
	{
		if (left->data != right->data)
		{
			ret = false;
			break;
		}
		left = left->next;
		right = right->next;
	}

	//恢复链表
	cur = prev;
	prev = NULL;
	while (cur != NULL)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}

	return ret;
}

//栈区法 将前一半数据压入栈中 根据栈的先进后出特点进行比较
bool Is_Palindrome_Plus_2(Node* plist);


//6.找到单链表倒数第 k 个节点
//申请两个指针 slow fast 让 fast 先走k步 再同时出发 
//当 fast==NULL 时 slow 就到了倒数第k个节点 返回 slow
Node* Get_backwards_k_Node(Node* plist,int k)
{
	if (k <= 0)
	{
		return NULL;
	}
	//申请两个指针
	Node* slow = plist->next;
	Node* fast = plist->next;
	while (k--)
	{
		//当k值超过lenght时退出
		if (fast == NULL)
		{
			return NULL;
		}
		fast = fast->next;
	}
	while (fast != NULL)
	{
		slow = slow->next;
		fast = fast->next;
	}
	return slow;
}


//int main()
//{
//	Node s;
//	Init_List(&s);
//	Insert_tail(&s, 1);
//	Insert_tail(&s, 2);
//	Insert_tail(&s, 2);
//	Insert_tail(&s, 1);
//	//Insert_tail(&s, 1);
//	Show(&s);
//	bool tag = Is_Palindrome_Plus(&s);
//	if (tag)
//	{
//		printf("是回文");
//	}
//	else
//	{
//		printf("不是回文");
//	}
//
//
//	return 0;
//}




