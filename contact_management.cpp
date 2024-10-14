#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Contact {
    string name;
    string phone;
    string email;
};

void addContact(vector<Contact>& contacts) {
    Contact newContact;
    cin.ignore(); // Clear input buffer
    cout << "Enter Name: ";
    getline(cin, newContact.name);
    cout << "Enter Phone Number: ";
    getline(cin, newContact.phone);
    cout << "Enter Email: ";
    getline(cin, newContact.email);
    cout << endl; // Added newline for better formatting

    contacts.push_back(newContact);
    cout << "Contact added successfully.\n";
}

void viewContacts(const vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts to display.\n";
    } else {
        for (size_t i = 0; i < contacts.size(); ++i) {
            cout << "Contact " << i + 1 << ":\n";
            cout << "Name: " << contacts[i].name << "\n";
            cout << "Phone: " << contacts[i].phone << "\n";
            cout << "Email: " << contacts[i].email << "\n";
            cout << "-----------------------\n";
        }
    }
}

void editContact(vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts to edit.\n";
        return;
    }

    int index;
    cout << "Enter the contact number you want to edit: ";
    cin >> index;

    if (index < 1 || index > contacts.size()) {
        cout << "Invalid contact number.\n";
        return;
    }

    cin.ignore();  // Clear input buffer before using getline

    Contact& contact = contacts[index - 1];
    cout << "Editing contact: " << contact.name << "\n";

    cout << "Enter new Name (leave blank to keep current): ";
    string newName;
    getline(cin, newName);
    if (!newName.empty()) {
        contact.name = newName;
    }

    cout << "Enter new Phone Number (leave blank to keep current): ";
    string newPhone;
    getline(cin, newPhone, '\n'); // Limit input to a single line
    if (!newPhone.empty()) {
        contact.phone = newPhone;
    }

    cout << "Enter new Email (leave blank to keep current): ";
    string newEmail;
    getline(cin, newEmail, '\n'); // Limit input to a single line
    if (!newEmail.empty()) {
        contact.email = newEmail;
    }

    cout << "Contact updated successfully.\n";
}

void deleteContact(vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts to delete.\n";
        return;
    }

    int index;
    cout << "Enter the contact number you want to delete: ";
    cin >> index;

    if (index < 1 || index > contacts.size()) {
        cout << "Invalid contact number.\n";
        return;
    }

    contacts.erase(contacts.begin() + index - 1);
    cout << "Contact deleted successfully.\n";
}

void loadContacts(vector<Contact>& contacts, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return;
    }

    Contact contact;
    string line;
    while (getline(file, contact.name)) {
        getline(file, contact.phone);
        getline(file, contact.email);
        contacts.push_back(contact);
    }

    file.close();
}

void saveContacts(const vector<Contact>& contacts, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open file for saving.\n";
        return;
    }

    for (const auto& contact : contacts) {
        file << contact.name << "\n" << contact.phone << "\n" << contact.email << "\n";
    }

    file.close();
    cout << "Contacts saved to file successfully.\n";
}

int main() {
    vector<Contact> contacts;
    string filename = "contacts.txt";

    loadContacts(contacts, filename);

    int choice;
    do {
        cout << "\nContact Management System\n";
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Edit Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addContact(contacts);
                break;
            case 2:
                viewContacts(contacts);
                break;
            case 3:
                editContact(contacts);
                break;
            case 4:
                deleteContact(contacts);
                break;
            case 5:
                saveContacts(contacts, filename);
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}