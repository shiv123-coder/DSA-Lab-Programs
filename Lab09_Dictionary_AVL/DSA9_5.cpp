#include <iostream>
#include <string>
using namespace std;

// Node structure for BST and AVL Tree
struct Node {
    string key, meaning;
    Node* left, * right;
    int height; // Used only for AVL Tree
};

// Utility functions
int height(Node* node) 
{
    if (node == NULL) 
    {
        return 0;
    }
    return node->height;
}

int maxVal(int a, int b) 
{
    if (a > b) 
    {
        return a;
    } 
    else 
    {
        return b;
    }
}

Node* createNode(string key, string meaning) 
{
    Node* node = new Node;
    node->key = key;
    node->meaning = meaning;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

// AVL rotations and balancing
int getBalance(Node* node) 
{
    if (node == NULL) 
    {
        return 0;
    }
    return height(node->left) - height(node->right);
}

Node* rotateRight(Node* y) 
{
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    y->height = maxVal(height(y->left), height(y->right)) + 1;
    x->height = maxVal(height(x->left), height(x->right)) + 1;
    return x;
}

Node* rotateLeft(Node* x) 
{
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    x->height = maxVal(height(x->left), height(x->right)) + 1;
    y->height = maxVal(height(y->left), height(y->right)) + 1;
    return y;
}

Node* balance(Node* node) 
{
    int bf = getBalance(node);
    
    if (bf > 1 && getBalance(node->left) >= 0) 
    {
        return rotateRight(node);
    }
    
    if (bf > 1 && getBalance(node->left) < 0) 
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    
    if (bf < -1 && getBalance(node->right) <= 0) 
    {
        return rotateLeft(node);
    }
    
    if (bf < -1 && getBalance(node->right) > 0) 
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Insert function for BST and AVL
Node* insert(Node* root, string key, string meaning, bool useAVL) 
{
    if (!root) 
    {
        return createNode(key, meaning);
    }
    
    if (key < root->key) 
    {
        root->left = insert(root->left, key, meaning, useAVL);
    } 
    else if (key > root->key) 
    {
        root->right = insert(root->right, key, meaning, useAVL);
    } 
    else 
    {
        cout << "Keyword already exists.\n";
        return root;
    }

    root->height = 1 + maxVal(height(root->left), height(root->right));

    if (useAVL) 
    {
        return balance(root);
    } 
    else 
    {
        return root;
    }
}

// Delete node
Node* findMin(Node* root) 
{
    while (root->left) 
    {
        root = root->left;
    }
    return root;
}

Node* deleteNode(Node* root, string key, bool useAVL) 
{
    if (!root) 
    {
        return NULL;
    }
    
    if (key < root->key) 
    {
        root->left = deleteNode(root->left, key, useAVL);
    } 
    else if (key > root->key) 
    {
        root->right = deleteNode(root->right, key, useAVL);
    } 
    else 
    {
        if (!root->left) 
        {
            Node* temp = root->right;
            delete root;
            return temp;
        } 
        else if (!root->right) 
        {
            Node* temp = root->left;
            delete root;
            return temp;
        } 
        else 
        {
            Node* temp = findMin(root->right);
            root->key = temp->key;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->key, useAVL);
        }
    }

    root->height = 1 + maxVal(height(root->left), height(root->right));

    if (useAVL) 
    {
        return balance(root);
    } 
    else 
    {
        return root;
    }
}

// Display in Ascending order
void displayAsc(Node* root) 
{
    if (!root) 
    {
        return;
    }
    
    displayAsc(root->left);
    cout << root->key << " : " << root->meaning << endl;
    displayAsc(root->right);
}

// Display in Descending order
void displayDesc(Node* root) 
{
    if (!root) 
    {
        return;
    }
    
    displayDesc(root->right);
    cout << root->key << " : " << root->meaning << endl;
    displayDesc(root->left);
}

// Search with comparison count
bool search(Node* root, string key, int& comparisons) 
{
    if (!root) 
    {
        return false;
    }
    
    comparisons++;
    
    if (key == root->key) 
    {
        return true;
    }
    
    if (key < root->key) 
    {
        return search(root->left, key, comparisons);
    } 
    else 
    {
        return search(root->right, key, comparisons);
    }
}

int main() 
{
    Node* root = NULL;
    bool useAVL;
    int choice;
    string key, meaning;

    cout << "Choose Tree Type:\n1. BST\n2. AVL Tree\nEnter choice: ";
    cin >> choice;
    cin.ignore();
    useAVL = (choice == 2);

    while (true) 
    {
        cout << "\n1. Add Keyword\n2. Delete Keyword\n3. Display Ascending\n4. Display Descending\n5. Search Keyword\n6. Show Max Comparisons\n7. Exit\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) 
        {
            cout << "Enter keyword: "; 
            getline(cin, key);
            cout << "Enter meaning: "; 
            getline(cin, meaning);
            root = insert(root, key, meaning, useAVL);
        } 
        else if (choice == 2) 
        {
            cout << "Enter keyword to delete: "; 
            getline(cin, key);
            root = deleteNode(root, key, useAVL);
        } 
        else if (choice == 3) 
        {
            cout << "\nDictionary (Ascending Order):\n";
            displayAsc(root);
        } 
        else if (choice == 4) 
        {
            cout << "\nDictionary (Descending Order):\n";
            displayDesc(root);
        } 
        else if (choice == 5) 
        {
            int comparisons = 0;
            cout << "Enter keyword to search: "; 
            getline(cin, key);
            if (search(root, key, comparisons)) 
            {
                cout << "Keyword found in " << comparisons << " comparisons.\n";
            } 
            else 
            {
                cout << "Keyword not found. Comparisons: " << comparisons << endl;
            }
        } 
        else if (choice == 6) 
        {
            cout << "Maximum comparisons (height of tree): " << height(root) << endl;
        } 
        else if (choice == 7) 
        {
            break;
        } 
        else 
        {
            cout << "Invalid choice.\n";
        }
    }
    
    return 0;
}

