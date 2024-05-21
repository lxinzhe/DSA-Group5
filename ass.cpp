#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;

struct Vendor {
    string name;
    string type;
    string contact;
    int boothNumber;
};

struct Feedback {
    string vendorName;
    string message;
    int boothNumber;
};

vector<Vendor> vendors;
vector<Feedback> feedbacks;
int nextBoothNumber = 1; 

void findVendor();
void displayMainMenu();
void addNewVendor();
void saveVendorsToFile();
void loadVendorsFromFile();

void writeFeedback();
void findFeedback();
void saveFeedbackToFile();
void loadFeedbackFromFile();
void interpolationSearchFeedback(int boothNumber);

int main() {
    loadVendorsFromFile();
    loadFeedbackFromFile();
    int choice;
    while (true) {
        displayMainMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                findVendor();
                break;
            case 2:
                addNewVendor();
                break;
            case 3:
                writeFeedback();
                break;
            case 4:
                findFeedback();
                break;
            case 5:
                cout << "Exiting the system. Goodbye!" << endl;
                saveVendorsToFile();
                saveFeedbackToFile();
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void displayMainMenu() {
    system("cls");
    cout << "\nWelcome to Food Feasta Registration and Vendor Booking System\n";
    cout << "1. Find Vendor\n";
    cout << "2. Add New Vendor\n";
    cout << "3. Write Feedback\n";
    cout << "4. Find Feedback\n";
    cout << "5. Exit\n";
    cout << "Please enter your choice: ";
}

void addNewVendor() {
    Vendor newVendor;
    cout << "Enter Vendor Name: ";
    getline(cin, newVendor.name);
    cout << "Enter Vendor Type (e.g., Food, Beverage, Accessories): ";
    getline(cin, newVendor.type);
    cout << "Enter Contact Information: ";
    getline(cin, newVendor.contact);
    
    newVendor.boothNumber = nextBoothNumber++;
    vendors.push_back(newVendor);
    cout << "Vendor has been successfully added with Booth Number " << newVendor.boothNumber << "!\n";
    saveVendorsToFile();
    cout << "Press Enter to return to the main menu.";
    cin.ignore();
}

//interpolation Search  for vendor
void interpolationSearch(int boothNumber) {
    int low = 0, high = vendors.size() - 1;
    
    while (low <= high && boothNumber >= vendors[low].boothNumber && boothNumber <= vendors[high].boothNumber) {
        if (low == high) {
            if (vendors[low].boothNumber == boothNumber) {
                cout << "Vendor found:\n";
                cout << "Name: " << vendors[low].name << endl;
                cout << "Type: " << vendors[low].type << endl;
                cout << "Contact: " << vendors[low].contact << endl;
                cout << "Booth Number: " << vendors[low].boothNumber << endl;
                return;
            } else {
                cout << "Vendor not found." << endl;
                return;
            }
        }
        
        // Interpolation formula
        int pos = low + (((double)(high - low) / (vendors[high].boothNumber - vendors[low].boothNumber)) * (boothNumber - vendors[low].boothNumber));
        
        if (vendors[pos].boothNumber == boothNumber) {
            cout << "Vendor found:\n";
            cout << "Name: " << vendors[pos].name << endl;
            cout << "Type: " << vendors[pos].type << endl;
            cout << "Contact: " << vendors[pos].contact << endl;
            cout << "Booth Number: " << vendors[pos].boothNumber << endl;
            return;
        }
        
        if (vendors[pos].boothNumber < boothNumber) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }
    
    cout << "Vendor not found." << endl;
}

void findVendor() {
    system("cls");
    int cho;
    cout << "Enter 1 to Search Vendor Booth Number\n";
    cout << "Enter 2 to Sort Vendor\n";
    cin >> cho;
    cin.ignore(); 

    switch (cho) {
        case 1: {
            int searchBoothNumber;
            cout << "Enter the booth number of the vendor to search: ";
            cin >> searchBoothNumber;
            cin.ignore(); 
            interpolationSearch(searchBoothNumber);
            break;
        }
        case 2: {
            // Call the function to sort vendors
            break;
        }
        default:
            cout << "Invalid choice.\n";
            break;
    }

    cout << "Press Enter to return to the main menu.";
    cin.ignore();
}

void writeFeedback() {
    Feedback newFeedback;
    cout << "Enter Vendor Name: ";
    getline(cin, newFeedback.vendorName);
    cout << "Enter Feedback: ";
    getline(cin, newFeedback.message);

	newFeedback.boothNumber = nextBoothNumber++;
    feedbacks.push_back(newFeedback);
    cout << "Feedback has been successfully added with Booth Number " << newFeedback.boothNumber << "!\n";
    saveFeedbackToFile();
    cout << "Press Enter to return to the main menu.";
    cin.ignore();
    
}

//interpolation Search  for feedback
void interpolationSearchFeedback(int boothNumber) {
    int low = 0, high = feedbacks.size() - 1;
    
    while (low <= high && boothNumber >= feedbacks[low].boothNumber && boothNumber <= feedbacks[high].boothNumber) {
        if (low == high) {
            if (feedbacks[low].boothNumber == boothNumber) {
                cout << "Feedback found:\n";
                cout << "Vendor Name: " << feedbacks[low].vendorName << endl;
                cout << "Feedback: " << feedbacks[low].message << endl;
                return;
            } else {
                cout << "Feedback not found." << endl;
                return;
            }
        }
        
        int pos = low + (((double)(high - low) / (feedbacks[high].boothNumber - feedbacks[low].boothNumber)) * (boothNumber - feedbacks[low].boothNumber));
        
        if (feedbacks[pos].boothNumber == boothNumber) {
            cout << "Feedback found:\n";
            cout << "Vendor Name: " << feedbacks[pos].vendorName << endl;
            cout << "Feedback: " << feedbacks[pos].message << endl;
            return;
        }
        
        if (feedbacks[pos].boothNumber < boothNumber) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }
    
    cout << "Feedback not found." << endl;
}

void findFeedback() {
    system("cls");
    int cho;
    cout << "Enter 1 to Search Feedback by Booth Number\n";
    cout << "Enter 2 to Sort Feedback\n";
    cin >> cho;
    cin.ignore(); 

    switch (cho) {
        case 1: {
            int searchBoothNumber;
            cout << "Enter the booth number of the vendor to search for feedback: ";
            cin >> searchBoothNumber;
            cin.ignore(); 
            interpolationSearchFeedback(searchBoothNumber);
            break;
        }
        case 2: {
            // Call the function to sort feedbacks
            break;
        }
        default:
            cout << "Invalid choice.\n";
            break;
    }

    cout << "Press Enter to return to the main menu.";
    cin.ignore();
}

// save feedback into file
void saveFeedbackToFile() {
    ofstream outFile("feedback.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < feedbacks.size(); ++i){
            outFile << feedbacks[i].vendorName << '\n'
                    << feedbacks[i].message << '\n'
                    << feedbacks[i].boothNumber << '\n';
        }
        outFile.close();
    } else {
        cout << "Unable to save feedback data.\n";
    }
}

//read feedback from file
void loadFeedbackFromFile() {
    ifstream inFile("feedback.txt");
    if (inFile.is_open()) {
        feedbacks.clear();
        Feedback feedback;
        while (getline(inFile, feedback.vendorName) &&
               getline(inFile, feedback.message)) {
            inFile >> feedback.boothNumber;
            inFile.ignore(); // Consume newline character
            feedbacks.push_back(feedback);
        }
        inFile.close();
    } else {
        cout << "No feedback data file found. Starting with an empty list.\n";
    }
}

// save vendor into file
void saveVendorsToFile() {
    ofstream outFile("vendors.txt");
    if (outFile.is_open()) {
        for (size_t i = 0; i < vendors.size(); ++i) {
            outFile << vendors[i].name << '\n'
                    << vendors[i].type << '\n'
                    << vendors[i].contact << '\n'
                    << vendors[i].boothNumber << '\n';
        }
        outFile.close();
    } else {
        cout << "Unable to save vendor data.\n";
    }
}

//read vendor from file
void loadVendorsFromFile() {
    ifstream inFile("vendors.txt");
    if (inFile.is_open()) {
        vendors.clear();
        Vendor vendor;
        while (getline(inFile, vendor.name) &&
               getline(inFile, vendor.type) &&
               getline(inFile, vendor.contact)) {
            inFile >> vendor.boothNumber;
            inFile.ignore(); // Consume newline character
            vendors.push_back(vendor);
            if (vendor.boothNumber >= nextBoothNumber) {
                nextBoothNumber = vendor.boothNumber + 1;
            }
        }
        inFile.close();
    } else {
        cout << "No vendor data file found. Starting with an empty list.\n";
    }
}


