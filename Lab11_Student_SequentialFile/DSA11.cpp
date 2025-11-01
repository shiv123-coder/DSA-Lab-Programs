#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

class student {
    typedef struct stud {
        int roll;
        char name[10];
        char div;
        char add[10];
    } stud;

    stud rec;

public:
    void create();
    void display();
    int search();
    void Delete();
};

void student::create() {
    char ans;
    ofstream fout;
    fout.open("stud.dat", ios::out | ios::binary);
    do {
        cout << "\n---------------------------------------------";
        cout << "\n\tEnter Roll No of Student    : ";
        cin >> rec.roll;
        cout << "\tEnter Name of Student        : ";
        cin >> rec.name;
        cout << "\tEnter Division of Student    : ";
        cin >> rec.div;
        cout << "\tEnter Address of Student     : ";
        cin >> rec.add;

        fout.write((char*)&rec, sizeof(stud)) << flush;

        cout << "\n---------------------------------------------";
        cout << "\n\tDo You Want to Add More Records (y/n)? : ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    fout.close();
    cout << "\n\n\tRecords Added Successfully!\n";
}

void student::display() {
    ifstream fin;
    fin.open("stud.dat", ios::in | ios::binary);
    fin.seekg(0, ios::beg);

    cout << "\n===============================================";
    cout << "\n\t\tStudent Records";
    cout << "\n-----------------------------------------------";
    cout << "\n\tRoll\tName\tDivision\tAddress";
    cout << "\n-----------------------------------------------";

    while (fin.read((char*)&rec, sizeof(stud))) {
        if (rec.roll != -1) {
            cout << "\n\t" << rec.roll
                 << "\t" << rec.name
                 << "\t" << rec.div
                 << "\t\t" << rec.add;
        }
    }
    cout << "\n-----------------------------------------------";
    fin.close();
}

int student::search() {
    int r, i = 0;
    ifstream fin;
    fin.open("stud.dat", ios::in | ios::binary);
    fin.seekg(0, ios::beg);

    cout << "\n---------------------------------------------";
    cout << "\n\tEnter Roll No to Search: ";
    cin >> r;

    while (fin.read((char*)&rec, sizeof(stud))) {
        if (rec.roll == r) {
            cout << "\n\n\tRecord Found!";
            cout << "\n-----------------------------------------------";
            cout << "\n\tRoll\tName\tDivision\tAddress";
            cout << "\n-----------------------------------------------";
            cout << "\n\t" << rec.roll
                 << "\t" << rec.name
                 << "\t" << rec.div
                 << "\t\t" << rec.add;
            cout << "\n-----------------------------------------------";
            fin.close();
            return i;
        }
        i++;
    }
    fin.close();
    cout << "\n\n\tRecord Not Found!";
    return 0;
}

void student::Delete() {
    int pos;
    pos = search();
    fstream f;
    f.open("stud.dat", ios::in | ios::out | ios::binary);
    f.seekg(0, ios::beg);

    if (pos == 0) {
        cout << "\n\tRecord Not Found!";
        f.close();
        return;
    }

    int offset = pos * sizeof(stud);
    f.seekp(offset);

    rec.roll = -1;
    strcpy(rec.name, "NULL");
    rec.div = 'N';
    strcpy(rec.add, "NULL");

    f.write((char*)&rec, sizeof(stud));
    f.seekg(0);
    f.close();
    cout << "\n\n\tRecord Deleted Successfully!";
}

int main() {
    student obj;
    int ch, key;
    char ans;

    do {
        cout << "\n\n===============================================";
        cout << "\n\tStudent Information System";
        cout << "\n===============================================";
        cout << "\n\t1. Create Record";
        cout << "\n\t2. Display Records";
        cout << "\n\t3. Delete Record";
        cout << "\n\t4. Search Record";
        cout << "\n\t5. Exit";
        cout << "\n===============================================";
        cout << "\n\n\tEnter Your Choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                obj.create();
                break;
            case 2:
                obj.display();
                break;
            case 3:
                obj.Delete();
                break;
            case 4:
                key = obj.search();
                break;
            case 5:
                cout << "\n\n\tExiting... Goodbye!";
                break;
            default:
                cout << "\n\tInvalid Choice! Please Try Again.";
        }

        if (ch != 5) {
            cout << "\n\n\tDo You Want to Continue? (y/n): ";
            cin >> ans;
        } else {
            ans = 'n';
        }
    } while (ans == 'y' || ans == 'Y');

    return 0;
}

