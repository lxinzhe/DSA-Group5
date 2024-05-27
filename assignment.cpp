#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

// Set maximum number of vendors that can be stored in the array
const int MAX_VENDORS = 100;

struct Vendor {
    string boothNumber;
    string vendorName;
    string category;
    string contactNumber;
    string event;
    string boothLocation;
    string price;
    string totalPrice; // Added field for total price
};

// Function to perform Jump Search by Vendor Name
int jumpSearchByName(const Vendor vendors[], int size, const string& vendorName) {
    int step = sqrt(size); // Determine the block size to be jumped

    // Find the block where the vendorName is present
    int prev = 0;
    while (vendors[min(step, size) - 1].vendorName < vendorName) {
        prev = step;
        step += sqrt(size);
        if (prev >= size)
            return -1; // If vendorName is not found in the array
    }

    // Perform linear search in the block
    while (vendors[prev].vendorName < vendorName) {
        prev++;
        if (prev == min(step, size))
            return -1; // If vendorName is not found in the block
    }

    // If vendorName is found, return its index
    if (vendors[prev].vendorName == vendorName)
        return prev;
    
    return -1; // If vendorName is not found
}

// Function to add vendors
void addVendor(Vendor vendors[], int& size) {
    if (size < MAX_VENDORS) {
        Vendor newVendor;
        cout << "Enter Booth Number: ";
        cin >> newVendor.boothNumber;
        cout << "Enter Vendor Name: ";
        cin.ignore(); // Ignore newline character left in the buffer
        getline(cin, newVendor.vendorName);
        cout << "Enter Category: ";
        cin >> newVendor.category;
        cout << "Enter Contact Number: ";
        cin >> newVendor.contactNumber;

        cout << "Event [A]Food Feasta Carnival Kuala Lumpur" << endl
             << "From 3 March 2024 - 13 March 2024" << endl;
        cout << "Event [B]Food Feasta Carnival Johor" << endl
             << "From 17 March 2024 - 27 March 2024" << endl;
        cout << "Which Event you will join: ";
        cin >> newVendor.event;

        cout << "------------------------------------" << endl;
        cout << "[A]Lot A, Price = RM900" << endl;
        cout << "[B]Lot B, Price = RM650" << endl;
        cout << "[C]Lot C, Price = RM550" << endl;
        cout << "Booth Location: ";
        cin >> newVendor.boothLocation;

        // Calculate total price based on booth location
        char selectedBooth = newVendor.boothLocation[0];
        switch (selectedBooth) {
            case 'A':
                newVendor.price = "RM900"; 
                break;
            case 'B':
                newVendor.price = "RM650"; 
                break;
            case 'C':
                newVendor.price = "RM550"; 
                break;
        }

        vendors[size++] = newVendor;
        cout << "Vendor added successfully." << endl;
    } else {
        cout << "Cannot add more vendors. Maximum limit reached." << endl;
    }
}

// Function to display a single vendor
void displayVendor(const Vendor& vendor) {
    cout << "| " << setw(15) << vendor.boothNumber << " | " << setw(20) << vendor.vendorName << " | " << setw(15) << vendor.category << " | " << setw(15) << vendor.contactNumber << " | " << setw(20) << vendor.event << " | " << setw(10) << vendor.price << " | "<< endl;
}

// Function to display the list of vendors
void displayVendors(const Vendor vendors[], int size) {
    if (size == 0) {
        cout << "No vendors available." << endl;
        return;
    }

    // Display all vendors
    cout << "\n---------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "|                                                   Vendor List                                                     |" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "| " << setw(15) << "Booth Number" << " | " << setw(20) << "Vendor Name" << " | " << setw(15) << "Category" << " | " << setw(15) << "Contact Number" << " | " << setw(20) << "Event" << " | " << setw(10) << "Price" << " | " << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < size; ++i) {
        displayVendor(vendors[i]);
    }
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
}

// Function to perform Jump Search by Vendor Name
int Jumpsearch(const Vendor vendors[], int size, const string& vendorName) {
    int step = sqrt(size); // Determine the block size to be jumped

    // Find the block where the vendorName is present
    int prev = 0;
    while (vendors[min(step, size) - 1].vendorName < vendorName) {
        prev = step;
        step += sqrt(size);
        if (prev >= size)
            return -1; // If vendorName is not found in the array
    }

    // Perform linear search in the block
    while (vendors[prev].vendorName < vendorName) {
        prev++;
        if (prev == min(step, size))
            return -1; // If vendorName is not found in the block
    }

    // If vendorName is found, return its index
    if (vendors[prev].vendorName == vendorName)
        return prev;
    
    return -1; // If vendorName is not found
}


