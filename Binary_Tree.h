#pragma once



typedef char ELEMTYPE;

//辅助节点 指向根节点
typedef struct BinaryTree
{
	struct BinaryTreeNode* root;
};

//二叉链表 
typedef struct BinaryTreeNode
{
	ELEMTYPE data;//数据域
	struct BinaryTreeNode* left_child;//左孩子指针域
	struct BinaryTreeNode* right_child;//右孩子指针域
};


//三叉链表定义
typedef struct BinaryTreeNode_T
{
	ELEMTYPE data;//数据域
	struct BinaryTreeNode_T* left_child;//左孩子指针域
	struct BinaryTreeNode_T* right_child;//右孩子指针域
	struct BinaryTreeNode_T* parent;//父节点指针域
};


//二叉树创建 前序+唯一字符串
BinaryTreeNode* Create_Binary_Tree_Pre(const char** str);

//二叉树创建 前序+中序 递归
BinaryTreeNode* Create_Binary_Tree_Pre_In(
	const char* preorder, const char* inorder, int Size);

//二叉树创建 中序+后序 递归
BinaryTreeNode* Create_Binary_Tree_In_Post(
	const char* inorder, const char* postorder, int Size);

//前序遍历(递归)
void Pre_Order_Traversal(BinaryTreeNode* root);

//中序遍历(递归)
void In_Order_Traversal(BinaryTreeNode* root);

//后序遍历(递归)
void Post_Order_Traversal(BinaryTreeNode* root);

//申请一个新节点
BinaryTreeNode* BuyNode();


//非递归就是用堆栈来代替递归时产生的函数栈帧(非递归只需要保存真正需要保存的状态) 
//防止栈溢出

//前序遍历(非递归)
void Pre_Order_Traversal_No_Recursion(BinaryTreeNode* root);

//中序遍历(非递归)
void In_Order_Traversal_No_Recursion(BinaryTreeNode* root);

//后序遍历(非递归)单栈法
void Post_Order_Traversal_No_Recursion1(BinaryTreeNode* root);

//后序遍历(非递归)双栈法
void Post_Order_Traversal_No_Recursion2(BinaryTreeNode* root);

//后序销毁二叉树(递归)
void Destroy_Binary_Tree(BinaryTreeNode* root);

//非递归销毁二叉树
void Destroy_Binary_Tree_1(BinaryTreeNode* rot);

//层序遍历 左->右
void Level_Order_Traversal_left_To_right(BinaryTreeNode* root);

//层序遍历 右->左
void Level_Order_Traversal_right_To_left(BinaryTreeNode* root);

//层序遍历 正S
void Level_Order_Traversal_S(BinaryTreeNode* root);

//层序遍历 倒S
void Level_Order_Traversal_Reverse_S(BinaryTreeNode* root);

//统计二叉树节点数量
int Total_Node_Binary_Tree(BinaryTreeNode* root);

//二叉树深度(高度) 根节点到最远叶子节点的节点数量
int BinaryTree_Depth(BinaryTreeNode* root);

//求叶子节点数量
int Total_Leaf_Node(BinaryTreeNode* root);

//查找节点
BinaryTreeNode* Find_BinaryTree_Node(BinaryTreeNode* root,ELEMTYPE val);



