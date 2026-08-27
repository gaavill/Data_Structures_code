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
AVL_Node* Left_Rotate(AVL_Node* node)
{
	if (node == NULL || node->right == NULL)
		return NULL;

	//保存失衡节点的右孩子
	AVL_Node* right_child = node->right;
	//保存失衡节点的右孩子的左子树
	AVL_Node* grand_child = right_child->left;

	//将失衡节点的右孩子的左子树挂在失衡节点的右子树位置
	node->right = grand_child;
	//将失衡节点挂在其右孩子的左子树上
	right_child->left = node;

	//更新失衡节点和失衡节点右子树的高度
	Update_Height(node);
	Update_Height(right_child);

	return right_child;
}


//单右旋  
//右旋这句话是对失衡节点来说  旋转到自己左孩子的右孩子位置
//情况一：旋转目的位置没有节点    直接进入目标位置
//情况二：旋转目的位置有节点      冲突的右孩子变失衡节点的左孩子
AVL_Node* Right_Rotate(AVL_Node* node)//node为失衡节点
{
	if (node == NULL)
		return NULL;

	//保存失衡节点的左孩子
	AVL_Node* left_child = node->left;
	//保存失衡节点左孩子的右子树
	AVL_Node* grand_child = left_child->right;//可能为NULL

	//将失衡节点的左孩子的右孩子挂在失衡节点的左子树
	node->left = grand_child;
	//将失衡节点挂在其左孩子的右子树位置
	left_child->right = node;

	//更新节点树高(失衡节点和失衡节点的左孩子)
	Update_Height(node);
	Update_Height(left_child);

	//返回新的根节点
	return left_child;
}




//先左再右
//先左旋是对失衡节点的左孩子说的 再右旋是对失衡节点说的
//旋转完成后 将旋转节点的孩子节点挂回旋转节点的原位置

//先右再左
//先右旋是对失衡节点的右孩子 再左旋是对失衡节点说的
//旋转完成后 将旋转节点的孩子节点挂回旋转节点的原位置

//通用旋转函数(调用两个旋转函数)
//根据传入节点的失衡情况 来判断怎么旋转  //失衡情况最多为 -2 2 两种情况
AVL_Node* Rotate(AVL_Node* node)
{
	assert(node);
	
	//获取失衡节点平衡因子 
	int BF_node = Get_Balance_Factor(node);

	if (BF_node > 1) //左子树过高
	{
		int BF_left = Get_Balance_Factor(node->left);

		if (BF_left >= 0)
		{
			//LL型  调用单右旋
			return Right_Rotate(node);
		}
		else   
		{
			//LR型  先左(失衡节点的左孩子)再右(失衡节点)
			node->left = Left_Rotate(node->left);
			return Right_Rotate(node);
		}
	}
	
	if (BF_node < -1) //右子树过高
	{
		int BF_right = Get_Balance_Factor(node->right);

		if (BF_right <= 0)
		{
			//RR型 单左旋
			return Left_Rotate(node);
		}
		else
		{
			//RL 先右再左   先右孩子再失衡节点
			node->right = Right_Rotate(node->right);
			return Left_Rotate(node);
		}
	} 

	//没有发生失衡现象 直接返回
	return node;
}


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

//插入 递归  
AVL_Node* Insert_Helper(AVL_Node* root, ELEMTYPE val)
{
	//找到插入位置插入
	if (root == NULL)
	{
		AVL_Node* newNode = (AVL_Node*)malloc(sizeof(*newNode));
		if (newNode == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		newNode->data = val;
		newNode->left = NULL;
		newNode->right = NULL;
		Update_Height(newNode);

		return newNode;
	}

	//递归查找插入位置
	if (val < root->data)
	{
		root->left = Insert_Helper(root->left, val);
	}
	else if (val > root->data)
	{
		root->right = Insert_Helper(root->right, val);
	}
	else
	{
		return root;//数据已经存在 直接返回根
	}

	//修正根节点高度
	Update_Height(root);

	//解决失衡情况
	root = Rotate(root);

	//插入完成 返回根节点
	return root;
}

void Insert_AVL(AVL* tree, ELEMTYPE val)
{
	tree->root = Insert_Helper(tree->root, val);
}


//插入导致的失衡只需要平衡调整一次
//删除导致的失衡可能需要平衡调整多次
//删除
//在BST的基础上进行删除 每次删除完再进行失衡调整
//流程：
//1.查找待删除节点 ->
//2.判断是0/1/2分支 如果是2分支 将其转换为删除其直接后继节点
//2.删除完成后 回溯判断是否造成失衡 将失衡节点进行调整
AVL_Node* Delete_help(AVL_Node* root, ELEMTYPE val)
{
	if (root == NULL)
	{
		return NULL;
	}
	
	//左子树查找
	if (val < root->data)
	{
		root->left = Delete_help(root->left, val);
	}
	else if (val > root->data)
	{
		//右子树查找
		root->right = Delete_help(root->right, val);
	}
	else //找到待删除节点
	{
		//左孩子为NULL (此处右孩子也可能为NULL)
		if (root->left == NULL)
		{
			AVL_Node* right = root->right;
			free(root);
			return right;//将其子节点返回给待删除节点的父节点
		}
		//右孩子为NULL (此处左孩子也可能为NULL)
		if (root->right == NULL)
		{
			AVL_Node* left = root->left;
			free(root);
			return left;
		}
		//左右孩子都存在 转换为删除其直接后继
		AVL_Node* successor = root->right;
		while (successor->left != NULL)
		{
			successor = successor->left;
		}
		//将直接后继的值赋值给原待删除节点
		root->data = successor->data;
		//再去右子树中进行删除
		root->right = Delete_help(root->right, successor->data);
	}
	//更新节点高度
	Update_Height(root);
	//平衡调整
	return Rotate(root); 
}

void Delete_AVL(AVL* tree, ELEMTYPE val)
{
	tree->root = Delete_help(tree->root, val);
}

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

	while (cur!=NULL || !st.empty())
	{
		//一路向左
		while (cur!=NULL)
		{
			st.push(cur);
			cur = cur->left;
		}
		//打印根
		cur = st.top();
		st.pop();
		printf("%d ", cur->data);
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
void Destroy_AVL(AVL* tree)
{
	if (tree == NULL || tree->root == NULL)
		return;

	std::stack<AVL_Node*>st;
	st.push(tree->root);
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
	tree->root = NULL;
}

int main()
{
	AVL tree;
	Init_AVL(&tree);
	int arr[10] = { 14,9,5,17,11,12,7,19,16,27 };
	for (int i = 0; i < 10; i++)
	{
		Insert_AVL(&tree ,arr[i]);
	}
	
	InOrderTraversal(tree.root);

	Delete_AVL(&tree, 17);
	InOrderTraversal(tree.root);
	Destroy_AVL(&tree);
	return 0;
}