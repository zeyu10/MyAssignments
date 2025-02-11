#include <iostream>
#include <string>

using namespace std;

// The first class contains the check function and pre operation management.
class Node {
private:
    string name;
    string phone;
    string email;

    // Function to check if name is available.
    bool isValidName(const string& name) {
        for (char c : name) {
            if (!isalpha(c)) return false;
        }
        return true;
    }

    // Function to check if phone is available.
    bool isValidPhone(const string& phone) {
        if (phone.length() != 10) return false;
        for (char c : phone) {
            if (!isdigit(c)) return false;
        }
        return true;
    }

    // Function to check if email is available.
    bool isValidEmail(const string& email) {
        int p0 = -1, p1 = -1;
        for (int i = 0; i < email.length(); i++) {
            if (email[i] == '@') p0 = i;
            if (email[i] == '.') p1 = i;
        }
        return p0 != -1 && p1 != -1 && p0 < p1 && p1 - p0 > 1;
    }

public:
    // Initialization
    Node() : name(""), phone(""), email("") {}

    // Uniformly implement output and check functions.
    void setContact() {
        while (true) {
            cout << "Enter name: ";
            cin >> name;
            if (isValidName(name)) break;
            cout << "  Invalid input." << endl;
            cout << "  Names should only contain alphabetic characters." << endl;
        }
        while (true) {
            cout << "Enter phone number: ";
            cin >> phone;
            if (isValidPhone(phone)) break;
            cout << "  Invalid input." << endl;
            cout << "  The phone number should only contain 10 digits." << endl;
        }
        while (true) {
            cout << "Enter email: ";
            cin >> email;
            if (isValidEmail(email)) break;
            cout << "  Invalid input." << endl;
            cout << "  The email address should contain '@' (at) and '.' (dot)." << endl;
        }
    }

    // Display single contact function.
    void displayContact() const {
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
        cout << "Email: " << email << endl;
        cout << "------------------------------" << endl << endl;
    }

    // Getter to name
    string getName() const {
        return name;
    }
};


// The second class implements contact information management.
class Manager {
private:
    // In order to add contacts without limit, dynamic arrays and pointers are used here.
    Node* node;
    int capacity;
    int length;

    // Expand capacity function increases the capacity of the Node array in the Manager class to store more contacts.
    void expCapacity() {
        // Check the current capacity, initializing it to 1 if it is zero.
        // Otherwise doubling the capacity to optimize memory allocation and avoid frequent array resizing operations.
        int newCapacity = capacity == 0 ? 1 : capacity * 2;

        // Temporarily store contact information.
        Node* temp = new Node[newCapacity];

        // Copy contents to temporary array.
        for (int i = 0; i < length; i++) {
            temp[i] = node[i];
        }

        // Release memory and reset data.
        delete[] node;
        node = temp;
        capacity = newCapacity;
    }

public:
    // Initialization
    Manager() : node(nullptr), capacity(0), length(0) {}

    // Add contact function.
    void addContact() {
        if (length == capacity) {
            expCapacity();
        }
        node[length].setContact();
        length++;
        cout << endl << "Contact added successfully!" << endl << endl;
    }

    // Delete contact function.
    void deleteContact() {
        string nameDelete;
        cout << "Enter the name of the contact to delete: ";
        cin >> nameDelete;
        for (int i = 0; i < length; i++) {

            // Delete the target contact and move the next contact forward to remove the empty space.
            // So that the information in the array is continuous.
            if (node[i].getName() == nameDelete) {
                for (int j = i; j < length - 1; j++) {
                    node[j] = node[j + 1];
                }
                length--;
                cout << endl << "Contact deleted successfully!" << endl << endl;
                return;
            }

        }
        cout << endl << "Contact not found." << endl << endl;
    }

    // Search contact function.
    void searchContact() const {
        string nameSearch;
        cout << "Enter the name of the contact to search: ";
        cin >> nameSearch;
        for (int i = 0; i < length; i++) {
            if (node[i].getName() == nameSearch) {
                cout << endl << "Contact found: " << endl << endl;
                node[i].displayContact();
                return;
            }
        }
        cout << endl << "Contact not found." << endl << endl;
    }

    // Display all contacts function.
    void displayAllContacts() const {
        if (length == 0) {
            cout << endl << "No contacts available." << endl << endl;
            return;
        }
        cout << endl << "All Contacts: " << endl << endl;
        for (int i = 0; i < length; i++) {
            node[i].displayContact();
        }
    }

    // Memory management avoiding memory leak.
    void clearMemory() {
        delete[] node;
        node = nullptr;
        capacity = 0;
        length = 0;
    }
};

int main() {
    Manager manager;
    string choice;

    while (true) {
        cout << endl << "Contact Management System" << endl;
        cout << "1. Add Contact" << endl;
        cout << "2. Delete Contact" << endl;
        cout << "3. Search Contact" << endl;
        cout << "4. Display All Contacts" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // Check the first character of the string entered by the user.
        // Prevent users from entering illegal characters and causing the program to loop infinitely.
        switch (choice[0]) {
            case '1':
                manager.addContact();
                break;
            case '2':
                manager.deleteContact();
                break;
            case '3':
                manager.searchContact();
                break;
            case '4':
                manager.displayAllContacts();
                break;
            case '5':
                // Clear memory before exiting this program.
                manager.clearMemory();
                cout << "Exiting..." << endl;
                // End the code directly after exiting.
                return 0;
            default:
                cout << "  Invalid choice." << endl;
                cout << "  Choice should be only 1~5 number." << endl;
        }
    }

    return 0;
}
