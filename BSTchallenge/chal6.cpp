#include <iostream>
#include <vector>

class Node
{
public:
    int value = 0;
    Node *right;
    Node *left;
    Node()
    {
        left = nullptr;
        right = nullptr;
    }
    Node(int num)
    {
        value = num;
        left = nullptr;
        right = nullptr;
    }
    ~Node() {}
};

class BST
{
public:
    BST() { root = nullptr;}
    ~BST()
    {
        deleteBST(root); 
    }
    void insertKey(int newKey);
    bool hasKey(int searchKey);
    std::vector<int> inOrder();
    int getHeight() { return traverseHeight(root); }
    void balance();
    void removeKey(int oldKey);
private:
    Node *root;
    std::vector<int> orderedTree;
    int traverseHeight(Node *node);
    void traverseInOrder(Node *node);
    void traverseInsert(int num, Node *node);
    bool traverseSearch(int num, Node *node);
    void deleteBST(Node *node);

    void sorter(Node* node,int lowVal, int highVal);
    void leftSort(Node* node,int lowVal, int highVal);
    void rightSort(Node* node,int lowVal, int highVal);
    void left(Node* node,int lowVal, int highVal);
    void right(Node* node,int lowVal, int highVal);
};
void BST::removeKey(int oldKey)
{
    if (!hasKey(oldKey))
    {
        orderedTree.clear();
        return;
    }

    for (int i = 0; i < orderedTree.size(); i++)
    {
        if (orderedTree.at(i) == oldKey)
        {
            orderedTree.erase(orderedTree.begin() + i);
            break;
        }
    }
    balance();
}
void BST::sorter(Node* node, int lowVal, int highVal)
{
    int mid = (lowVal+highVal)/2;
    traverseInsert(orderedTree.at(mid), node);
    int leftMid = (lowVal+mid)/2 ;
    int rightMid = (mid+highVal)/2;
    traverseInsert(orderedTree.at(leftMid),node);
    traverseInsert(orderedTree.at(rightMid), node);
}

void BST::leftSort(Node* node,int lowVal, int highVal)
{
    sorter(node, lowVal,highVal);
    int mid = (lowVal+highVal)/2;
    if(mid == 0 || lowVal == highVal) return;
    leftSort(node,lowVal,mid);
}
void BST::rightSort(Node* node,int lowVal, int highVal)
{
    int mid = (lowVal+highVal)/2;
    if(mid == lowVal) return;
    sorter(node, lowVal,highVal);
    rightSort(node,mid,highVal);
}
void BST::left(Node* node, int lowVal, int highVal)
{
    rightSort(node, lowVal, highVal);
    leftSort(node, lowVal, highVal);
}
void BST::right(Node* node, int lowVal, int highVal)
{
    leftSort(node, lowVal, highVal);
    rightSort(node, lowVal, highVal);
}
void BST::balance()
{
    int mid = orderedTree.size() / 2;
    deleteBST(root);
    root = new Node(orderedTree.at(mid));
   
    left(root, 0, orderedTree.size()/2);
    right(root,orderedTree.size()/2, orderedTree.size());
    
    orderedTree.clear();
}
void BST::deleteBST(Node *node)
{
    if (node == nullptr)
    {
        return;
    }

    deleteBST(node->left);
    deleteBST(node->right);

    delete node;
}

int BST::traverseHeight(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }

    int leftHeight = traverseHeight(node->left);
    int rightHeight = traverseHeight(node->right);
    return (leftHeight < rightHeight) ? rightHeight + 1 : leftHeight + 1;
}

bool BST::traverseSearch(int num, Node *node)
{
    if (node == nullptr)
        return false;

    if (num == node->value)
        return true;

    if (num > node->value)
    {
        return traverseSearch(num, node->right);
    }
    else if (num < node->value)
    {
        return traverseSearch(num, node->left);
    }

    return false;
}

bool BST::hasKey(int searchKey)
{
    if (root == nullptr)
        return false;

    return traverseSearch(searchKey, root);
}

void BST::traverseInsert(int num, Node *node)
{
    if (node->right == nullptr)
    {
        if (num > node->value)
        {
            node->right = new Node(num);
            return;
        }
    }
    if (node->left == nullptr)
    {
        if (num < node->value)
        {
            node->left = new Node(num);
            return;
        }
    }

    if (num > node->value)
    {
        traverseInsert(num, node->right);
    }
    else if (num < node->value)
    {
        traverseInsert(num, node->left);
    }
}

void BST::insertKey(int newKey)
{
    if (root == nullptr)
    {
        root = new Node(newKey);
        return;
    }
    traverseInsert(newKey, root);
}

void BST::traverseInOrder(Node *node)
{
    if (node == nullptr)
    {
        orderedTree.push_back(node->value);
        return;
    }

    if (node->left != nullptr)
    {
        traverseInOrder(node->left);
    }

    orderedTree.push_back(node->value);

    if (node->right != nullptr)
    {
        traverseInOrder(node->right);
    }
}
std::vector<int> BST::inOrder()
{
    if (root == nullptr)
    {
        return orderedTree;
    }
    traverseInOrder(root);
    return orderedTree;
}
void print(BST &tree)
{
    std::vector<int> inOrder = tree.inOrder();
    std::cout << "The numbers in sorted order: ";
    for (int i = 0; i < inOrder.size(); i++)
    {
        std::cout << inOrder.at(i) << ' ';
    }
    std::cout << std::endl;
    std::cout << "Height of the tree: " << tree.getHeight() << std::endl;
}
int main()
{
    BST tree;
    for (int i = 0; i < 17; i++)
    {
        tree.insertKey(i + 1);
    }
    print(tree);
    tree.balance();
    print(tree);
    tree.removeKey(42);
    print(tree);
    tree.removeKey(6);
    print(tree);
    tree.removeKey(2);
    print(tree);
    return 0;
}