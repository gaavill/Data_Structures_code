#pragma once

typedef int ELEMTYPE;

//平衡因子范围[-1,0,1] = 左子树高度 - 右子树高度

//节点设计
typedef struct AVL_Node
{
	ELEMTYPE data;
	struct AVL_Node* left;
	struct AVL_Node* right;
	int height;//节点的高度
}AVL_Node;

//AVL设计
typedef struct AVL
{
	struct AVL_Node* root;
}AVL;



//工具函数：

//单左旋


//单右旋


//通用旋转函数(调用两个旋转函数)


//获取当前节点高度
int Get_Height(AVL_Node* root);

//更新当前节点的高度
void Update_Height(AVL_Node* root);

//获取当前节点的平衡因子
int Get_Balance_Factor(AVL_Node* root);

//操作函数：

//初始化
void Init_AVL(AVL* tree);

//插入

//删除

//查找
AVL_Node* Search_AVL(AVL_Node* root, ELEMTYPE val);

//遍历
AVL_Node* Search_AVL(AVL_Node* root, ELEMTYPE val);

//判空
bool Empty_AVL(AVL_Node* root);

//销毁
void Destroy_AVL(AVL* tree);


