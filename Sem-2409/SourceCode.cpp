#include <iostream>
#include <vector>

using namespace std;

class Node {
private:
    string name;
    string phone;
    string email;

    bool isValidName(const string& name) {
        for (char c : name) {
            if (!isalpha(c)) return false;
        }
        return true;
    }
    bool isValidPhone(const string& phone) {
        if (phone.length() != 10) return false;
        for (char c : phone) {
            if (!isdigit(c)) return false;
        }
        return true;
    }
    bool isValidEmail(const string& email) {
        int p0 = -1, p1 = -1;
        for (int i = 0; i < email.length(); i++) {
            if (email[i] == '@') p0 = i;
            if (email[i] == '.') p1 = i;
        }
        return p0 != -1 && p1 != -1 && p0 < p1 && p1 - p0 > 1;
    }

public:

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
    void displayContact() const {
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
        cout << "Email: " << email << endl;
        cout << "-------------------------" << endl << endl;
    }

    string getName() const {
        return name;
    }
};

class Manager {
private:
    vector<Node> node;

public:

    void addContact() {
        Node newContact;
        newContact.setContact();
        node.push_back(newContact);
        cout << endl << "Contact added successfully!" << endl << endl;
    }
    void deleteContact() {
        string nameDelete;
        cout << "Enter the name of the contact to delete: ";
        cin >> nameDelete;
        for (int i = 0; i < node.size(); i++) {
            if (node[i].getName() == nameDelete) {
                node.erase(node.begin() + i);
                cout << endl << "Contact deleted successfully!" << endl << endl;
                return;
            }
        }
        cout << endl << "Contact not found." << endl << endl;
    }
    void searchContact() const {
        string nameSearch;
        cout << "Enter the name of the contact to search: ";
        cin >> nameSearch;
        for (int i = 0; i < node.size(); i++) {
            if (node[i].getName() == nameSearch) {
                cout << endl << "Contact found: " << endl << endl;
                node[i].displayContact();
                return;
            }
        }
        cout << endl << "Contact not found." << endl << endl;
    }
    void displayAllContacts() const {
        if (node.empty()) {
            cout << endl << "No contacts available." << endl << endl;
            return;
        }
        cout << endl << "All Contacts: " << endl << endl;
        for (int i = 0; i < node.size(); ++i) {
            cout << i + 1 << ". ";
            node[i].displayContact();
        }
    }
};

int main() {
    Manager manager;
    int choice;

    while (true) {
        cout << endl << "Contact Management System" << endl;
        cout << "1. Add Contact" << endl;
        cout << "2. Delete Contact" << endl;
        cout << "3. Search Contact" << endl;
        cout << "4. Display All Contacts" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manager.addContact();
                break;
            case 2:
                manager.deleteContact();
                break;
            case 3:
                manager.searchContact();
                break;
            case 4:
                manager.displayAllContacts();
                break;
            case 5:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "  Invalid choice." << endl;
                cout << "  Choice should be only 1~5 number." << endl;
        }
    }

    return 0;
}
