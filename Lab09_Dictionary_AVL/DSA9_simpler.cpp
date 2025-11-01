#include <iostream>
#include <string>
using namespace std;

// Node structure for the AVL Tree
struct Node {
    string keyword, meaning;
    Node* left;
    Node* right;
    int height;
};

// Function to get the height of a node
int getHeight(Node* node) {
    return (node == NULL) ? 0 : node->height;
}

// Function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to create a new node
Node* createNode(string keyword, string meaning) {
    Node* newNode = new Node;
    newNode->keyword = keyword;
    newNode->meaning = meaning;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1; // New node is initially at height 1
    return newNode;
}

// Function to update the height of a node
void updateHeight(Node* node) {
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

// Function to get balance factor of a node
int getBalance(Node* node) {
    return (node == NULL) ? 0 : getHeight(node->left) - getHeight(node->right);
}

// Right rotate
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Left rotate
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Balance a node
Node* balance(Node* node) {
    updateHeight(node);
    int balanceFactor = getBalance(node);

    // Left Heavy
    if (balanceFactor > 1) {
        if (getBalance(node->left) < 0)
            node->left = rotateLeft(node->left); // Left-Right Case
        return rotateRight(node); // Left-Left Case
    }

    // Right Heavy
    if (balanceFactor < -1) {
        if (getBalance(node->right) > 0)
            node->right = rotateRight(node->right); // Right-Left Case
        return rotateLeft(node); // Right-Right Case
    }

    return node; // Already balanced
}

// Insert a new keyword
Node* insert(Node* root, string keyword, string meaning) {
    if (root == NULL)
        return createNode(keyword, meaning);

    if (keyword < root->keyword)
        root->left = insert(root->left, keyword, meaning);
    else if (keyword > root->keyword)
        root->right = insert(root->right, keyword, meaning);
    else {
        // Keyword already exists, update meaning
        root->meaning = meaning;
        return root;
    }

    return balance(root);
}

// Find node with minimum keyword (used in delete)
Node* findMin(Node* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

// Delete a keyword
Node* deleteNode(Node* root, string keyword) {
    if (root == NULL)
        return NULL;

    if (keyword < root->keyword)
        root->left = deleteNode(root->left, keyword);
    else if (keyword > root->keyword)
        root->right = deleteNode(root->right, keyword);
    else {
        // Found node to delete
        if (root->left == NULL || root->right == NULL) {
            Node* temp = (root->left != NULL) ? root->left : root->right;
            delete root;
            return temp;
        } else {
            // Node with two children
            Node* temp = findMin(root->right);
            root->keyword = temp->keyword;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->keyword);
        }
    }

    return balance(root);
}

// Search a keyword and count comparisons
int search(Node* root, string keyword, int count = 0) {
    if (root == NULL)
        return count;

    count++;
    if (keyword == root->keyword)
        return count;
    else if (keyword < root->keyword)
        return search(root->left, keyword, count);
    else
        return search(root->right, keyword, count);
}

// Update the meaning of a keyword
void updateMeaning(Node* root, string keyword, string newMeaning) {
    if (root == NULL) {
        cout << "Keyword not found!" << endl;
        return;
    }

    if (keyword < root->keyword)
        updateMeaning(root->left, keyword, newMeaning);
    else if (keyword > root->keyword)
        updateMeaning(root->right, keyword, newMeaning);
    else
        root->meaning = newMeaning;
}

// Display dictionary in ascending order
void displayAscending(Node* root) {
    if (root != NULL) {
        displayAscending(root->left);
        cout << root->keyword << " : " << root->meaning << endl;
        displayAscending(root->right);
    }
}

// Display dictionary in descending order
void displayDescending(Node* root) {
    if (root != NULL) {
        displayDescending(root->right);
        cout << root->keyword << " : " << root->meaning << endl;
        displayDescending(root->left);
    }
}

// Main function with menu
int main() {
    Node* root = NULL;
    int choice;
    string keyword, meaning;

    do {
        cout << "\n--- Dictionary Menu ---\n";
        cout << "1. Insert\n2. Delete\n3. Update Meaning\n4. Display Ascending\n";
        cout << "5. Display Descending\n6. Search\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To clear the newline

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                cin >> keyword;
                cin.ignore();
                cout << "Enter meaning: ";
                getline(cin, meaning);
                root = insert(root, keyword, meaning);
                break;

            case 2:
                cout << "Enter keyword to delete: ";
                cin >> keyword;
                root = deleteNode(root, keyword);
                break;

            case 3:
                cout << "Enter keyword to update: ";
                cin >> keyword;
                cin.ignore();
                cout << "Enter new meaning: ";
                getline(cin, meaning);
                updateMeaning(root, keyword, meaning);
                break;

            case 4:
                cout << "\nDictionary in Ascending Order:\n";
                displayAscending(root);
                break;

            case 5:
                cout << "\nDictionary in Descending Order:\n";
                displayDescending(root);
                break;

            case 6:
                cout << "Enter keyword to search: ";
                cin >> keyword;
                cout << "Comparisons required: " << search(root, keyword) << endl;
                break;

            case 7:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 7);

    return 0;
}

