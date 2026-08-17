#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Binary_Tree.h"
#include <memory.h>

//申请一个新节点
BinaryTreeNode* BuyNode()
{
	BinaryTreeNode* NewNode = (BinaryTreeNode*)malloc(sizeof(*NewNode));
	if (NewNode == NULL)
	{
		exit(EXIT_FAILURE);
	}
	//内存重置 将指针设为 NULL
	memset(NewNode, 0, sizeof(*NewNode));

	return NewNode;
}

//搭建二叉树
void Create_Binary_Tree(BinaryTree* Tree)
{
	assert(Tree);

	BinaryTreeNode* NewNode1 = BuyNode();
	NewNode1->data = 'A';
	Tree->root = NewNode1;

	BinaryTreeNode* NewNode2 = BuyNode();
	BinaryTreeNode* NewNode3 = BuyNode();
	NewNode2->data = 'B';
	NewNode1->left_child = NewNode2;
	NewNode3->data = 'G';
	NewNode1->right_child = NewNode3;

	BinaryTreeNode* NewNode4 = BuyNode();
	BinaryTreeNode* NewNode5 = BuyNode();
	BinaryTreeNode* NewNode6 = BuyNode();
	NewNode4->data = 'C';
	NewNode5->data = 'D';
	NewNode6->data = 'H';
	NewNode2->left_child = NewNode4;
	NewNode2->right_child = NewNode5;
	NewNode3->left_child = NewNode6;

	BinaryTreeNode* NewNode7 = BuyNode();
	BinaryTreeNode* NewNode8 = BuyNode();
	NewNode7->data = 'E';
	NewNode8->data = 'F';
	NewNode5->left_child = NewNode7;
	NewNode5->right_child = NewNode8;

}

//前序遍历(递归)
void Pre_Order_Traversal(BinaryTreeNode* root)
{
	//设置递归出口
	if (root == NULL)
	{
		return;
	}
	//根
	printf("%c ", root->data);
	//左
	Pre_Order_Traversal(root->left_child);
	//右
	Pre_Order_Traversal(root->right_child);
}

//中序遍历(递归)
void In_Order_Traversal(BinaryTreeNode* root)
{
	if (root == NULL)
	{
		return;
	}

	//左
	In_Order_Traversal(root->left_child);
	//根
	printf("%c ", root->data);
	//右
	In_Order_Traversal(root->right_child);
}

//后序遍历(递归)
void Post_Order_Traversal(BinaryTreeNode* root)
{
	if (root == NULL)
	{
		return;
	}

	//左
	Post_Order_Traversal(root->left_child);
	//右
	Post_Order_Traversal(root->right_child);
	//根
	printf("%c ", root->data);
}

//后序销毁
void Destroy_Binary_Tree(BinaryTreeNode* root)
{
	if (root == NULL)
	{
		return;
	}
	Destroy_Binary_Tree(root->left_child);
	Destroy_Binary_Tree(root->right_child);
	free(root);
}


/************************************************************************************************************/
//注意：进行入栈操作时 需要考虑的是出栈时的需求

#include <stack>
//前序遍历(非递归)
//流程：
//根 → 左 → 右
//访问根后：
//右入栈 → 左入栈
void Pre_Order_Traversal_No_Recursion(BinaryTreeNode* root)
{
	assert(root);

	//创建栈
	std::stack<BinaryTreeNode*>st;

	//将根节点入栈
	st.push(root);
	//while循环 条件为栈不空
	while (!st.empty())
	{
		//弹出栈顶节点并访问 然后将左右子节点按顺序压入栈中(先右后左)
		BinaryTreeNode* cur = st.top();
		printf("%c ", cur->data);
		st.pop();
		//栈为先进后出 所以right先进left后进 来保证left先出
		if (cur->right_child != NULL)
		{
			st.push(cur->right_child);
		}
		if (cur->left_child != NULL)
		{
			st.push(cur->left_child);
		}
	}
	printf("\n");
}

//中序遍历(非递归)
//流程：
//左 → 根 → 右
//一路向左入栈：
//左边到底 → 弹栈访问 → 转右
//核心思想：先将根和左孩子全部入栈 走到最后一个节点时 它的左节点为NULL
//所以访问其根 再处理其右孩子
void In_Order_Traversal_No_Recursion(BinaryTreeNode* root)
{
	assert(root);

	//创建栈
	std::stack<BinaryTreeNode*>st;
	//创建临时指针
	BinaryTreeNode* cur = root;

	//循环条件为指针不空或者栈不空
	while (cur != NULL || !st.empty())
	{
		//一路向左 将根节点和左子树全部入栈
		while (cur != NULL)
		{
			st.push(cur);
			cur = cur->left_child;
		}
		//此时cur已经没有左孩子了 直接访问其根
		cur = st.top();
		st.pop();
		printf("%c ", cur->data);
		//处理右孩子
		cur = cur->right_child;
		//如果右孩子为空 则会跳过将左孩子全部入栈这一过程
		//下一步直接从栈中取值进行访问
	}
	printf("\n");
}

