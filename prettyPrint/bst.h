#ifndef BST_H
#define BST_H
#include <iostream>
#include <vector>
#include "bstNode.h"

class BST
{
public:
    BST(){ root = nullptr;}
    ~BST(){ deleteBST(root);}
    void insertKey(int newKey);
    bool hasKey(int searchKey);
    std::vector<int> inOrder();
    void prettyPrint();
    int getHeight(){ return traverseHeight(root);}
private:
    Node* root;
    std::vector<int> orderedTree;
    std::vector<std::vector<std::string>> tree;
    void getTree();
    void printCeiling();
    void initializeTreeVector();
    void deleteBST(Node* node);
    int traverseHeight(Node* node);
    void traverseInOrder(Node* node);
    void traverseInsert(int num, Node* node);
    bool traverseSearch(int num, Node* node);
    int getDistanceToNode(Node* node, int searchKey);
};

#endif
