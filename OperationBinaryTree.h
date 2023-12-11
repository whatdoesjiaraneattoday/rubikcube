#ifndef OPERATIOM_BINARY_TREE_H
#define OPERATIOM_BINARY_TREE_H

#include<vector>
#include<string>
#include<fstream>
#include<iostream>

//表示机械手各操作的枚举
enum class Operation {
	R,		//右手顺时针转动
	_R ,	//右手逆时针转动
	F,		//左手顺时针转动
	_F ,	//左手逆时针转动
	R2 ,	//R面转动180°	
	F2 ,	//F面转动180°
	LeftLoose,	//左手松开		
	LeftTight,	//左手夹紧
	RightLoose,	//右手松开
	RightTight	//右手夹紧
};

struct Node{
    Operation claw_operation;
    Node* left;
    Node* right;

    //初始化
    Node(Operation op);
};

//二叉树
class OperationBinaryTree {
private:
    Node* root;
    //建立节点
    Node* createNode(Operation op);
    //摧毁树
    void destroyTree(Node* node);

public:
    //类的初始化
    OperationBinaryTree();
    //插入节点
    Node* insert(Node* node,Operation op, int direction=0);
    //记录节点
    Node* record(Node*node);
    //输出树
    void printTree(Node* node);
    //析构
    ~OperationBinaryTree();
};
#endif
