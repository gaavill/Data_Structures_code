#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "AVL.h"
#include <stack>


//工具函数：

/*
	判断当前失衡节点需要哪一种旋转方式    正树左高 负数右高
	将失衡情况分为了4种形态 每一种多赢相应的处理方案
	1.LL型       单右旋
	2.RR型       单左旋
	3.LR型       先左再右 (注意：双旋要先处理失衡节点的子节点)
	4.RL型       先右再左

	失衡节点的平衡因子 == 2 -> 左偏树 确定第一个字母 -> R ?  -> 左孩子的平衡因子 == 1    LL型
	                                                            左孩子的平衡因子 == -1   LR型
	失衡节点平衡因子 == -2 -> 右偏树 确定第一个字母 -> L ? ->  右孩子的平衡因子 == -1    RR型
	                                                           右孩子的平衡因子 == 1     RL型
*/



//单左旋
//左旋是对失衡节点说的   旋转到自己右孩子的左孩子位置
//情况一：旋转目标位置没有节点   直接进入目标位置
//情况二：旋转目标位置有节点     冲突的左孩子变失衡节点的右孩子



//单右旋  
//右旋这句话是对失衡节点来说  旋转到自己左孩子的右孩子位置
//情况一：旋转目的位置没有节点    直接进入目标位置
//情况二：旋转目的位置有节点      冲突的右孩子变失衡节点的左孩子


//通用旋转函数(调用两个旋转函数)

//先左再右
//先左旋是对失衡节点的左孩子说的 再右旋是对失衡节点说的
//旋转完成后 将旋转节点的孩子节点挂回旋转节点的原位置

//先右再左
//先右旋是对失衡节点的右孩子 再左旋是对失衡节点说的
//旋转完成后 将旋转节点的孩子节点挂回旋转节点的原位置






//获取当前节点高度
int Get_Height(AVL_Node* node)
{
	//不存在
	if (node == NULL)
	{
		return -1;
	}

	return node->height;
}

//更新当前节点的高度
void Update_Height(AVL_Node* node)
{
	int h1 = Get_Height(node->left);
	int h2 = Get_Height(node->right);
	node->height = h1 > h2 ? h1 +1 : h2 + 1;
}

//获取当前节点的平衡因子 左子树高度 - 右子树高度
int Get_Balance_Factor(AVL_Node* node)
{
	// 空地址默认平衡
	if (node == NULL)
	{
		return 0;
	}

	return  Get_Height(node->left) - Get_Height(node->right);
}

//操作函数：

//初始化
void Init_AVL(AVL* tree)
{
	tree->root = NULL;
}

//插入

//删除

//查找
AVL_Node* Search_AVL(AVL_Node* root,ELEMTYPE val)
{
	AVL_Node* cur = root;

	while (cur)
	{
		if (cur->data == val)
		{
			return cur;
		}
		else if (cur->data > val)
		{
			cur = cur->left;
		}
		else
		{
			cur = cur->right;
		}
	}

	return NULL;
}

//遍历
void InOrderTraversal(AVL_Node* root)
{
	std::stack<AVL_Node*>st;

	AVL_Node* cur = root;

	while (cur!=NULL&&!st.empty())
	{
		//一路向左
		while (cur)
		{
			st.push(cur);
			cur = cur->left;
		}
		//打印根
		cur = st.top();
		st.pop();

		//转向右子树
		cur = cur->right;
	}
	printf("\n");
}

//判空
bool Empty_AVL(AVL_Node* root)
{
	return root == NULL;
}

//销毁
void Destroy_AVL(AVL_Node* root)
{
	std::stack<AVL_Node*>st;
	st.push(root);
	while (!st.empty())
	{
		AVL_Node* cur = st.top();
		st.pop();
		
		if (cur->left != NULL)
		{
			st.push(cur->left);
		}
		if (cur->right != NULL)
		{
			st.push(cur->right);
		}
		free(cur);
	}
	root = NULL;
}

int main()
{
	AVL tree;
	Init_AVL(&tree);
	const char* str_pre = "532147689";
	const char* str_in = "123456789";

	AVL_Node* node = Search_AVL(tree.root, 8);
	printf("%d \n", node->data);
	InOrderTraversal(tree.root);
	Destroy_AVL(tree.root);
	return 0;
}