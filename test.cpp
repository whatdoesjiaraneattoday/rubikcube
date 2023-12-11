#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    Node* root;

    Node* createNode(int value) {
        return new Node(value);
    }

    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    void insert(int value) {
        root = insertRecursive(root, value);
    }

    Node* insertRecursive(Node* node, int value) {
        if (node == nullptr) {
            return createNode(value);
        }

        if (value < node->data) {
            node->left = insertRecursive(node->left, value);
        } else if (value > node->data) {
            node->right = insertRecursive(node->right, value);
        }

        return node;
    }

    void printInOrder() {
        printInOrderRecursive(root);
        std::cout << std::endl;
    }

    void printInOrderRecursive(Node* node) {
        if (node != nullptr) {
            printInOrderRecursive(node->left);
            std::cout << node->data << " ";
            printInOrderRecursive(node->right);
        }
    }

    ~BinaryTree() {
        destroyTree(root);
    }
};

int main() {
    BinaryTree tree;
    
    // Insert elements into the tree
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    // Print the tree in order (should print sorted elements)
    tree.printInOrder();

    return 0;
}
