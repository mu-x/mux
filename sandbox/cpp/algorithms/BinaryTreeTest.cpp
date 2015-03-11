#include "BinaryTree.hpp"

#include <iostream>
#include <string>

int main()
{
    BinaryTree<int, std::string> tree;

    tree[5] = "root";
    tree[0] = "left";
    tree[10] = "right";
    tree[15] = "tmp";
    tree[8] = "right-left";
    tree[15] = "right-right";

    std::cout << tree << std::endl;

    tree.remove(0);
    tree.remove(10);

    std::cout << tree << std::endl;
}
