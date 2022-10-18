#include <iostream>
#include <vector>


class Node
{
    public:
        Node(int num){this->value = num;}
        void insertLeft(Node* nextLoc);
        void insertRight(Node* nextLoc);
        int value;
        Node* right;
        Node* left;
};

void Node::insertLeft(Node* nextLoc)
{
    this->left = nextLoc->left;
}
void Node::insertRight(Node* nextLoc)
{
    this->right = nextLoc->right;
}

class BST{
    public:
        BST();
        ~BST();
        void insertKey(int newKey);
        bool hasKey(int searchKey);
        std::vector<int> inOrder();
        int getHeight();
    private:
        int root; 
        Node node;
        Node* headObj;
        Node* right;
        Node* left;
};

BST::BST()
{
    node.value = 0;
    node.right = nullptr;
    node.left = nullptr;
}
BST::~BST(){}

void BST::insertKey(int newKey)
{
    if(headObj == nullptr)
    {
        
    }

    if(newKey > headObj->value) // right
    {

    }
    else if(newKey < headObj->value) //left
    {

    }
}

int main()
{
    int num;
    BST tree;
    std::cin >> num;
    while(!std::cin.fail())
    {
        tree.insertKey(num);
        std::cin >> num;
    }

}