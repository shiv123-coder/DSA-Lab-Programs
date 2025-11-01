#include <iostream>
#include <string>

#define N 20  // Maximum size of the queue

#define SERIOUS 10
#define NONSERIOUS 5
#define CHECKUP 1

using namespace std;

struct Patient 
{
    string name;
    int priority;
};

// Priority Queue implementation
class PriorityQueue 
{
private:
    Patient Q[N];  // Array to store patient data
    int front, rear;

public:
    PriorityQueue() 
	{
        front = rear = -1;
    }

    bool isEmpty() 
	{
        return front == -1;
    }

    bool isFull() 
	{
        return (rear == N - 1);
    }

    void enqueue(string name, int priority) 
	{
        if (isFull()) 
		{
            cout << "Queue is full! Cannot add more patients.\n";
            return;
        }

        // If queue is empty
        if (isEmpty()) 
		{
            front = rear = 0;
            Q[rear] = {name, priority};
        } 
		else 
		{
            // Insert based on priority
            int i;
            for (i = rear; i >= front && Q[i].priority < priority; i--) 
			{
                Q[i + 1] = Q[i];  // Shift elements
            }
            Q[i + 1] = {name, priority};
            rear++;
        }
    }

    void dequeue() 
	{
        if (isEmpty()) 
		{
            cout << "Queue is empty! No patients to serve.\n";
            return;
        }

        cout << "Serving Patient: " << Q[front].name << " (Priority: ";
        switch (Q[front].priority) 
		{
            case SERIOUS: cout << "Serious"; break;
            case NONSERIOUS: cout << "Non-serious"; break;
            case CHECKUP: cout << "General Checkup"; break;
            default: cout << "Unknown"; break;
        }
        cout << ")\n";

        // If only one patient in the queue
        if (front == rear) 
		{
            front = rear = -1;
        } 
		else 
		{
            front++;
        }
    }

    void display() 
	{
        if (isEmpty()) 
		{
            cout << "No patients in queue.\n";
            return;
        }
        cout << "\nPatient Queue (Higher priority first):\n";
        for (int i = front; i <= rear; i++) 
		{
            cout << Q[i].name << " - ";
            switch (Q[i].priority) 
			{
                case SERIOUS: cout << "Serious"; break;
                case NONSERIOUS: cout << "Non-serious"; break;
                case CHECKUP: cout << "General Checkup"; break;
                default: cout << "Unknown"; break;
            }
            cout << endl;
        }
    }
};

int main() 
{
    PriorityQueue pq;
    int choice, priority;
    string name;

    do {
        cout << "\nHospital Priority Queue System\n";
        cout << "1. Add Patient\n";
        cout << "2. Serve Patient\n";
        cout << "3. Display Patients\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
		{
            case 1:
                cout << "Enter patient name: ";
                cin.ignore();
                getline(cin, name);
                do 
				{
                    cout << "Enter priority (0: Serious, 1: Non-serious, 2: General Checkup): ";
                    cin >> priority;
                } while (priority < 0 || priority > 2);

                switch (priority) 
				{
                    case 0: pq.enqueue(name, SERIOUS); break;
                    case 1: pq.enqueue(name, NONSERIOUS); break;
                    case 2: pq.enqueue(name, CHECKUP); break;
                }
                break;
            
            case 2:
                pq.dequeue();
                break;

            case 3:
                pq.display();
                break;

            case 0:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 0);

    return 0;
}

