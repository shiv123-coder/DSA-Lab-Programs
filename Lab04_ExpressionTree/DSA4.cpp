#include <iostream>
#include <cstring>  // Use <cstring> for string functions in C++98
using namespace std;

struct node 
{
    char data;
    node *left;
    node *right;
};

class tree 
{
    char prefix[20];
    
public:
    node *root; // Renamed top to root to avoid conflict with stack

    void expression(char[]);
    void display(node *);
    void non_rec_postorder(node *);
    void del(node *);
};

class stack1 
{
    node *data[30];
    int top;
    
public:

    stack1() 
	{
        top = -1;  // Initialize stack top to -1.
    }

    int empty() 
	{
        return top == -1;
    }

    void push(node *p) 
	{
        if (top < 29) 
		{
            data[++top] = p;
        }
    }

    node* pop() 
	{
        if (top >= 0) 
		{
            return data[top--];
        }
        return NULL; // Use NULL instead of nullptr in C++98
    }
};

void tree::expression(char prefix[]) 
{
    char c;
    stack1 s;
    node *t1, *t2;
    int len = strlen(prefix);

    for (int i = len - 1; i >= 0; i--) 
	{
        node *top = new node; // Local variable, so no conflict with class member root
        top->left = NULL;
        top->right = NULL;

        if (isalpha(prefix[i])) 
		{
            top->data = prefix[i];
            s.push(top);
        } 
		else if (prefix[i] == '+' || prefix[i] == '-' || prefix[i] == '*' || prefix[i] == '/') 
		{
            t1 = s.pop();
            t2 = s.pop();
            top->data = prefix[i];
            top->left = t1;
            top->right = t2;
            s.push(top);
        }
    }

    root = s.pop();  // Set the root of the expression tree to the last node in the stack.
}

void tree::display(node *root) {
    if (root == NULL) return;

    display(root->left);
    cout << root->data << " ";
    display(root->right);
}

void tree::non_rec_postorder(node *root) 
{
    if (root == NULL) return;

    stack1 s1, s2;
    s1.push(root);

    while (!s1.empty()) 
	{
        node *t = s1.pop();
        s2.push(t);

        if (t->left != NULL) 
			s1.push(t->left);
        if (t->right != NULL) 
			s1.push(t->right);
    }

    while (!s2.empty()) 
	{
        node *t = s2.pop();
        cout << t->data << " ";
    }
}

void tree::del(node *root) 
{
    if (root == NULL) return;

    del(root->left);
    del(root->right);

    cout << "Deleting node: " << root->data << endl;
    delete root;  // Delete the node.
}

int main() 
{
    char expr[20];
    tree t;

    cout << "Enter prefix Expression: ";
    cin >> expr;
    cout << "Prefix Expression is : " ;
    cout << expr << endl;

    t.expression(expr);

    cout << "Postorder Traversal: ";
    t.non_rec_postorder(t.root); // Use root instead of top
    cout << endl;

    t.del(t.root); // Use root instead of top
    return 0;
}

