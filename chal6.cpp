#include <iostream>
#include <vector>

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

class BST
{
public:
    BST(){ root = nullptr;}
    ~BST(){ deleteBST(root);}
    void insertKey(int newKey);
    bool hasKey(int searchKey);
    std::vector<int> inOrder();
    int getHeight(){ return traverseHeight(root);}
    void balance();
    void removeKey(int oldKey);
private:
    Node* root;
    std::vector<int> orderedTree;
    int traverseHeight(Node* node);
    void traverseInOrder(Node* node);
    void traverseInsert(int num, Node* node);
    bool traverseSearch(int num, Node* node);
    void deleteBST(Node* node);
};

void BST::removeKey(int oldKey)
{
    if(!hasKey(oldKey))
    {
        std::cout << "Key not found" << std::endl;
        return;
    }

    for(int i = 0 ; i < orderedTree.size(); i++)
    {
        if(orderedTree.at(i) == oldKey)
        {
            orderedTree.erase(orderedTree.begin()+i);
            break;
        }
    }
    balance();
}
void BST::balance()
{
    int mid = (orderedTree.size()-1)/2;
    Node* newRoot = new Node(orderedTree.at(mid));

    for(int i = mid ; i >= 0 ; i--)
    {
        if(orderedTree.at(i) == orderedTree.at(mid))
        {
            continue;
        }
        traverseInsert(orderedTree.at(i), newRoot);
    }
    for(int i = mid ; i < orderedTree.size() ; i++)
    {
        if(orderedTree.at(i) == orderedTree.at(mid))
        {
            continue;
        }
        traverseInsert(orderedTree.at(i), newRoot);
    }
    root = newRoot;
}
void BST::deleteBST(Node* node)
{
    if(node == nullptr)
    {
        return;
    }

    deleteBST(node->left);
    deleteBST(node->right);

    delete node;
}

int BST::traverseHeight(Node* node)
{
    if(node == nullptr)
    {
        return 0;
    }

    int leftHeight = traverseHeight(node->left);
    int rightHeight = traverseHeight(node->right);
    return (leftHeight<rightHeight) ? rightHeight+1 : leftHeight+1;
}

bool BST::traverseSearch(int num, Node* node)
{
    if(node == nullptr) return false;

    if(num == node->value) return true;

    if(num > node->value){ return traverseSearch(num, node->right);}
    else if(num < node->value){ return traverseSearch(num, node->left);}
    
    return false;
}

bool BST::hasKey(int searchKey)
{
    if(root == nullptr) return false;

    return traverseSearch(searchKey,root);
}

void BST::traverseInsert(int num, Node* node) 
{
    if(node->right == nullptr)
    {
        if(num > node->value)
        {
            node->right = new Node(num);
            return;
        }
    }
    if(node->left == nullptr)
    {
        if(num < node->value)
        {
            node->left = new Node(num);
            return;
        }
    }

    if(num > node->value){ traverseInsert(num, node->right);}
    else if(num < node->value){ traverseInsert(num, node->left);} 
}

void BST::insertKey(int newKey)
{
    if(root == nullptr)
    {
        root = new Node(newKey);
        return;
    }
    traverseInsert(newKey,root); 
}

void BST::traverseInOrder(Node* node)
{
    if(node == nullptr)
    {
        orderedTree.push_back(node->value);
        return;
    }

    if(node->left != nullptr){ traverseInOrder(node->left);}

    orderedTree.push_back(node->value);
 
    if(node->right != nullptr){ traverseInOrder(node->right);}
}
std::vector<int> BST::inOrder()
{
    if(root == nullptr)
    {
        return orderedTree;
    }
    traverseInOrder(root);
    return orderedTree;
}

int main()
{
    std::cout << "Enter the numbers to be stored (end with a letter): " << std::endl;

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

    int searchNum;
    std::string isFound = "no";
    
    std::cout << "Which number do you want to look up? " << std::endl;
    std::cin >> searchNum;
    if(tree.hasKey(searchNum))
    {
       isFound = "yes";
    }
    std::cout << searchNum << " is in the tree: "<< isFound << std::endl;

    std::vector<int> orderedTree = tree.inOrder();
    std::cout << "The numbers in sorted order: ";

    for(int i = 0 ; i < orderedTree.size(); i++)
    {
        std::cout << orderedTree.at(i) << " "; 
    }
    std::cout << std::endl;
    std::cout << "Height of the tree: "<< tree.getHeight();

    tree.balance();
    tree.removeKey(4);
}