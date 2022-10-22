#include <iostream>
#include <vector>
#include "bst.h"

void printTree(BST tree)
{
    std::vector<int> orderedTree = tree.inOrder();
    std::cout <<"The numbers in sorted order: ";
    for(int i = 0 ; i < orderedTree.size(); i++)
    {
        std::cout << orderedTree.at(i) << " "; 
    }
    std::cout << std::endl;

    tree.prettyPrint();
}
BST getInput()
{
    std::cout << "Enter the numbers to be stored: " << std::endl;
    BST tree;
    int num;
    std::cin >> num;
    while (!std::cin.fail())
    {
        tree.insertKey(num);
        std::cin >> num;
    }
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    return tree;
}
int main()
{
    BST tree = getInput();
    printTree(tree);
}