#pragma once

//前提是一颗二叉树
/*
1.空树也是二叉搜索树
2.如果二叉搜索树的左子树不为空 则其左子树上所有节点关键值都小于其根节点的关键值
3.如果BST的右子树不为空 则其右子树上所有节点的关键值都大于其根节点的关键值
4.BST的子树也是二叉搜索树
5.BST的关键值互不相同

左<根<右

用链表来实现BST 
BST运用在文件系统 数据库 排序 检索
*/

typedef int ELEMTYPE;

//节点设计 三叉链表设计
typedef struct BST_Node
{
	ELEMTYPE data;
	struct BST_Node* left;//左节点
	struct BST_Node* right;//右节点
	struct BST_Node* parent;//父节点
}BST_Node;

//BST设计
typedef struct BST
{
	struct BST_Node* root;//指向BST的根节点
}BST;


//1.初始化
void Init_BST(BST* tree);

//2.查找
BST_Node* Search_BST(BST_Node* root,ELEMTYPE key);

//3.遍历 中序
void InOrderTraversal(BST_Node* root);

//4.插入
bool Insert_BST(BST* tree, ELEMTYPE val);

//5.删除
bool Delete_BST(BST* tree, ELEMTYPE val);

//销毁
void Destroy_BST(BST_Node* root);