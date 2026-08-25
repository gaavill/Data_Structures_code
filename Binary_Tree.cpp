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

//单个序列构造唯一二叉树(前序) 指针偏移+递归  默认节点元素不重复
//思想：先构建一个前序的字符串str 将无效节点用 '#'表示
//读取字符串 如果不是'#'就创建节点 再递归左子树 递归右子树
//注意：必须让str中的字符逐个向后走 不能因为递归而回到上一次的位置
BinaryTreeNode* Create_Binary_Tree_Pre(const char** str)
{
	//使用二级指针传参 让所有递归层都操作一个str 也可以使用char*&
	//修改指针变量本身
	ELEMTYPE ch = **str;
	(*str)++;
	
	//如果为# 返回NULL 即递归出口
	if (ch == '#')
	{
		return NULL;
	}
	//创建节点
	BinaryTreeNode* root = BuyNode();
	root->data = ch;

	//递归构建左子树
	root->left_child = Create_Binary_Tree_Pre(str);
	//递归构建右子树
	root->right_child = Create_Binary_Tree_Pre(str);

	//把当前构造的节点返回给上一层
	return root;
}

//两个序列构造唯一二叉树
//两个序列构造唯一二叉树(前序 中序)
//核心思想：前序确定根节点 中序确定左右分布  
//前序负责找根 中序负责划分左右子树  
//流程：先在前序中确定根 然后申请节点 再左右递归构造子树
//找前序中确定的根节点在中序中的位置函数
int Find_pos(const char* str, char ch)
{
	int pos = 0;
	while (*str)
	{
		if (*str == ch)
		{
			return pos;
		}
		str++;
		pos++;
	}
	return -1;
}
BinaryTreeNode* Create_Binary_Tree_Pre_In(const char* preorder,const char* inorder, int Size)
{
	//设置递归出口 即当前子树节点个数等于0就退出
	if (Size <= 0)
	{
		return NULL;
	}
	//申请节点 前序的第一个元素就是根
	BinaryTreeNode* root = BuyNode();
	root->data = preorder[0];

	//在中序中找前序中设置为根的节点在中序中的下标 方便计算指针偏移量
	int pos = Find_pos(inorder, root->data);
	if (pos == -1)
	{
		free(root);
		return NULL;
	 }
	/* 在中序中确定根的位置 再回到前序中根据中序确定前序的左右子树
	* 根在中序中左边就是左子树 右边就是右子树
	前序：A | B C D E F | G H
	      根   左子树    右子树
	中序：C B E D F | A |  G H
	      左子树     根   右子树	 
	*/
	//递归构造左子树
	root->left_child = Create_Binary_Tree_Pre_In(
		preorder +1, inorder, pos);
	//递归构造右子树
	root->right_child = Create_Binary_Tree_Pre_In(
		preorder +pos +1, inorder +pos +1,Size -pos -1);

	return root;
}

//两个序列构造唯一二叉树(中序 后序)
//核心思想：利用后序来确定根节点 中序来确定左右子树
//后序从后往前就是根节点的顺序
BinaryTreeNode* Create_Binary_Tree_In_Post(const char* inorder, const char* postorder, int Size)
{
	if (Size <= 0)
	{
		return NULL;
	}

	BinaryTreeNode* root = BuyNode();
	//后序的最后一个元素就是根
	root->data = postorder[Size - 1];
	//找到根节点在中序中的位置下标
	int pos = Find_pos(inorder, root->data);

	/*
	中序：C B E D F | A |  G H
	        左子树   根   右子树
	后续：C E F D B | H G | A
	      左子树    右子树  根
	*/
	//递归构造左子树
	root->left_child = Create_Binary_Tree_In_Post(
		inorder,postorder, pos);
	//递归构造右子树
	root->right_child = Create_Binary_Tree_In_Post(
		inorder + pos + 1,postorder + pos, Size - pos - 1);

	return root;
}


/******************************************************************************/

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
void Post_Order_Traversal_No_Recursion2(BinaryTreeNode* root)
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


//统计二叉树节点数量
int Total_Node_Binary_Tree(BinaryTreeNode* root)
{
	if (root == NULL)
	{
		return 0;
	}
	//左+右+根
	return 1 + Total_Node_Binary_Tree(root->left_child) +
		Total_Node_Binary_Tree(root->right_child);
}

//二叉树深度(高度) 根节点到最远叶子节点的节点数量
int BinaryTree_Depth(BinaryTreeNode* root)
{
	if (root == NULL)
	{
		return 0;
	}

	int left_depth = BinaryTree_Depth(root->left_child);
	int right_depth = BinaryTree_Depth(root->right_child);

	return left_depth > right_depth ? left_depth + 1 : right_depth + 1;
}

//求叶子节点数量
int Total_Leaf_Node(BinaryTreeNode* root)
{
	if (root == NULL)
	{
		return 0;
	}

	if (root->left_child == NULL && root->right_child == NULL)
	{
		return 1;
	}

	return Total_Leaf_Node(root->left_child) +
		Total_Leaf_Node(root->right_child);
}

//查找节点
BinaryTreeNode* Find_BinaryTree_Node(BinaryTreeNode* root, ELEMTYPE val)
{
	if (root == NULL)
	{
		return NULL;
	}

	if (root->data == val)
	{
		return root;
	}

	//查找左子树
	BinaryTreeNode* left = Find_BinaryTree_Node(root->left_child, val);
	if (left != NULL)
	{
		return left;
	}
	//查找右子树
	return Find_BinaryTree_Node(root->right_child, val);
}

//test
//int main()
//{
//	BinaryTree tree;
//    const char* str = "ABC##DE##F##G#H##";
//	//tree.root = Create_Binary_Tree_Pre(&str);
//	const char* str_Pre = "ABCDEFGH";
//	const char* str_In = "CBEDFAGH";
//	const char* str_Post = "CEFDBHGA";
//	//tree.root = Create_Binary_Tree_Pre_In(str_Pre,str_In,8);
//	tree.root = Create_Binary_Tree_In_Post(str_In, str_Post, 8);
//	printf("前序:");
//	Pre_Order_Traversal(tree.root);
//	printf("\n中序:");
//	In_Order_Traversal(tree.root); 
//	printf("\n后序:");
//	Post_Order_Traversal(tree.root);
//	printf("\n\n\n前序:");
//	Pre_Order_Traversal_No_Recursion(tree.root);
//	printf("中序:");
//	In_Order_Traversal_No_Recursion(tree.root);
//	printf("后续1:");
//	Post_Order_Traversal_No_Recursion1(tree.root);
//	printf("后续2:");
//	Post_Order_Traversal_No_Recursion2(tree.root);
//	printf("\n\n层序 左->右:");
//	Level_Order_Traversal_left_To_right(tree.root);
//	printf("层序 右->左:");
//	Level_Order_Traversal_right_To_left(tree.root);
//	printf("层序 正S:");
//	Level_Order_Traversal_S(tree.root);
//	printf("层序 倒S:");
//	Level_Order_Traversal_Reverse_S(tree.root);
//	printf("\n");
//
//	printf("%d\n", Total_Node_Binary_Tree(tree.root));
//
//	printf("%d\n", BinaryTree_Depth(tree.root));
//	
//	printf("%d\n", Total_Leaf_Node(tree.root));
//	BinaryTreeNode* p = Find_BinaryTree_Node(tree.root, 'p');
//	printf("%p\n", &p->data);
//	Destroy_Binary_Tree_1(tree.root);
//	return 0;
//}