int main() {
    // Declare variables
    int choice = 0;

    // Default data
    Vendor vendors[MAX_VENDORS] = {
        {"1001", "John's Burger", "Burger", "012-3456789", "A", "A", "RM900"},
                {"1002", "Maria's Pasta", "Pasta", "012-9876543", "B", "B", "RM650"},
        {"1003", "Sam's Pizza", "Pizza", "019-8765432", "A", "C", "RM550"}
    };
    int size = 3; // Initialize size with the number of predefined vendors

    while (choice != 4) {
        // Display main menu
        cout << "\n-----------------------------------" << endl;
        cout << "    WELCOME TO FOOD FESTA VENDOR BOOKING SYSTEM    " << endl;
        cout << "-----------------------------------" << endl;
        cout << "1. Add/View Vendors" << endl;
        cout << "2. Assignment 01 - cocktailSort + Jump Search" << endl;
        cout << "3. Assignment 02 - To be determined + Ubiquitous Binary Search" << endl;
        cout << "4. Exit" << endl;
        // Ask for selection from user
        cout << "Enter your choice: ";
        cin >> choice;

        // Loop when user enters invalid selection
        while (choice < 1 || choice > 4) {
            cout << "\nInvalid Selection, please enter your choice again: ";
            cin >> choice;
        }

        // Go to relevant function
        if (choice == 1) {
            // Add/View vendors function
            int selection = 0;

            while (selection != 3) {
                cout << "\n------------------" << endl;
                cout << "   Vendor Menu   " << endl;
                cout << "------------------" << endl;
                cout << "1. Add new vendor" << endl;
                cout << "2. View all vendors" << endl;
                cout << "3. Back to main menu" << endl;
                // Ask for selection from user
                cout << "Enter your choice: ";
                cin >> selection;

                while (selection < 1 || selection > 3) {
                    cout << "\nInvalid Selection, please enter your choice again: ";
                    cin >> selection;
                }

                switch (selection) {
                    case 1:
                        addVendor(vendors, size);
                        cout << "Press any key to go back to vendor menu...";
                        fflush(stdin);
                        getchar();
                        break;
                    case 2:
                        // This case is to display all vendors
                        displayVendors(vendors, size);
                        cout << "Press any key to go back to vendor menu...";
                        fflush(stdin);
                        getchar();
                        break;
                    case 3:
                        // This case is to go back to main menu
                        break;
                }
            }
        } else if (choice == 2) {
            int action;
            displayVendors(vendors, size);
            cout << "1. Sorting\n";
            cout << "2. Searching\n";
            cout << "3. Back to main menu\n";
            cout << "Enter your action: ";
            cin >> action;
             while (action < 1 || action > 3) {
                cout << "\nInvalid selection, please enter your action again: ";
                cin >> action;
            }

            if (action == 1) {
                // Sorting function here
            } else if (action == 2) {
                // This is jump search
                string target;
                cout << "Enter the Vendor Name you want to search: ";
                cin.ignore(); // Ignore newline character left in the buffer
                getline(cin, target);

                int result = Jumpsearch(vendors, size, target);
                if (result != -1) {
                    cout << "Search result: Vendor found at index " << result << endl;
                    displayVendor(vendors[result]); // Display the found vendor
                } else {
                    cout << "Vendor not found." << endl;
                }
            } 
        } else if (choice == 3) {
            int action;
            displayVendors(vendors, size);
            cout << "1. Sorting\n";
            cout << "2. Searching\n";
            cout << "3. Back to main menu\n";
            cout << "Enter your action: ";
            cin >> action;
             while (action < 1 || action > 3) {
                cout << "\nInvalid selection, please enter your action again: ";
                cin >> action;
            }

            if (action == 1) {
                // Sorting function here
            } else if (action == 2) {
                // Searching function here
            }
        } else {
            // Exit function
            cout << "Thank you for using the system, have a nice day. :)" << endl;
            exit(0);
        }
    } // end of main menu while loop

    return 0;
}

