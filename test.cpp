#include <iostream>

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
