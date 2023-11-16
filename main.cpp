#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

struct Contact {
    string name;
    string phoneNumber;
    Contact* next;

    Contact(const std::string& n, const string& phone)
        : name(n), phoneNumber(phone), next(nullptr) {}
};

Contact* phonebook = nullptr;

void addContact() {
    Contact* newContact;
    cout << "Enter name: ";
    string name, phoneNumber;
    cin >> name;
    cout << "Enter phone number: ";
    cin >> phoneNumber;

    newContact = new Contact(name, phoneNumber);
    newContact->next = phonebook;
    phonebook = newContact;
    cout << "Contact added successfully." << endl;
}

void searchContact() {
    string searchName;
    cout << "Enter name to search: ";
    cin >> searchName;

    Contact* current = phonebook;
    while (current != nullptr) {
        if (current->name == searchName) {
            cout << "Name: " << current->name << " | Phone: " << current->phoneNumber << endl;
            return;
        }
        current = current->next;
    }

    cout << "Contact not found." << endl;
}

void deleteContact() {
    string deleteName;
    cout << "Enter name to delete: ";
    cin >> deleteName;

    Contact* current = phonebook;
    Contact* prev = nullptr;

    while (current != nullptr) {
        if (current->name == deleteName) {
            if (prev != nullptr) {
                prev->next = current->next;
            } else {
                phonebook = current->next;
            }
            delete current;
            std::cout << "Contact deleted successfully." << std::endl;
            return;
        }
        prev = current;
        current = current->next;
    }

    cout << "Contact not found." << std::endl;
}

void updateContact() {
    string updateName;
    cout << "Enter name to update: ";
    cin >> updateName;

    Contact* current = phonebook;
    while (current != nullptr) {
        if (current->name == updateName) {
            std::cout << "Enter new phone number: ";
            std::cin >> current->phoneNumber;
            std::cout << "Contact updated successfully." << endl;
            return;
        }
        current = current->next;
    }

    cout << "Contact not found." << endl;
}

void notepadMenu() {
    vector<string> text;
    stack<vector<string>> undoStack;
    stack<vector<string>> redoStack;
    string clipboard;

    while (true) {
        cout << "Notepad Menu:" << endl;
        cout << "1. Type a line of text" << endl;
        cout << "2. Undo" << endl;
        cout << "3. Redo" << endl;
        cout << "4. Cut" << endl;
        cout << "5. Copy" << endl;
        cout << "6. Paste" << endl;
        cout << "7. Return to Main Menu" << endl;

        int choice;
        cin >> choice;
        cin.ignore(); 
        
        string line;

        switch (choice) {
            case 1:
                cout << "Enter a line of text: ";
                getline(cin, line);
                text.push_back(line);
                undoStack.push(text);
                while (!redoStack.empty()) {
                    redoStack.pop();
                }
                break;
            case 2:
                if (undoStack.size() > 1) {
                    redoStack.push(undoStack.top());
                    undoStack.pop();
                    text = undoStack.top();
                } else {
                    cout << "Cannot undo further." << endl;
                }
                break;
            case 3:
                if (!redoStack.empty()) {
                    undoStack.push(redoStack.top());
                    redoStack.pop();
                    text = undoStack.top();
                } else {
                    cout << "Cannot redo further." << endl;
                }
                break;
            case 4:
                if (!text.empty()) {
                    clipboard = text.back();
                    text.pop_back();
                    undoStack.push(text);
                    cout << "Text has been cut and copied to the clipboard."<<endl;
                } else {
                    cout << "No text to cut." << endl;
                }
                break;
            case 5:
                if (!text.empty()) {
                    clipboard = text.back();
                    cout << "Text has been copied to the clipboard." << endl;
                } else {
                    cout << "No text to copy." << endl;
                }
                break;
            case 6:
                if (!clipboard.empty()) {
                    text.push_back(clipboard);
                    undoStack.push(text);
                    cout << "Text from clipboard has been pasted." << endl;
                } else {
                    cout << "Clipboard is empty." << endl;
                }
                break;
            case 7:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        
        cout << "Current Text:" << endl;
        for (const string &line : text) {
            cout << line << endl;
        }
    }
}

int main() {
    int choice;
    while (true) {
        cout << "Main Menu:" << endl;
        cout << "1. Phonebook" << endl;
        cout << "2. Notepad" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                while (true) {
                    cout << "Phonebook Application" << endl;
                    cout << "1. Add Contact" << endl;
                    cout << "2. Search Contact" << endl;
                    cout << "3. Delete Contact" << endl;
                    cout << "4. Update Contact" << endl;
                    cout << "5. Return to Main Menu" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice) {
                        case 1:
                            addContact();
                            break;
                        case 2:
                            searchContact();
                            break;
                        case 3:
                            deleteContact();
                            break;
                        case 4:
                            updateContact();
                            break;
                        case 5:
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                    }
                }
            case 2:
                notepadMenu();
                break;
            case 3:
                cout << "Exiting the program..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}