//后序遍历(非递归)单栈法
//流程：
// 左 → 右 → 根
//一路向左入栈：
//检查右子树
//↓
//没有 / 已处理 → 访问根
//有且未处理 → 转向右子树
//思想：先将左处理完 判断右子树是否存在/或者右子树已经处理完  访问根
//cur!=NULL 表示现在处理的是一颗新子树 需要一路向左
//cur==NULL 表示向下探索已经完成 需要从栈中返回 处理上游节点
void Post_Order_Traversal_No_Recursion1(BinaryTreeNode* root)
{
	if (root == NULL)
		return;

	//申请栈
	std::stack<BinaryTreeNode*>st;
	
	BinaryTreeNode* cur = root;
	BinaryTreeNode* prev = NULL;//保存已经被访问过的节点

	while (cur != NULL || !st.empty())
	{
		//一路向左
		while (cur != NULL)
		{
			st.push(cur);
			cur = cur->left_child;
		}
		//查看栈顶节点 即当前子树的根节点
		cur = st.top();
		
		//右子树不存在 或者右子树已经被处理完
		if (cur->right_child == NULL || cur->right_child == prev)
		{
			//直接访问根
			st.pop();
			printf("%c ", cur->data);
			//保存当前已经访问的节点
			prev = cur;
			//返回上一个节点继续处理 即当前节点已经处理完 不需要再向左探索
			cur = NULL;
		}
		else
		{
			//右子树还没有处理 就先处理右子树
			cur = cur->right_child;
		}
	}
	printf("\n");
}

//后续遍历双栈法
//第一次遍历按照 根->右->左 的顺序(此处的顺序为出栈顺序) 将结果保存进第二个栈中
//再从第二个栈中进行输出 就是 左->右->根 的顺序
//注意：第一次遍历的时候需要 左先入栈 再右入栈 保证右子树先出
//从而让第二个栈出栈顺序为 左->右->根
void Post_Order_Traversal2(BinaryTreeNode* root)
{
	if (root == NULL)
		return;

	//申请两个栈
	std::stack<BinaryTreeNode*>st1;//模拟递归栈调用
	std::stack<BinaryTreeNode*>st2;//保存第一次遍历的结果

	st1.push(root);//根先入栈

	//第一次遍历(此处的顺序为出栈的顺序) 根->右->左
	while (!st1.empty())
	{
		BinaryTreeNode* cur = st1.top();
		st1.pop();
		//保存到第二个栈
		st2.push(cur);
		
		if (cur->left_child != NULL)
		{
			st1.push(cur->left_child);//左入栈
		}
		if (cur->right_child != NULL)
		{
			st1.push(cur->right_child);//右入栈
		}
	}

	//第二个栈里出栈已经是 左->右->根 顺序
	while (!st2.empty())
	{
		printf("%c ", st2.top()->data);
		st2.pop();
	}
	printf("\n");
}


//非递归销毁 单栈法
//核心：只需要将当前节点的孩子入栈 之后就可ui销毁节点了
void Destroy_Binary_Tree_1(BinaryTreeNode* root)
{
	if (root == NULL)
		return;

	std::stack<BinaryTreeNode*>st1;

	st1.push(root);

	while (!st1.empty())
	{
		BinaryTreeNode* cur = st1.top();
		st1.pop();

		if (cur->left_child != NULL)
		{
			st1.push(cur->left_child);
		}
		if (cur->right_child != NULL)
		{
			st1.push(cur->right_child);
		}

		//只要节点的孩子入栈了就可以销毁了
		free(cur);
	}
	root = NULL;
}

/********************************************************************************************************/
#include <queue>
//层序遍历
//利用队列 先进先出
//从左至右
void Level_Order_Traversal_left_To_right(BinaryTreeNode* root)
{
	if (root == NULL)
		return;
	//申请队列
	std::queue<BinaryTreeNode*>qu;
	//根入队
	qu.push(root);

	while (!qu.empty())
	{
		//打印根
		BinaryTreeNode* cur = qu.front();
		qu.pop();
		printf("%c ", cur->data);

		//从左->右  左先入队
		if (cur->left_child != NULL)
		{
			qu.push(cur->left_child);
		}
		//右入队
		if (cur->right_child != NULL)
		{
			qu.push(cur->right_child);
		}
	}
	printf("\n");
}

