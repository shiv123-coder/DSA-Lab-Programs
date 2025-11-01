#include <iostream>
#include <map>
#include <string>

using namespace std;

class Dictionary 
{
	private:
		map<string, string> hashTable; // Using map instead of unordered_map

	public:
		void insert (const string &key ,const string &value )
		{
			if (hashTable.find(key) != hashTable.end()) 
			{
				cout << "Key '" << key << "' already exists. Updating its value.\n";
			}
			hashTable[key] = value ;
			cout << "Inserted/Updated: (" << key << ", " << value << ")\n";
		}
		
		void find (const string &key)
		{
			if (hashTable.find(key) != hashTable.end())
			{
				cout <<"Found:("<<key<<","<<hashTable[key]<<")\n";
			}
			else
			{
				cout << "'Key " << key << "' not found.\n";
			}
		}
		
		void remove (const string &key)
		{
			if (hashTable.erase(key))
			{
				cout << "Key '" << key << "' deleted successfully.\n";
			}
			else
			{
				cout << "Key '" << key << "' not found.\n";
			}
		}
		
		void display()
		{
			if (hashTable.empty()) 
			{
				cout << "The dictionary is empty.\n";
			} 
			else 
			{
				cout << "Current dictionary contents:\n";
				
				for (map<string, string>::iterator it = hashTable.begin(); it != hashTable.end(); ++it) 
				{
					cout << "(" << it->first << ", " << it->second << ")\n";
				}
			}
		}
};	

int main ()
{
	Dictionary dict ;
	int choice ;	
	string key , value ;
	
	do {
		cout << "\n Dictionary Operations : \n";
		cout << "1. Insert\n";
		cout << "2. Find\n";
		cout << "3. Delete\n";
		cout << "4. Display\n";
		cout << "5. Exit\n";	
		
		cout << "Enter your choice: ";
		cin >> choice ;
		
		switch (choice)
		{
			case 1:
				cout << "Enter Key: ";
				cin >> key ;
				cout << "Enter Value: ";
				cin >> value ;
				dict.insert(key, value);
				break;
				
			case 2 :
				cout << "Enter key to find: ";
				cin >> key ;
				dict.find(key);
				break;
			
			case 3 :
				cout << "Enter key to delete: ";
				cin >> key ;
				dict.remove(key);
				break;
					
			case 4:
				dict.display();
				break;
			
			case 5:
				cout << "Exiting program.\n";
				break;
	
			default:
				cout << "Invalid choice. Please try again.\n";
		}
	} while (choice != 5);
	
	return 0;
}

