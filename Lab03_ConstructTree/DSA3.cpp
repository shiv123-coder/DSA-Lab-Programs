#include <iostream>
#include <string.h>
using namespace std;

struct node // Node Declaration
{
    string label;
    int ch_count;            // Number of children (chapters or sections)
    struct node *child[10];  // Child nodes (sections or subsections)
    int sub_count;           // Number of subsections (for section nodes)
} * root;

class GT // Class Declaration
{
public:
    void create_tree();
    void display(node *r1);

    GT()
    {
        root = NULL;  // Explicitly initializing root to NULL
    }
};

// Function definitions outside the class

void GT::create_tree()
{
    int tchapters, tsections, tsubsections, i, j, k;

    root = new node;
    cout << "Enter name of book: ";
    cin.get();  // To handle any leftover newline
    getline(cin, root->label);  // C++98 compatible method for reading full line

    cout << "Enter number of chapters in book: ";
    cin >> tchapters;
    cin.get();  // Consume the newline character after integer input
    root->ch_count = tchapters;

    for (i = 0; i < tchapters; i++)
    {
        root->child[i] = new node;
        cout << "Enter the name of Chapter " << i + 1 << ": ";
        getline(cin, root->child[i]->label);  // C++98 compatible method for reading full line

        cout << "Enter number of sections in Chapter " << root->child[i]->label << ": ";
        cin >> tsections;
        cin.get();  // Consume the newline character after integer input
        root->child[i]->ch_count = tsections;

        for (j = 0; j < tsections; j++)
        {
            root->child[i]->child[j] = new node;
            cout << "Enter Name of Section " << j + 1 << " in Chapter " << root->child[i]->label << ": ";
            getline(cin, root->child[i]->child[j]->label);  // C++98 compatible method for reading full line

            cout << "Enter number of subsections in Section " << root->child[i]->child[j]->label << ": ";
            cin >> tsubsections;
            cin.get();  // Consume the newline character after integer input
            root->child[i]->child[j]->sub_count = tsubsections;

            for (k = 0; k < tsubsections; k++)
            {
                root->child[i]->child[j]->child[k] = new node;
                cout << "Enter Name of Subsection " << k + 1 << " in Section " << root->child[i]->child[j]->label << ": ";
                getline(cin, root->child[i]->child[j]->child[k]->label);  // C++98 compatible method for reading full line
            }
        }
    }
}

void GT::display(node *r1)
{
    int i, j, k;

    if (r1 != NULL)
    {
        cout << "\n-----Book Hierarchy-----";
        cout << "\nBook Title: " << r1->label;
        int tchapters = r1->ch_count;

        for (i = 0; i < tchapters; i++)
        {
            cout << "\nChapter " << i + 1 << ": " << r1->child[i]->label;
            int tsections = r1->child[i]->ch_count;

            for (j = 0; j < tsections; j++)
            {
                cout << "\n  Section " << j + 1 << ": " << r1->child[i]->child[j]->label;
                int tsubsections = r1->child[i]->child[j]->sub_count;

                for (k = 0; k < tsubsections; k++)
                {
                    cout << "\n    Subsection " << k + 1 << ": " << r1->child[i]->child[j]->child[k]->label;
                }
            }
        }
    }
    cout << endl;
}

int main()
{
    int choice;
    GT gt;

    while (1)
    {
        cout << "------------------\n";
        cout << "Book Tree Creation\n";
        cout << "------------------\n";
        cout << "1. Create\n";
        cout << "2. Display\n";
        cout << "3. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.get();  // Consume the newline character after integer input

        switch (choice)
        {
        case 1:
            gt.create_tree();
            break;

        case 2:
            gt.display(root);
            break;

        case 3:
            cout << "Thanks for using this program!!!";
            exit(1);
            break;

        default:
            cout << "Wrong choice!!!" << endl;
        }
    }
    return 0;
}

