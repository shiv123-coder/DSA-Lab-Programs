#include <iostream>
#include <fstream>
#include <map>
using namespace std;

struct Employee {
    int id;
    char name[30];
    char designation[30];
    float salary;
};

// Global index (in-memory)
map<int, streampos> indexMap;

void buildIndex() {
    indexMap.clear();
    ifstream file("employee.dat", ios::binary);
    Employee emp;
    streampos pos = file.tellg();
    while (file.read((char*)&emp, sizeof(emp))) {
        indexMap[emp.id] = pos;
        pos = file.tellg();
    }
    file.close();
}

void addEmployee() {
    ofstream file("employee.dat", ios::binary | ios::app);
    Employee emp;

    cout << "Enter ID: ";
    cin >> emp.id;
    cout << "Enter Name: ";
    cin.ignore();
    cin.getline(emp.name, 30);
    cout << "Enter Designation: ";
    cin.getline(emp.designation, 30);
    cout << "Enter Salary: ";
    cin >> emp.salary;

    file.write((char*)&emp, sizeof(emp));
    file.close();

    buildIndex(); // Rebuild index after adding
    cout << "Employee added.\n";
}

void displayEmployee() {
    int searchId;
    cout << "Enter Employee ID to search: ";
    cin >> searchId;

    buildIndex(); // Ensure index is current

    if (indexMap.find(searchId) == indexMap.end()) {
        cout << "Employee not found.\n";
        return;
    }

    ifstream file("employee.dat", ios::binary);
    file.seekg(indexMap[searchId]);
    Employee emp;
    file.read((char*)&emp, sizeof(emp));
    file.close();

    cout << "Employee Details:\n";
    cout << "ID: " << emp.id << "\n";
    cout << "Name: " << emp.name << "\n";
    cout << "Designation: " << emp.designation << "\n";
    cout << "Salary: " << emp.salary << "\n";
}

void deleteEmployee() {
    int deleteId;
    cout << "Enter Employee ID to delete: ";
    cin >> deleteId;

    buildIndex();
    if (indexMap.find(deleteId) == indexMap.end()) {
        cout << "Employee not found.\n";
        return;
    }

    ifstream infile("employee.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);
    Employee emp;

    while (infile.read((char*)&emp, sizeof(emp))) {
        if (emp.id != deleteId)
            temp.write((char*)&emp, sizeof(emp));
    }

    infile.close();
    temp.close();
    remove("employee.dat");
    rename("temp.dat", "employee.dat");

    buildIndex();
    cout << "Employee deleted.\n";
}

int main() {
    int choice;
    buildIndex(); // Initial index build

    do {
        cout << "\n--- Employee Management ---\n";
        cout << "1. Add Employee\n";
        cout << "2. Delete Employee\n";
        cout << "3. Display Employee\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                deleteEmployee();
                break;
            case 3:
                displayEmployee();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}

