#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Binary_Search_Tree.h"
#include <stack>

//1.初始化
void Init_BST(BST* tree)
{
	if (tree == NULL)
		exit(EXIT_FAILURE);
	tree->root = NULL;
}

//2.查找
BST_Node* Search_BST(BST_Node* root,ELEMTYPE key)
{
	//设置递归出口
	if (root == NULL)
	{
		return NULL;
	}

	//查找根
	if (root->data == key)
	{
		return root;
	}
	
	//查找左子树
	if (root->data > key)
	{
		return Search_BST(root->left, key);
	}
	else
	{
		//查找右子树
		return Search_BST(root->right, key);
	}
}

BST_Node* Search_BST_No_Recursion(BST_Node* root, ELEMTYPE key)
{
	if (root == NULL)
		return NULL;

	BST_Node* cur = root;
	while (cur)
	{
		//查找根
		if (cur->data == key)
		{
			return cur;
		}
		
		//查找左子树
		if (cur->data > key)
		{
			cur = cur->left;
		}
		else
		{
			//查找右子树
			cur = cur->right;
		}
	}
	return NULL;
}

//3.遍历 中序
void InOrderTraversal(BST_Node* root)
{
	if (root == NULL)
		return;

	std::stack<BST_Node*>st;
	BST_Node* cur = root;
	while (cur != NULL || !st.empty())
	{
		//一路向左
		while (cur != NULL)
		{
			st.push(cur);
			cur = cur->left;
		}
		//处理根
		cur = st.top();
		st.pop();
		printf("%d ", cur->data);
		//转向右子树
		
		cur = cur->right;
	}
	printf("\n");
}

//4.插入
//核心：BST 插入就是沿着 BST 的查找路径寻找位置
//如果找到相同值则不插入 如果找到 NULL 则在该 NULL 位置创建新节点
//查找过程的两种情况：1.插入数据已经存在->直接退出
//                    2.找到NULL 插入
bool Insert_BST(BST* tree, ELEMTYPE val)
{
	//1.空树 根节点为NULL 创建根节点
	if (tree->root == NULL)
	{
		tree->root = (BST_Node*)malloc(sizeof(*tree->root));
		if (tree->root == NULL)
			return false;
		
		tree->root->data = val;
		tree->root->left = tree->root->right = NULL;
		tree->root->parent = NULL;

		return true;
	}

	//2.非空树 搜索合适的插入位置 找到后cur==NULL
	BST_Node* cur = tree->root;
	BST_Node* parent = NULL;
	while (cur)
	{
		//更新父节点
		parent = cur;

		if (cur->data > val)
		{
			//搜索左子树 并更新父节点
			cur = cur->left;
		}
		else if (cur->data < val)
		{
			//搜索右子树 并更新父节点
			cur = cur->right;
		}
		else
		{
			//插入节点已经存在
			return false;
		}
	}
	
	//此时已经找到插入位置 申请节点
	BST_Node* newNode = (BST_Node*)malloc(sizeof(*newNode));
	if (newNode == NULL)
		return false;

	newNode->data = val;//赋值数据
	newNode->parent = parent;//赋值父节点
	newNode->left = newNode->right = NULL;//赋值左右子节点

	//根据父节点来判断插左还是插右 左<根<右
	if (parent->data < val)
	{
		parent->right = newNode;
	}
	else
	{
		parent->left = newNode;
	}

	return true;
}

//5.删除
//删除的节点有两个分支
//1.找到待删除节点 
//2.找待删除节点的直接前驱或者直接后继(即待删除节点在中序遍历中的前后节点)
//注意 直接前驱是 左子树中的最大值 直接后继是右子树中的最小值
//3.将找到的直接前驱或者直接后继 的值赋值给待删除节点 
//4.释放直接前驱或者直接后继
//注意：删除双分支就是将其转换成删除一孩子节点 或者 叶子节点
bool Delete_BST(BST* tree, ELEMTYPE val)
{
	if (tree->root == NULL)
		return false;

	BST_Node* del = Search_BST(tree->root, val);
	if (del == NULL)
		return false;

	//如果待删除节点有两个孩子 将其转换成删除一个节点
	if (del->left != NULL && del->right != NULL)
	{
		//找到后继节点
		BST_Node* cat = del->right;
		while (cat->left != NULL)
		{
			cat = cat->left;
		}
		//数据转换
		del->data = cat->data;
		del = cat;//将删除节点进行转换
	}

	//此时 del最多有一个孩子
	BST_Node* parent = del->parent;//保存父节点
	//保存待删除节点的子节点 包括 NULL 
	BST_Node* child = del->left;
	if (del->right != NULL)
	{
		child = del->right;
	}
	
	if (parent == NULL)
	{
		//删除的是根节点
		tree->root = child;
	}
	else
	{
		//非根节点
		if (parent->left == del)//利用指针关系判断
		{
			parent->left = child;
		}
		else
		{
			parent->right = child;
		}
	}
	//处理子节点的父节点指向
	if (child != NULL)
	{
		child->parent = parent;
	}

	free(del);
	return true;
}


//6.销毁
void Destroy_BST(BST_Node* root)
{
	//后序遍历销毁
	if (root == NULL)
		return;

	Destroy_BST(root->left);
	Destroy_BST(root->right);
	free(root);
}

/****************************************************************************/
//找任意一个节点的直接前驱或者直接后继
//直接前驱或者直接后继 是在中序遍历中的前后位置

//找直接后继节点函数
//如果右子树存在 则直接找右子树中的最小值
//如果右子树不存在 则向上寻找 直到找到当前节点位于某个祖先节点的左子树中
//这个祖先节点就是直接后继
//定义的parent 循环条件为 !=NULL && cur=parent.right 
BST_Node* Find_Successor(BST_Node* node)
{
	 //存在右子树 直接找右子树中的最小值
	if (node->right!= NULL)
	{
		BST_Node* cur = node->right;
		while (cur->left != NULL)
		{
			cur = cur->left;
		}
		return cur;
	}

	//右子树不存在 向上搜索找到这个节点位于某个祖先节点的左子树中
	BST_Node* parent = node->parent;
	//parent==NULL则已经到了根 
	while (parent != NULL && node == parent->right)
	{
		//让cur保存父节点 用来判断是否在某个节点的左子树还是右子树
		node = parent;
		parent = parent->parent;//向上搜索
	}
	
	return parent;
}

BST_Node* Find_Predecessor(BST_Node* node)
{
	//存在左子树
	if (node->left != NULL)
	{
		BST_Node* cur = node->left;
		while (cur->right)
		{
			cur = cur->right;
		}
		return cur;
	}

	//不存在左子树
	//只要当前节点是父节点的左孩子 就继续向上
	BST_Node* parent = node->parent;
	while (parent != NULL && node==parent->left)
	{
		node = parent;
		parent = parent->parent;
	}

	return parent;
}

//int main()
//{
//	BST tree;
//	Init_BST(&tree);
//	int arr[10] = { 12,8,46,82,9,3,64,3,5,74 };
//	for (int i = 0; i < 10; i++)
//	{
//		Insert_BST(&tree, arr[i]);
//	}
//	Delete_BST(&tree, 8);
//	InOrderTraversal(tree.root);
//	BST_Node* p = Find_Successor(tree.root->right->right);
//	if (p == NULL)
//	{
//		printf("no_find\n");
//	}
//	Destroy_BST(tree.root);
//	return 0;
//}