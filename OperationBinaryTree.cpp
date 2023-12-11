//二叉树类，通过DFS加剪枝求出最小运动指标
#include "OperationBinaryTree.h"

Node::Node(Operation op) : claw_operation(op), left(nullptr), right(nullptr) {}

OperationBinaryTree::OperationBinaryTree() : root(nullptr) {}

Node* OperationBinaryTree::createNode(Operation op) {
    return new Node(op);
}

void OperationBinaryTree::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

Node* OperationBinaryTree::insert(Node* node,Operation op,int direction){
    if(node==nullptr)
    {
        return createNode(op);
    }
    if(direction==0)
    {
        node->left=createNode(op);
        return node->left;
    }
    if(direction==1)
    {
        node->right=createNode(op);
        return node->right;
    }
    
}
Node* OperationBinaryTree::record(Node* node){
    return node;
}

void OperationBinaryTree::printTree(Node* node) {
    if (node != nullptr) {
        printTree(node->left);
        std::cout << static_cast<int>(node->claw_operation) << " ";
        printTree(node->right);
    }
}

OperationBinaryTree::~OperationBinaryTree() {
    destroyTree(root);
}
