#ifndef BSTNODE_H
#define BSTNODE_H
class Node
{
public:
    int value = 0;
    Node *right;
    Node *left;
    Node(){left = nullptr; right = nullptr;}
    Node(int num){value = num ; left = nullptr; right = nullptr;}
    ~Node(){}
};

#endif
