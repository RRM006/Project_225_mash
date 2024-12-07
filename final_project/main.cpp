#include <iostream>
#include <string>
#include <unordered_map>
#include <limits>
#include <thread>
#include <chrono>
#include <conio.h> // For _getch() on Windows

using namespace std;

// Function prototypes
void showMenu();
void olympicInformationSystem();
void animatedText(const string& text, int delay = 50);
string hashPassword(const string& password);
string readPassword(); // Function to mask password input

// User database using hashed passwords
unordered_map<string, string> userDatabase;

// Node structure for Linked List
struct Node {
    string data;
    Node* next;
};

Node* head = nullptr; // Head pointer for linked list

// Linked List CRUD operations
void createData(string value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    animatedText("Data created successfully.\n", 25);
}

void readData() {
    if (head == nullptr) {
        animatedText("No data available.\n", 25);
        return;
    }

    Node* temp = head;
    animatedText("Data in the system: \n", 25);
    while (temp != nullptr) {
        cout << temp->data << endl;
        temp = temp->next;
    }
}

void updateData(string oldValue, string newValue) {
    if (head == nullptr) {
        animatedText("No data available to update.\n", 25);
        return;
    }

    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == oldValue) {
            temp->data = newValue;
            animatedText("Data updated successfully.\n", 25);
            return;
        }
        temp = temp->next;
    }

    animatedText("Data not found.\n", 25);
}

void deleteData(string value) {
    if (head == nullptr) {
        animatedText("No data available to delete.\n", 25);
        return;
    }

    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;
        animatedText("Data deleted successfully.\n", 25);
        return;
    }

    Node* temp = head;
    Node* prev = nullptr;

    while (temp != nullptr && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        animatedText("Data not found.\n", 25);
        return;
    }

    prev->next = temp->next;
    delete temp;
    animatedText("Data deleted successfully.\n", 25);
}

void searchRecord(string value) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == value) {
            cout << "Record found: " << temp->data << endl;
            return;
        }
        temp = temp->next;
    }
    animatedText("Record not found.\n", 25);
}

// Animated Text Display
void animatedText(const string& text, int delay) {
    for (char ch : text) {
        cout << ch;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}

// Password hashing
string hashPassword(const string& password) {
    hash<string> hasher;
    return to_string(hasher(password));
}

// Function to read a masked password
string readPassword() {
    string password;
    char ch;
    cout << "Enter Password: ";
    while ((ch = _getch()) != '\r') { // '\r' corresponds to Enter key
        if (ch == '\b') { // Handle backspace
            if (!password.empty()) {
                cout << "\b \b"; // Erase the last '*' on the console
                password.pop_back();
            }
        } else {
            cout << '*'; // Display asterisk for each character entered
            password.push_back(ch);
        }
    }
    cout << endl;
    return password;
}

// Login System
bool loginUser() {
    string email, password;
    cout << "Enter Email: ";
    cin >> email;
    password = readPassword();

    string hashedPassword = hashPassword(password);
    if (userDatabase.find(email) != userDatabase.end() && userDatabase[email] == hashedPassword) {
        animatedText("Login successful!\n", 50);
        return true;
    } else {
        animatedText("Invalid email or password.\n", 50);
        return false;
    }
}

void registerUser() {
    string email, password;
    cout << "Create an Email: ";
    cin >> email;
    password = readPassword();

    if (userDatabase.find(email) != userDatabase.end()) {
        animatedText("Email already registered. Try logging in.\n", 50);
    } else {
        userDatabase[email] = hashPassword(password);
        animatedText("Registration successful. You can now log in.\n", 50);
    }
}

void loginPage() {
    bool loggedIn = false;

    while (!loggedIn) {
        int choice;
        cout << "1. Login\n2. Register\nChoose an option: ";
        cin >> choice;

        // Validate input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            animatedText("Invalid option. Please enter 1 or 2.\n", 50);
            continue;
        }

        switch (choice) {
            case 1:
                loggedIn = loginUser();
                break;
            case 2:
                registerUser();
                break;
            default:
                animatedText("Invalid option. Try again.\n", 50);
        }
    }

    olympicInformationSystem();
}

// Olympic Information System
void olympicInformationSystem() {
    animatedText("\n--- Paris 2024 Olympic Summer Games: CRUD Operations ---\n", 50);

    while (true) {
        showMenu();

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        // Input validation
        if (cin.fail()) {
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            animatedText("Invalid input. Please enter a number.\n", 50);
            continue;
        }

        switch (choice) {
            case 1:
                readData();
                break;
            case 2: {
                string value;
                cout << "Enter data to search: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, value);
                searchRecord(value);
                break;
            }
            case 3: {
                string value;
                cout << "Enter data to add: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, value);
                createData(value);
                break;
            }
            case 4: {
                string oldValue, newValue;
                cout << "Enter the old data: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, oldValue);
                cout << "Enter the new data: ";
                getline(cin, newValue);
                updateData(oldValue, newValue);
                break;
            }
            case 5: {
                string value;
                cout << "Enter data to delete: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, value);
                deleteData(value);
                break;
            }
            case 6:
                readData();
                break;
            case 7:
                animatedText("Exiting the system. Goodbye!\n", 50);
                return;
            default:
                animatedText("Invalid option. Try again.\n", 50);
        }
    }
}

void showMenu() {
    animatedText("\n--- Paris 2024 Olympic Summer Games: CRUD Operations ---\n", 50);
    cout << "1. View All Records\n";
    cout << "2. Search for a Record\n";
    cout << "3. Add a New Record\n";
    cout << "4. Update an Existing Record\n";
    cout << "5. Delete a Record\n";
    cout << "6. Show Records After CRUD\n";
    cout << "7. Exit\n";
}

int main() {
    animatedText("Welcome to Paris Olympic 2024 Information System!\n", 100);
    loginPage();
    return 0;
}