//从右到左打印
void Level_Order_Traversal_right_To_left(BinaryTreeNode* root)
{
	if (root == NULL)
		return;
	//申请队列
	std::queue<BinaryTreeNode*>qu;
	//根入队
	qu.push(root);

	while (!qu.empty())
	{
		//打印根
		BinaryTreeNode* cur = qu.front();
		qu.pop();
		printf("%c ", cur->data);

		//右入队
		if (cur->right_child != NULL)
		{
			qu.push(cur->right_child);
		}
		//左入队
		if (cur->left_child != NULL)
		{
			qu.push(cur->left_child);
		}
	}
	printf("\n");
}

//层序 正S
//第一层 先右后左
//双栈法：
//先将栈1中的节点拿出来打印 然后将其孩子按照先右后左压入栈2中
//判断栈2 将节点拿出来打印 再将其孩子按照先左后后压入栈1
void Level_Order_Traversal_S(BinaryTreeNode* root)
{
	if (root == NULL)
		return;

	//申请两个栈
	std::stack<BinaryTreeNode*>st1;
	std::stack<BinaryTreeNode*>st2;

	//根入栈
	st1.push(root);

	//只要有一个栈不空 就继续判断  每次进入循环时一定只有一个栈有数据
	while (!st1.empty() || !st2.empty())
	{
		//如果栈1不空 将其孩子按照先右后左的顺序压入栈2
		while (!st1.empty())
		{
			BinaryTreeNode* cur = st1.top();
			st1.pop();
			printf("%c ", cur->data);

			//右->左处理孩子
			if (cur->right_child != NULL)
			{
				st2.push(cur->right_child);
			}
			if (cur->left_child != NULL)
			{
				st2.push(cur->left_child);
			}
		}

		//如果栈2不空 将其孩子按照先左后右的顺序压入栈1
		while (!st2.empty())
		{
			BinaryTreeNode* cur = st2.top();
			st2.pop();
			printf("%c ", cur->data);

			//左->右处理孩子
			if (cur->left_child != NULL)
			{
				st1.push(cur->left_child);
			}
			if (cur->right_child != NULL)
			{
				st1.push(cur->right_child);
			}
		}
	}
	printf("\n");
}

//倒S 
//第一层：左->右
void Level_Order_Traversal_Reverse_S(BinaryTreeNode* root)
{
	if (root == NULL)
		return;

	std::stack<BinaryTreeNode*>st1, st2;

	st1.push(root);

	while (!st1.empty() || !st2.empty())
	{
		//如果栈1不空 将其孩子按照先左后右的顺序压入栈2
		while (!st1.empty())
		{
			BinaryTreeNode* cur = st1.top();
			st1.pop();
			printf("%c ", cur->data);

			if (cur->left_child != NULL)
			{
				st2.push(cur->left_child);
			}
			if (cur->right_child != NULL)
			{
				st2.push(cur->right_child);
			}
		}

		//如果栈2不空 将其孩子按照先右后左的顺序压入栈1
		while (!st2.empty())
		{
			BinaryTreeNode* cur = st2.top();
			st2.pop();
			printf("%c ", cur->data);

			if (cur->right_child != NULL)
			{
				st1.push(cur->right_child);
			}
			if (cur->left_child != NULL)
			{
				st1.push(cur->left_child);
			}
		}
	}
	printf("\n");
}
//test
int main()
{
	BinaryTree tree;
	
	Create_Binary_Tree(&tree);
	printf("前序:");
	Pre_Order_Traversal(tree.root);
	printf("\n中序:");
	In_Order_Traversal(tree.root);
	printf("\n后序:");
	Post_Order_Traversal(tree.root);
	printf("\n\n\n前序:");
	Pre_Order_Traversal_No_Recursion(tree.root);
	printf("中序:");
	In_Order_Traversal_No_Recursion(tree.root);
	printf("后续1:");
	Post_Order_Traversal_No_Recursion1(tree.root);
	printf("后续2:");
	Post_Order_Traversal2(tree.root);
	printf("\n\n层序 左->右:");
	Level_Order_Traversal_left_To_right(tree.root);
	printf("层序 右->左:");
	Level_Order_Traversal_right_To_left(tree.root);
	printf("层序 正S:");
	Level_Order_Traversal_S(tree.root);
	printf("层序 倒S:");
	Level_Order_Traversal_Reverse_S(tree.root);
	printf("\n");



	Destroy_Binary_Tree_1(tree.root);
	return 0;
}