#include<iostream> 
#include<iomanip>
#include<fstream>
#include<cstring>
#include <bits/stdc++.h>
#include<Windows.h>
#include<unistd.h>
#include <string>
#include<map>
#include <conio.h>
#include <sstream>
#include <algorithm>
#include <unordered_map>


using namespace std;
struct Booking {
    string userID;
    string details;
};

struct BookingDetails {
    string user;
    string vendorName;
    string contact;
    string eventDate;
    string serviceType;
    char booth;
    string boothNumber;
    float totalPrice;

    BookingDetails() : totalPrice(0.0f) {}
};
 
struct FeedbackNode {
    string username;
    string feedback;
    int rating;
    FeedbackNode* next;

    FeedbackNode(const string& user, const string& fb, int rate)
        : username(user), feedback(fb), rating(rate), next(nullptr) {}
};

struct Node {
   string name;
    string contact;
    string service_type;
    string userID;
    char eventgrp;
    char booth;
    float total;
    int duration;
    Node* next;

    // Constructor
    Node() : next(nullptr) {}
};

HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);

void display_menu();
void process_menu(const string& Username); 
void adminpage();
void detaildisplay(const string& userIdfile);
string GetHiddenPassword();
void viewFeedback();
void exitAdminPage();


class USER {
private:
    struct UserData {
        string username;
        string password;
        string email;
        UserData* next;

        UserData(const string& uname, const string& pwd, const string& mail)
            : username(uname), password(pwd), email(mail), next(nullptr) {}
    };
    UserData* head;


public:
    USER() : head(nullptr) {}

    ~USER() {
        UserData* current = head;
        while (current != nullptr) {
            UserData* next = current->next;
            delete current;
            current = next;
        }
        
    }
    
        string Login() {
    string enteredUsername, enteredPassword;
    bool loginSuccessful = false;

    do {
        system("cls");
        cout << "===================================" << endl;
        cout << "              LOGIN                 " << endl;
        cout << "===================================" << endl;
        cout << "Enter your username: ";
        cin >> enteredUsername;

        cout << "Enter your password: ";
        enteredPassword = GetHiddenPassword();

        ifstream file("user_data.txt");
        if (file.is_open()) {
            string fileUsername, filePassword, fileEmail;
            while (file >> fileUsername >> filePassword >> fileEmail) {
                if (fileUsername == enteredUsername && filePassword == enteredPassword) {
                    cout << "Login successful!" << endl;
                    loginSuccessful = true;
                    break;
                }
            }
            file.close();
        } else {
            cout << "Error opening file." << endl;
        }

        if (!loginSuccessful) {
            cout << "\033[1;31mInvalid username or password. Please try again.\033[0m";
            cin.get();
            cin.ignore();
        }
    } while (!loginSuccessful);

    return enteredUsername;
}

    void NewUser() {
        cout << "New register?  \n(Note: if you are a new user type Yes, otherwise type No):";
        string NewRegister;
        cin >> NewRegister; // must be "yes" if he is a new user or "no" if he is not a new user
        cin.ignore();
        if (NewRegister == "Yes" || NewRegister == "yes") {
            string username, email, password;
            cout << "Enter Your Username : "; 
            cin >> username;
            while (!validusername(username)) {
                cout << "The Username is not valid please try again : " << endl;
                cin >> username;
            }
            cout << endl << "Valid Username." << endl << endl;

            cout << "Email : "; // enter email
            cin >> email;
            while (!validEmail(email)) {
                cout << "The email address is not valid please try again : " << endl;
                cin >> email;
            }
            cout << endl << "Valid email address." << endl << endl;

            cout << "(Note: your password must be at least one digit, one special character, one uppercase letter, and one lowercase letter) \n"; // enter password
            cout << "Password : ";
            cin >> password;
            while (!validpassword(password)) {
                cout << "The password is not valid please try again : " << endl;
                cin >> password;
            }
            cout << endl << "Valid password." << endl << endl;

            // Save user details to linked list
            AddUser(username, password, email);

            cout << "Registration completed!" << endl;
        }
        else if (NewRegister == "No"  || NewRegister == "no") { // have already an account
            string Username = Login();
            system("cls");
            process_menu(Username);
        }
    }

void AddUser(const string& username, const string& password, const string& email) {
    UserData* newUser = new UserData(username, password, email);
    if (head == nullptr) {
        head = newUser;
    } else {
        UserData* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newUser;
    }
    // Save user details to a file
    ofstream file("user_data.txt", ios::app);
    if (file.is_open()) {
        file << username << " " << password << " " << email << endl;
        file.close();
    } else {
        cout << "Error opening file." << endl;
    }
}
   	bool validusername(string firstname) // function to check the validity of the first name
		{
    		if (firstname[0] >= 'A' && firstname[0] <= 'Z')
     		return true;
	  		else
	  		return false;
		}
		bool validEmail(string email) // function to check the validity of the email
		{
    		int AT = -1, dot = -1;                                                            // variables to store the position of ( @ )and (dot)
    		int counterforAT = 0, counterforDot = 0;                                          // check if there is more than one (@) or (dot)
    		if ((email[0] >= 'a' && email[0] <= 'z') || (email[0] >= 'A' && email[0] <= 'Z')) // if the email address start with letter(valid )
    		{
        		for (int i = 0; i < email.length(); i++)
        		{
            		if (email[i] == '@') // If the character is '@'
            		{
                		AT = i;
                		++counterforAT;
            		}else if (email[i] == '.'){ // If character is '.'
                		dot = i;
                		++counterforDot;
            		}
        		}
        			if (AT == -1 || dot == -1) // If (@) or (dot)is not present
            		return false;

        			if (AT > dot) // If (dot) is present before(@)
            		return false;

        			if (counterforDot > 1 || counterforAT > 1)
            		return false;

        			return !(dot >= (email.length() - 1));
    			}
    				else if (email[0] >= '0' && email[0] <= '9'){ // if the email address start with number (not valid )
        			return false;
    			}
    				else // if the email address start with other symbols (not valid)
    				{
        				return false;
    				}
		}//end of validEmail
		
		bool validpassword(string password) // function to check the validity of the password
		{
    		int digit = 0, uppercase = 0, lowercase = 0, specialchar = 0; // counter to find if password contain at least one digit,one special character, one uppercase letter, and one lowercase letter
    		if (password.length() >= 8 && password.length() <= 15){
        		if (password.find(" ") == -1)
        		{
            		for (int i = 0; i < password.length(); i++)
            		{
               			if (password[i] >= '0' && password[i] <= '9')
                		{
                    	++digit;
                		}
                		else if (password[i] >= 'a' && password[i] <= 'z')
                		{
                    	++lowercase;
                		}
                		else if (password[i] >= 'A' && password[i] <= 'Z')
                		{
                   		++uppercase;
                		}
                		else if (password[i] == '@' || password[i] == '#' || password[i] == '_')
                		{
                    	++specialchar;
                		}
            		}

            		if (digit == 0 || uppercase == 0 || lowercase == 0 || specialchar == 0)
            		{
                	return false;
            		}
            		else
            		{
               		return true;
            		}
        		}
        		else if (password.find(" ") != -1){
            		return false;
        		}
    }//end of if else
		cout << "Note : your password length less than 8 characters or more than 15 characters." << endl;
    	return false;
    }
};

class adminpanel : public USER
{
private:
    string enteredAdmin, adminname, enteredPassword, adminpassword;
    struct AdminData {
        string username;
        string password;
        AdminData* next;

        AdminData(const string& uname, const string& pwd)
            : username(uname), password(pwd), next(nullptr) {}
    };
    AdminData* head;

public:
    adminpanel() : head(nullptr) {
        loadAdmindetails(); // Load admin details on initialization
    }

    ~adminpanel() {
        AdminData* current = head;
        while (current != nullptr) {
            AdminData* next = current->next;
            delete current;
            current = next;
        }
    }

    void loadAdmindetails() {
        ifstream file("admin_login.txt");
        if (file.is_open()) {
            string uname, pwd;
            while (file >> uname >> pwd) {
                AddAdmin(uname, pwd);
            }
            file.close();
        } else {
            cout << "Error opening admin file." << endl;
        }
    }

    void AddAdmin(const string& username, const string& password) {
        AdminData* newAdmin = new AdminData(username, password);
        if (head == nullptr) {
            head = newAdmin;
        } else {
            AdminData* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newAdmin;
        }
    }

    void SaveAdmindetails() {
        ofstream file("admin_login.txt");
        if (file.is_open()) {
            AdminData* current = head;
            while (current != nullptr) {
                file << current->username << " " << current->password << endl;
                current = current->next;
            }
            file.close();
        } else {
            cout << "Error opening admin file." << endl;
        }
    }

    bool admin() {
        bool loginSuccessful = false;
        string enteredAdmin, enteredPassword;

        cout << "\nPlease Enter Admin Name     :";
        cin.ignore();
        getline(cin, enteredAdmin);
        cout << "Please Enter Admin Password :";
        enteredPassword = GetHiddenPassword();

        AdminData* current = head;
        while (current != nullptr) {
            if (enteredAdmin == current->username && enteredPassword == current->password) {
                loginSuccessful = true;
                break;
            }
            current = current->next;
        }

        if (loginSuccessful) {
            system("cls");
            SetConsoleCP(437);
            SetConsoleOutputCP(437);
            int bar1 = 177, bar2 = 219;
            cout << "\n\n\n\t\t\t\tVerification...";
            cout << "\n\t\t\t\t";
            for (int i = 0; i < 25; i++)
                cout << (char)bar1;
            cout << "\r";
            cout << "\t\t\t\t";
            for (int i = 0; i < 25; i++) {
                cout << (char)bar2;
                Sleep(20);
            }
            cout << "\n\n\t\t\t\t" << (char)1 << "\033[1;32mLog In Succesful!\033[0m\n";
            system("Pause");

            return true;
        } else {
            cout << "\n\033[1;31mInvalid Name or Password, Please Try Again\033[0m" << endl;
            system("Pause");
            system("cls");
            return false;
        }
    }

    void NewAdmin() {
        cout << "New register?  \n(Note: if you are a new admin type Yes, otherwise type No):";
        string NewRegister;
        cin >> NewRegister; // must be "yes" if he is a new admin or "no" if he is not a new admin
        if (NewRegister == "Yes" || NewRegister == "yes") {
            string username, email, password;
            cout << "Enter Your Username : ";
            cin >> username;

            cout << "(Note: your password must be at least one digit, one special character, one uppercase letter, and one lowercase letter) \n"; // enter password
            cout << "Password : ";
            cin >> password;
            while (!validpassword(password)) {
                cout << "The password is not valid please try again : " << endl;
                cin >> password;
            }
            cout << endl << "Valid password." << endl << endl;

            // Save admin details to linked list
            AddAdmin(username, password);
            SaveAdmindetails(); // Save updated linked list to file

            cout << "Registration completed!" << endl;
        }
    }

    void UpdateAdmin(const string& adminName, const string& newPassword) {
        AdminData* current = head;
        bool adminFound = false;

        while (current != nullptr) {
            if (current->username == adminName) {
                current->password = newPassword;
                adminFound = true;
                cout << "\033[1;32mAdmin password updated successfully!\033[0m" << endl;
                break;
            }
            current = current->next;
        }

        if (!adminFound) {
            cout << "No admin found with the specified name." << endl;
        }

        SaveAdmindetails(); // Save updated linked list to file
    }

    void deleteAdmin(const string& adminName) {
        AdminData* current = head;
        AdminData* previous = nullptr;
        bool adminFound = false;

        while (current != nullptr) {
            if (current->username == adminName) {
                adminFound = true;
                fflush(stdin);
                cout << "Are you sure you want to delete admin " << adminName << "? (yes/no): ";
                string confirmation;
                getline(cin, confirmation);
                if (confirmation == "yes") {
                    if (previous == nullptr) {
                        head = current->next;
                    } else {
                        previous->next = current->next;
                    }
                    string deletionTime = getCurrentTime();
                    cout << "\033[1;32mAdmin " << adminName << " has been deleted at " << deletionTime << ".\033[0m" << endl;

                    // Log deletion
                    ofstream logFile("admin_deletion_log.txt", ios::app);
                    if (logFile.is_open()) {
                        logFile << "Admin '" << adminName << "' was deleted at " << deletionTime << endl;
                        logFile.close();
                    }

                    delete current;
                    break;
                } else {
                    cout << "Admin deletion cancelled." << endl;
                    return;
                }
            }
            previous = current;
            current = current->next;
        }

        if (!adminFound) {
            cout << "No admin found with the specified name." << endl;
        } else {
            SaveAdmindetails(); // Save updated linked list to file
        }
    }

    void viewDeletionLog() {
        ifstream logFile("admin_deletion_log.txt");
        if (logFile.is_open()) {
            string line;
            cout << "================ Delete Time ================" << endl;
            while (getline(logFile, line)) {
                cout << line << endl;
            }
                cout << "=================================================" << endl;
            logFile.close();
        } else {
            cout << "Unable to open log file." << endl;
        }
    }

    void addinAdmin() {
        int updatechoice;
        cout << "\t\t\t\t\t-------------------------------------" << endl;
        cout << "\t\t\t\t\tEnter 1 for Add New Admin" << endl;
        cout << "\t\t\t\t\tEnter 2 for Update Admin Information" << endl;
        cout << "\t\t\t\t\tEnter 3 for Delete Admin" << endl;
        cout << "\t\t\t\t\tEnter 4 for View deleted Admin" << endl;
        cout << "\t\t\t\t\tEnter 5 for Search/Sort Admin" << endl;
        cout << "\t\t\t\t\tEnter 6 for Go Back to Admin Panel" << endl;
        cout << "\t\t\t\t\tYour Choice:";
        cin >> updatechoice;
        cin.ignore();
        if (updatechoice == 1) {
            NewAdmin();
        } else if (updatechoice == 2) {
            string adminName, newPassword;
            cout << "Enter admin name to update: ";
            cin >> adminName;
            cout << "Enter new password: ";
            cin >> newPassword;
            UpdateAdmin(adminName, newPassword);
        } else if (updatechoice == 3) {
            string adminToDelete;
            cout << "Enter the name of the admin to delete: ";
            cin >> adminToDelete;
            cin.ignore(); // Clear the input buffer
            deleteAdmin(adminToDelete);
            system("Pause");
            system("cls");
            adminpage();
        } else if (updatechoice == 4) {
            viewDeletionLog();
            system("Pause");
            system("cls");
            adminpage();
        } else if (updatechoice == 5) {
            char searchsortadmin;
                    cout << "\t\t\t\t\t-------------------------------------" << endl;
                    cout << "\t\t\t\t\tEnter 1 to Search Admin "<< endl;
                    cout << "\t\t\t\t\tEnter 2 to Sort Admin" << endl;
                    cout << "\t\t\t\t\tEnter 3 for Go Back to Admin Panel" << endl;
                    cout << "\t\t\t\t\tYour Choice: ";
                    cin >> searchsortadmin;
                    
                    switch(searchsortadmin){
                        case '1':
                        {
                            string adminname;
                            cout << "Enter Admin Name to Search: ";
                            cin.ignore(); // Ignore newline character left in input buffer
                            getline(cin, adminname); // Read full vendor name including spaces if any
                            binarySearchAdmin(adminname);
                        }
                        case '2':
                        {
                            //sort function
                        }
                        case '3' :
            				system("Pause");
                            system("cls");
                            adminpage();
                            return; 
                        default:
                            cout << "Invalid choice. Please enter a valid option (1-3)" << endl;
                    }
        } else if (updatechoice == 6) {
            system("cls");
            adminpage();
        } else {
            cout << "Invalid choice. Please enter a valid option (1-6)" << endl;
            system("Pause");
            system("cls");
            adminpage();
        }
    }
    
// binary search admin function
void binarySearchAdmin(const string& adminName) {
    ifstream file("admin_login.txt");
    
    if (file.is_open()) {
        string line;
        bool found = false;
        
        // Read each line and search for vendorName
        while (getline(file, line)) {
            size_t pos1 = line.find(' '); // Find the first space (assumes space separates fields)
            if (pos1 == string::npos) continue; // Skip if not found
            
            string currentadminName = line.substr(0, pos1);
            
            // Convert currentVendorName to lower case for case-insensitive comparison
            // (if needed; depends on your data)
            
            if (currentadminName == adminName) {
                found = true;

                // Display the entire vendor details row
                cout << "Admin Found..." << endl;
                cout << "-----------------------------------------------" << endl;
                cout << "Admin Details:" << endl;
                cout << "-----------------------------------------------" << endl;
                cout << "Admin | Password  " << endl;
                cout << "-----------------------------------------------" << endl;
                cout << line << endl;  // Display the entire line
                break;
            }
        }
        
        if (!found) {
            cout << "Admin '" << adminName << "' not found." << endl;
        }
        
        file.close();
    } else {
        cout << "Error opening user file." << endl;
    }
}

    
//Get time
string getCurrentTime() 
{ 
    time_t currentTime;
    struct tm* timeInfo;
    char buffer[80];

    time(&currentTime);
    timeInfo = localtime(&currentTime);

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
    return buffer;
}

    bool validpassword(const string& password) {
        bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
        for (char c : password) {
            if (isupper(c)) hasUpper = true;
            else if (islower(c)) hasLower = true;
            else if (isdigit(c)) hasDigit = true;
            else if (ispunct(c)) hasSpecial = true;
        }
        return password.length() >= 8 && hasUpper && hasLower && hasDigit && hasSpecial;
    }

    string GetHiddenPassword() {
        string password;
        char ch;
        while ((ch = _getch()) != '\r') { // '\r' is the Enter key
            if (ch == '\b') { // Handle backspace
                if (!password.empty()) {
                    cout << "\b \b";
                    password.pop_back();
                }
            } else {
                cout << '*';
                password += ch;
            }
        }
        cout << endl;
        return password;
    }

void optionbooking() {
    int viewchoice;
    cout << "\t\t\t\t\t-------------------------------------" << endl;
    cout << "\t\t\t\t\tEnter 1 for View All Booking" << endl;
    cout << "\t\t\t\t\tEnter 2 for Search/Sort Booking" << endl;
    cout << "\t\t\t\t\tEnter 3 for Cancel Booking" << endl;
    cout << "\t\t\t\t\tEnter 4 for View User Cancel Reason" << endl;
    cout << "\t\t\t\t\tEnter 5 for Go Back to Admin Panel" << endl;
    cout << "\t\t\t\t\tYour Choice:";
    cin >> viewchoice;

    switch (viewchoice) {
        case 1:
            viewBooking();
            system("Pause");
            system("cls");
            adminpage();
            break;
        case 2: {
            char searchsortbooking;
            cout << "\t\t\t\t\t-------------------------------------" << endl;
            cout << "\t\t\t\t\tEnter 1 to Search Booking "<< endl;
            cout << "\t\t\t\t\tEnter 2 to Sort Booking" << endl;
            cout << "\t\t\t\t\tEnter 3 for Go Back to Admin Panel" << endl;
            cout << "\t\t\t\t\tYour Choice: ";
            cin >> searchsortbooking;
            
            switch(searchsortbooking){
                case '1':
                {
                    string userbooking;
                    cout << "Enter User Name to Search: ";
                    cin.ignore(); // Ignore newline character left in input buffer
                    getline(cin, userbooking); // Read full vendor name including spaces if any
                    binarySearchBooking(userbooking);
                    system("Pause");
                    system("cls");
                    adminpage();
                    break;
                }
                case '2':
                    // sort function
                    break;
                case '3':
                    system("Pause");
                    system("cls");
                    adminpage();
                    break;
                default:
                    cout << "Invalid choice. Please enter a valid option (1-3)" << endl;
                    break;
            }
            break;
        }
        case 3: {
            string usernameToDelete;
            cout << "Enter the username to cancel bookings: ";
            cin >> usernameToDelete;
            cancelBookingByUserID(usernameToDelete);
            system("Pause");
            system("cls");
            adminpage();
            break;
        }
        case 4:
            cancelreason();
            system("Pause");
            system("cls");
            adminpage();
            break;
        case 5:
            system("cls");
            adminpage();
            break;
        default:
            cout << "Invalid choice. Please enter a valid option (1-5)" << endl;
            system("Pause");
            system("cls");
            adminpage();
            break;
    }
}

//binary search booking function 
void binarySearchBooking(const string& userBooking) {
    ifstream file("booking_details.txt");
    
    if (file.is_open()) {
        string line;
        bool found = false;
        
        while (getline(file, line)) {
            size_t pos1 = line.find(':'); // Find the first ':' (assuming it separates fields)
            if (pos1 == string::npos) continue; // Skip if not found
            
            string field = line.substr(0, pos1);
            if (field == "User") {
                string username = line.substr(pos1 + 2); // Skip ': ' after field name
                if (username == userBooking) {
                    found = true;
                    cout << "Booking Found..." << endl;
                    cout << "================ Booking Details ================" << endl;
                    cout << line << endl;  // Display the entire line
                    // Optionally, print additional lines if needed
                    for (int i = 0; i < 6; ++i) {
                        getline(file, line); // Read next line
                        cout << line << endl; // Display next line
                    }
                    cout << "=================================================" << endl;
                    break;
                }
            }
        }
        
        if (!found) {
            cout << "User '" << userBooking << "' not found." << endl;
        }
        
        file.close();
    } else {
        cout << "Error opening user file." << endl;
    }
}
 
 void cancelBookingByUserID(const string& userID) {
    ifstream inFile("booking_details.txt");
    ofstream cancelReasonFile("cancellation_log.txt", ios::app); // New file for cancel reasons

    if (!inFile.is_open() ||!cancelReasonFile.is_open()) {
        cout << "Error opening files." << endl;
        return;
    }

    list<Booking> bookings;
    string line, bookingDetails;
    bool bookingFound = false;
    while (getline(inFile, line)) {
        istringstream iss(line);
        string token;
        if (iss >> token && token == "User:") {
            string userIDFromLine;
            if (iss >> userIDFromLine) {
                if (userIDFromLine == userID) {
                    bookingFound = true;

                    // Store booking details
                    bookingDetails = "User: " + userIDFromLine + "\n";
                    for (int i = 0; i < 8; ++i) {
                        getline(inFile, line);
                        bookingDetails += line + "\n";
                    }
                    cout << bookingDetails;
                    cout << "Do you want to cancel this booking? (yes/no): ";
                    string confirmation;
                    cin >> confirmation;
                    if (confirmation!= "yes") {
                        cout << "Cancellation aborted." << endl;
                        bookings.emplace_back(Booking{userIDFromLine, bookingDetails});
                        continue;
                    }

                    cout << "Enter the reason for cancellation: ";
                    cin.ignore(); 
                    string cancelReason;
                    getline(cin, cancelReason);

                    // Save the cancel reason to the cancelReasonFile
                    cancelReasonFile << "User ID: Admin" << "\n";
                    cancelReasonFile << "Cancel Reason: " << cancelReason << "\n";
                    cancelReasonFile << "Booking Details:\n" << bookingDetails << "\n";

                    cout << "\033[1;32mBooking for user ID " << userID << " has been canceled.\033[0m" << endl;
                } else {
                    bookings.emplace_back(Booking{userIDFromLine, line + "\n"});
                }
            } else {
                cout << "Error parsing line: " << line << endl;
            }
        } else {
            bookings.emplace_back(Booking{"", line + "\n"});
        }
    }

    inFile.close();
    cancelReasonFile.close();

    if (!bookingFound) {
        cout << "No booking found for user ID " << userID << "." << endl;
    } else {
        // Write the updated bookings back to the file
        ofstream outFile("booking_details.txt");
        for (const auto& booking : bookings) {
            outFile << booking.details;
        }
        outFile.close();
    }
}

   void viewBooking() 
	{
      ifstream file("booking_details.txt");
    
      if (file.is_open()) {
        string line;
        cout << "================ Booking Details ================" << endl;

        while (getline(file, line)) {
            cout << line << endl;
        }
        cout << "=================================================" << endl;

        file.close();
        } else {
        cout << "Error opening booking file." << endl;
        }
    }
    
 void cancelreason()
 {
 	ifstream file("cancellation_log.txt");
 	if (!file.is_open() || !file.is_open()) {
        cout << "Error opening files." << endl;
        return;
    }else if(file.is_open()){
    	string line;
    	cout << "==================== Reason Cancel ====================" << endl;
    	while(getline(file,line)){
    		SetConsoleTextAttribute(h,4);
    		cout<<line<<endl;
    		SetConsoleTextAttribute(h, 15);
		}
		cout << "=======================================================" << endl;
	}
 }
 
void viewUserDeletionLog() {
    ifstream logFile("user_deletion_log.txt");
    if (logFile.is_open()) {
        string line;
        cout << "================ Vendor Deleted ================" << endl;
        while (getline(logFile, line)) {
            cout << line << endl;
        }
        cout << "===================================================" << endl;
        logFile.close();
    } else {
        cout << "Unable to open user deletion log file." << endl;
    }
}

    void calculateBookingCounts() {
      ifstream file("booking_details.txt");

      if (file.is_open()) {
        map<string, int> bookingCounts; // Map to store the booking counts for each service type
        string line, serviceType;

        while (getline(file, line)) {
            if (line.find("Service Type: ") != string::npos) {
                size_t startPos = line.find("Service Type: ") + 14;
                size_t endPos = line.find("\n", startPos);
                serviceType = line.substr(startPos, endPos - startPos);

                bookingCounts[serviceType]++;
            }
        }

        file.close();

        // Display the booking counts
        cout << "============= Service Type =============" << endl;
        for (map<string, int>::iterator it = bookingCounts.begin(); it != bookingCounts.end(); ++it) {
          cout << it->first << ": " << it->second << " bookings" <<endl<<endl;;
        }
        cout << "========================================" << endl;
      } else {
        cout << "Error opening booking file." << endl;
     }
   }

void deleteUser(const string& username) {
    ifstream inFile("user_data.txt");
    ofstream outFile("temp_user_data.txt");
    ofstream deletionLog("user_deletion_log.txt", ios::app); // Open for appending

    if (!inFile.is_open() || !outFile.is_open() || !deletionLog.is_open()) {
        cout << "Error opening files." << endl;
        return;
    }

    bool userFound = false;
    string line;

    while (getline(inFile, line)) {
        istringstream iss(line);
        string usernameFromLine;
        if (iss >> usernameFromLine) {
            if (usernameFromLine == username) {
                userFound = true;
                cout << "Do you want to delete Vendor " << username << "? (yes/no): ";
                string confirmation;
                cin >> confirmation;
                if (confirmation == "yes" || confirmation == "YES") {
                    string deletionTime = getCurrentTime();
                    cout << "\033[1;32mUser " << username << " has been deleted at " << deletionTime << ".\033[0m" << endl;
                    deletionLog << "Vendor " << username << " has been deleted at " << deletionTime << "." << endl;
                } else {
                    cout << "Vendor " << username << " has been canceled." << endl;
                    outFile << line << endl; // Write back the user data if not deleted
                }
            } else {
                outFile << line << endl;
            }
        }
    }

    inFile.close();
    outFile.close();
    deletionLog.close();

    if (!userFound) {
        cout << "No user found with Vendor " << username << "." << endl;
    }
    remove("user_data.txt");
    rename("temp_user_data.txt", "user_data.txt");
}

//binary search vendor function
void binarySearchVendor(const string& vendorName) {
    ifstream file("user_data.txt");
    
    if (file.is_open()) {
        string line;
        bool found = false;
        
        // Read each line and search for vendorName
        while (getline(file, line)) {
            size_t pos1 = line.find(' '); // Find the first space (assumes space separates fields)
            if (pos1 == string::npos) continue; // Skip if not found
            
            string currentVendorName = line.substr(0, pos1);
            
            // Convert currentVendorName to lower case for case-insensitive comparison
            // (if needed; depends on your data)
            
            if (currentVendorName == vendorName) {
                found = true;

                // Display the entire vendor details row
                cout << "Vendor Found..." << endl;
                cout << "-----------------------------------------------" << endl;
                cout << "Vendor Details:" << endl;
                cout << "-----------------------------------------------" << endl;
                cout << "Vendor name |   Password  |     Email" << endl;
                cout << "-----------------------------------------------" << endl;
                cout << line << endl;  // Display the entire line
                break;
            }
        }
        
        if (!found) {
            cout << "Vendor '" << vendorName << "' not found." << endl;
        }
        
        file.close();
    } else {
        cout << "Error opening user file." << endl;
    }
}


  void viewuser() {
    char choiceuser;

    while (true) {
        cout << "\t\t\t\t\t-------------------------------------" << endl;
        cout << "\t\t\t\t\tEnter 1 for View Vendor Details" << endl;
        cout << "\t\t\t\t\tEnter 2 for Search/Sort Vendor" << endl;
        cout << "\t\t\t\t\tEnter 3 for Delete Vendor" << endl;
        cout << "\t\t\t\t\tEnter 4 for View Deleted Vendor" << endl;
        cout << "\t\t\t\t\tEnter 5 for Go Back to Admin Panel" << endl;
        cout << "\t\t\t\t\tYour Option:";
        cin >> choiceuser;

        switch (choiceuser) {
            case '1':
                {
                    ifstream file("user_data.txt");

                    if (file.is_open()) {
                        string line;
                        cout << "-----------------------------------------------" << endl;
                        cout << "Vendor Details:" << endl;
                        cout << "-----------------------------------------------" << endl;
                        cout << "Vendor name |   Password  |     Email" << endl;
                        cout << "-----------------------------------------------" << endl;

                        while (getline(file, line)) {
                            cout<<line<<endl;
                        }

                        file.close();
                    } else {
                        cout << "Error opening user file." << endl;
                    }
                }
                break;
            case '2':
                {
                    char searchsortchoice;
                    cout << "\t\t\t\t\t-------------------------------------" << endl;
                    cout << "\t\t\t\t\tEnter 1 to Search Vendor "<< endl;
                    cout << "\t\t\t\t\tEnter 2 to Sort Vendor" << endl;
                    cout << "\t\t\t\t\tEnter 3 for Go Back to Admin Panel" << endl;
                    cout << "\t\t\t\t\tYour Choice: ";
                    cin >> searchsortchoice;
                    
                    switch(searchsortchoice){
                        case '1':
                        {
                            string vendorname;
                            cout << "Enter Vendor Name to Search: ";
                            cin.ignore(); // Ignore newline character left in input buffer
                            getline(cin, vendorname); // Read full vendor name including spaces if any
                            binarySearchVendor(vendorname);
                        }
                        case '2':
                        {
                            //sort function
                        }
                        case '3' :
            				system("Pause");
                            system("cls");
                            adminpage();
                            return; 
                        default:
                            cout << "Invalid choice. Please enter a valid option (1-3)" << endl;
                    }
                    
                }
                break;
            case '3':
            	{
            		string usernameToDelete;
                    cout << "Enter the username to delete: ";
                    cin >> usernameToDelete;
                    deleteUser(usernameToDelete);
				}
                break;
            case '4':
            	viewUserDeletionLog();
                system("Pause");
                system("cls");
                adminpage();
			case '5' :
				system("Pause");
                system("cls");
                adminpage();
                return; 
            default:
                cout << "Invalid choice. Please enter a valid option (1-5)" << endl;
        }
    }
}
    
    void profit();
       
   
   friend class booking;
};

//Admin Exit
void exitAdminPage() {
        system("cls");
        char exitChoice;
        cout<<"-----------------------------" << endl;
        cout<<"| Confirm to Exit? (Y/N) |" << endl; 
        cout<<"-----------------------------" << endl;
        cout<<"> ";
        cin>> exitChoice;
        exitChoice = toupper(exitChoice);
        if(exitChoice == 'Y') {
        	SetConsoleTextAttribute(h,9);
            cout << "Exiting..." << endl;
            cout << "Goodbye, have a great day!"<< endl; 
            SetConsoleTextAttribute(h,15);
            exit(0);
        }else if(exitChoice == 'N') {
            system("cls");
            adminpage();
        }else{
            cout<<"Invalid Option. Please Try Again (Y/N)" << endl;
            system("Pause");
            system("cls");
            adminpage();
        }
    }

void adminpage() {
    adminpanel ap;
    int adoption;
    char exitChoice;
    SetConsoleTextAttribute(h, 15);
    cout << "\t\t\t\t\t=========================================" << endl;
    cout << "\t\t\t\t\t|\t\tAdmin Page\t\t|" << endl;
    cout << "\t\t\t\t\t=========================================" << endl;
    cout << "\t\t\t\t\t|  Press 1 to View/Delete User         |" << endl;
    cout << "\t\t\t\t\t|  Press 2 to View/Cancel Booking      |" << endl;
    cout << "\t\t\t\t\t|  Press 3 to View Total Profit/Vendor |" << endl;
    cout << "\t\t\t\t\t|  Press 4 to View Categories          |" << endl;
    cout << "\t\t\t\t\t|  Press 5 to Update Admin Information |" << endl;
    cout << "\t\t\t\t\t|  Press 6 to View User Feedback       |" << endl; 
    cout << "\t\t\t\t\t|  Press 7 to Exit                     |" << endl; 
    cout << "\t\t\t\t\tEnter Your Option :";
    cin >> adoption;

    switch (adoption) {
        case 1:
            ap.viewuser();
            system("cls");
            break;
        case 2:
            ap.optionbooking();
            system("cls");
            break;
        case 3:
            ap.profit();
            system("Pause");
            system("cls");
            adminpage();
            break;
        case 4:
            ap.calculateBookingCounts();
            system("Pause");
            system("cls");
            adminpage();
            break;
        case 5:
            ap.addinAdmin();
            system("Pause");
            system("cls");
            adminpage();
            break;
        case 6:
            viewFeedback();
            system("cls");
            adminpage();
            break;
        case 7:
            system("cls");
            exitAdminPage();
            break;
        default:
            cout << "\t\t\t\t\tInvalid option. Please Try Again(1-8)" << endl;
            system("Pause");
            system("cls");
            adminpage();
    }
}

void adminpanel::profit() {
    ifstream file("booking_details.txt");

    if (file.is_open()) {
        double totalProfit = 0.0;
        set<string> uniqueVendors; // Set to store unique vendor names
        string line, name;
        while (getline(file, line)) {
            if (line.find("Vendor Company Name: ") != string::npos) {
                size_t pos = line.find("Vendor Company Name: ") + 19;
                name = line.substr(pos); // Extract vendor name
                uniqueVendors.insert(name); // Insert the vendor name into the set
            }

            if (line.find("Total Price: RM") != string::npos) {
                size_t pos = line.find("Total Price: RM") + 15;
                string total = line.substr(pos);
                // Calculate profit and update the total profit
                if (!total.empty()) {
                    double price = atof(total.c_str()); // Use atof for string-to-double conversion
                    totalProfit += price;
                }
            }
        }

        cout << "Total Profit: RM" << totalProfit << endl;
        cout << "Total Vendors: " << uniqueVendors.size() << endl;
        cout << "======== List of Company Names ========" << endl;

        int count = 1;
        for (set<string>::iterator it = uniqueVendors.begin(); it != uniqueVendors.end(); ++it) 
		{
          cout << count << ". " << *it << endl;
          count++;
        }

        cout << "====================================" << endl;

        file.close();
        } else {
          cout << "Error opening booking file." << endl;
        }
}

//LInked list Booking
class booking {
private:
    Node* head;
    Node* tail;

public:
    // Constructor
    booking() : head(nullptr), tail(nullptr) {}

    // Destructor
    ~booking() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    // Method to set vendor company name for booking
    void setName() {
        string nameInput;
        cout << "Vendor Company Name: ";
        getline(cin, nameInput);

        Node* newNode = new Node;
        newNode->name = nameInput;

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Method to set contact number for booking
    void setContact() {
        string contactInput;
        cout << "Contact No: ";
        getline(cin, contactInput);
        tail->contact = contactInput;
    }

    // Method to set event group for booking
    void setEventGroup() {
        char eventInput;
        cout << "Event [A] Food Feasta Carnival Kuala Lumpur" << endl;
        cout << "From 3 March 2024 - 13 March 2024" << endl;
        cout << "Event [B] Food Feasta Carnival Johor" << endl;
        cout << "From 17 March 2024 - 27 March 2024" << endl;
        cout << "Which Event you will join (A/B): ";
        cin >> eventInput;
        cin.ignore(); // Consume newline character

        while (eventInput != 'A' && eventInput != 'B') {
            cout << "Invalid Event. Please Reenter (A/B): ";
            cin >> eventInput;
            cin.ignore(); // Consume newline character
        }

        tail->eventgrp = eventInput;
    }

    // Method to set duration (days) for booking
    void setDuration() {
        int durationInput;
        cout << "Duration (Days): ";
        cin >> durationInput;
        cin.ignore(); // Consume newline character
        tail->duration = durationInput;
    }

    // Method to set user ID for booking
    void setUserID(const string& userIdfile) {
        tail->userID = userIdfile;
    }

    // Method to set service category for booking
    void service_cat() {
        char codeInput;
        cout << "[A] Food & Beverages" << endl;
        cout << "[B] Art & Craft" << endl;
        cout << "[C] Accessories" << endl;
        cout << "[D] Stationeries" << endl;
        cout << "[E] Home & Living" << endl;
        cout << "Service Category (A-E): ";
        cin >> codeInput;
        cin.ignore(); // Consume newline character

        switch (codeInput) {
            case 'A':
            case 'a':
                tail->service_type = "Food & Beverages";
                break;
            case 'B':
            case 'b':
                tail->service_type = "Art & Craft";
                break;
            case 'C':
            case 'c':
                tail->service_type = "Accessories";
                break;
            case 'D':
            case 'd':
                tail->service_type = "Stationeries";
                break;
            case 'E':
            case 'e':
                tail->service_type = "Home & Living";
                break;
            default:
                tail->service_type = "Others";
                break;
        }
    }

    // Method to set booth location for booking
   void booth_location() {
    char boothInput;
    string boothNumber;
    cout << "[A] Lot A, Price = RM900" << endl;
    cout << "[B] Lot B, Price = RM650" << endl;
    cout << "[C] Lot C, Price = RM550" << endl;
    cout << "Booth Location (A/B/C): ";
    cin >> boothInput;
    cin.ignore(); // Consume newline character

    while (boothInput != 'A' && boothInput != 'B' && boothInput != 'C') {
        cout << "Invalid Booth Location. Please Reenter (A/B/C): ";
        cin >> boothInput;
        cin.ignore(); // Consume newline character
    }

   
    tail->booth = boothInput;
    tail->total = calculateBoothPrice(boothInput); // Calculate and store booth price
}

    // Method to get event date based on event group
    string getEventDate() const {
        if (tail->eventgrp == 'A' || tail->eventgrp == 'a') {
            return "3 March 2024 - 13 March 2024";
        } else {
            return "17 March 2024 - 27 March 2024";
        }
    }
    
    int getBoothNumber(char booth) {
        static int boothNumberA = 1;
        static int boothNumberB = 1;
        static int boothNumberC = 1;

        switch (booth) {
            case 'A':
                return boothNumberA++;
            case 'B':
                return boothNumberB++;
            case 'C':
                return boothNumberC++;
            default:
                cerr << "Invalid booth location" << endl;
                return -1; // or handle error as needed
        }
    }

    // Method to calculate booth price based on location
    float calculateBoothPrice(char booth) const {
        switch (booth) {
            case 'A':
                return 900.0f;
            case 'B':
                return 650.0f;
            case 'C':
                return 550.0f;
            default:
                return 0.0f; // Default case should ideally not be reached due to validation in booth_location()
        }
    }

    // Method to save booking details to file
    void saveBookingToFile() {
    ofstream file("booking_details.txt", ios::app);
    if (file.is_open()) {
        file << "User: " << tail->userID << endl;
        file << "Vendor Company Name: " << tail->name << endl;
        file << "Contact: " << tail->contact << endl;
        file << "Event Date: " << getEventDate() << endl;
        file << "Service Type: " << tail->service_type << endl;
        file << "Booth Location: " << tail->booth << endl;
        file << "Booth Number: " << tail->booth <<getBoothNumber(tail->booth) << endl; // Include booth number
        file << "Total Price: RM" << tail->total << endl;
        file << endl << endl;

        cout << "Booking details saved to file." << endl;
    } else {
        cout << "Error opening file to save booking details." << endl;
    }
    file.close();
}

    // Method to display all bookings from file
    void displayAllBookings() const {
        ifstream file("booking_details.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        } else {
            cout << "Error opening file to display booking details." << endl;
        }
    }

    // Method to edit a booking based on user ID
void editBooking(const string& userID) {
	
	ifstream inputFile("booking_details.txt");
    ofstream tempFile("temp_booking_details.txt");
    unordered_map<string, BookingDetails> bookingMap;
    vector<BookingDetails> bookings;
    string searchVendorName;
    bool found = false;

    // Read and store all bookings in a vector
    if (inputFile.is_open()) {
        string line;
        BookingDetails bd;
        bool isCurrentUser = false;

        while (getline(inputFile, line)) {
            if (line.find("User: ") != string::npos) {
                bd.user = line.substr(6);
                isCurrentUser = (bd.user == userID);
            }

            if (isCurrentUser) {
                if (line.find("Vendor Company Name: ") != string::npos) {
                    bd.vendorName = line.substr(21);
                } else if (line.find("Contact: ") != string::npos) {
                    bd.contact = line.substr(9);
                } else if (line.find("Event Date: ") != string::npos) {
                    bd.eventDate = line.substr(12);
                } else if (line.find("Service Type: ") != string::npos) {
                    bd.serviceType = line.substr(14);
                } else if (line.find("Booth Location: ") != string::npos) {
                    bd.booth = line[16];
                } else if (line.find("Booth Number: ") != string::npos) {
                    bd.boothNumber = line.substr(14);
                } else if (line.find("Total Price: RM") != string::npos) {
                    bd.totalPrice = stof(line.substr(15));
                    bookingMap[bd.vendorName] = bd;
                    bookings.push_back(bd);
                    isCurrentUser = false; // Reset for the next entry
                }
            }
        }
        inputFile.close();
    } else {
        cout << "Error opening booking details file." << endl;
        return;
    }

    // Display all bookings in a table format
    cout << "-------------Current Booking Details-----------" << endl;
    cout << left << setw(15) << "Vendor Name" << setw(12) << "Contact" << setw(30) << "Event Date" << setw(20) << "Service Type" << setw(15) << "Booth" << setw(15) << "Booth Number" << setw(15) << "Total Price" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    for (const auto& booking : bookings) {
        cout << left << setw(15) << booking.vendorName << setw(12) << booking.contact << setw(30) << booking.eventDate << setw(20) << booking.serviceType << setw(15) << booking.booth << setw(15) << booking.boothNumber << "RM" << booking.totalPrice << endl;
    }
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;

    // Prompt the user to choose which booking to update
    cout << "Enter the Vendor Company Name you want to update (or type 'exit' to cancel): ";
    getline(cin, searchVendorName);
    if (searchVendorName == "exit") {
        cout << "Update canceled." << endl;
        return; // Exit the function
    }

    auto it = bookingMap.find(searchVendorName);
    if (it != bookingMap.end()) {
        found = true;
        BookingDetails& bd = it->second;

        cout << "Booking found. You can now update it." << endl;
        cout << "Vendor Company Name: ";
        getline(cin, bd.vendorName);
        cout << "Contact No: ";
        getline(cin, bd.contact);
        cout << "Event [A] Food Feasta Carnival Kuala Lumpur\n";
        cout << "From 3 March 2024 - 13 March 2024\n";
        cout << "Event [B] Food Feasta Carnival Johor\n";
        cout << "From 17 March 2024 - 27 March 2024\n";
        cout << "Which Event you will join (A/B): ";
        char eventInput;
        cin >> eventInput;
        cin.ignore(); // Consume newline character
        bd.eventDate = (eventInput == 'A' || eventInput == 'a') ? "3 March 2024 - 13 March 2024" : "17 March 2024 - 27 March 2024";

        cout << "[A] Food & Beverages\n[B] Art & Craft\n[C] Accessories\n[D] Stationeries\n[E] Home & Living\n";
        cout << "Service Category (A-E): ";
        char serviceInput;
        cin >> serviceInput;
        cin.ignore(); // Consume newline character
        switch (serviceInput) {
            case 'A': case 'a': bd.serviceType = "Food & Beverages"; break;
            case 'B': case 'b': bd.serviceType = "Art & Craft"; break;
            case 'C': case 'c': bd.serviceType = "Accessories"; break;
            case 'D': case 'd': bd.serviceType = "Stationeries"; break;
            case 'E': case 'e': bd.serviceType = "Home & Living"; break;
            default: bd.serviceType = "Others"; break;
        }

        cout << "[A] Lot A, Price = RM900\n[B] Lot B, Price = RM650\n[C] Lot C, Price = RM550\n";
        cout << "Booth Location (A/B/C): ";
        char boothInput;
        cin >> boothInput;
        cin.ignore(); // Consume newline character
        bd.booth = boothInput;
        bd.totalPrice = (boothInput == 'A') ? 900.0f : (boothInput == 'B') ? 650.0f : 550.0f;
        bd.boothNumber = bd.booth + to_string((boothInput == 'A') ? 1 : (boothInput == 'B') ? 2 : 3); // Example logic to set booth number

        // Write all updated bookings to the temp file
        for (const auto& pair : bookingMap) {
            const auto& b = pair.second;
            tempFile << "User: " << b.user << endl;
            tempFile << "Vendor Company Name: " << b.vendorName << endl;
            tempFile << "Contact: " << b.contact << endl;
            tempFile << "Event Date: " << b.eventDate << endl;
            tempFile << "Service Type: " << b.serviceType << endl;
            tempFile << "Booth Location: " << b.booth << endl;
            tempFile << "Booth Number: " << b.boothNumber << endl;
            tempFile << "Total Price: RM" << b.totalPrice << endl << endl;
        }

        cout << "Booking updated successfully!" << endl;
        
        cin.ignore();
    } else {
        cout << "No booking found for Vendor Company Name: " << searchVendorName << "." << endl;
    }

    tempFile.close();

    if (found) {
        remove("booking_details.txt");
        rename("temp_booking_details.txt", "booking_details.txt");

        // Display the updated table
            bookings.clear();
        ifstream updatedFile("booking_details.txt");
        if (updatedFile.is_open()) {
            string line;
            while (getline(updatedFile, line)) {
                BookingDetails bd;
                if (line.find("User: ") != string::npos) {
                    bd.user = line.substr(6);
                    getline(updatedFile, line);
                    bd.vendorName = line.substr(21);
                    getline(updatedFile, line);
                    bd.contact = line.substr(9);
                    getline(updatedFile, line);
                    bd.eventDate = line.substr(12);
                    getline(updatedFile, line);
                    bd.serviceType = line.substr(14);
                    getline(updatedFile, line);
                    bd.booth = line[16];
                    getline(updatedFile, line);
                    bd.boothNumber = line.substr(14);
                    getline(updatedFile, line);
                    bd.totalPrice = stof(line.substr(15));
                    bookings.push_back(bd);
                }
            }
            updatedFile.close();
        }

        // Display the updated table
        system("cls");
        cout << "-------------Updated Booking Details-----------" << endl;
        cout << left << setw(15) << "Vendor Name" << setw(12) << "Contact" << setw(30) << "Event Date" << setw(20) << "Service Type" << setw(15) << "Booth" << setw(15) << "Booth Number" << setw(15) << "Total Price" << endl;
        cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
        for (const auto& booking : bookings) {
            cout << left << setw(15) << booking.vendorName << setw(12) << booking.contact << setw(30) << booking.eventDate << setw(20) << booking.serviceType << setw(15) << booking.booth << setw(15) << booking.boothNumber << "RM" << booking.totalPrice << endl;
        }
        cout << "---------------------------------------------------------------------------------------------------------------------" << endl;

        cout << "Press Enter to continue...";
        cin.ignore();
    }
}


    // Method to cancel a booking based on user ID
    void cancelBooking(const string& userID) {
        ifstream inputFile("booking_details.txt");
    ofstream tempFile("temp_booking_details.txt");
    unordered_map<string, BookingDetails> bookingMap;
    vector<BookingDetails> bookings;
    string searchVendorName;
    bool found = false;

    // Read and store all bookings in a vector
    if (inputFile.is_open()) {
        string line;
        BookingDetails bd;
        bool isCurrentUser = false;

        while (getline(inputFile, line)) {
            if (line.find("User: ") != string::npos) {
                bd.user = line.substr(6);
                isCurrentUser = (bd.user == userID);
            }

            if (isCurrentUser) {
                if (line.find("Vendor Company Name: ") != string::npos) {
                    bd.vendorName = line.substr(21);
                } else if (line.find("Contact: ") != string::npos) {
                    bd.contact = line.substr(9);
                } else if (line.find("Event Date: ") != string::npos) {
                    bd.eventDate = line.substr(12);
                } else if (line.find("Service Type: ") != string::npos) {
                    bd.serviceType = line.substr(14);
                } else if (line.find("Booth Location: ") != string::npos) {
                    bd.booth = line[16];
                } else if (line.find("Booth Number: ") != string::npos) {
                    bd.boothNumber = line.substr(14);
                } else if (line.find("Total Price: RM") != string::npos) {
                    bd.totalPrice = stof(line.substr(15));
                    bookingMap[bd.vendorName] = bd;
                    bookings.push_back(bd);
                    isCurrentUser = false; // Reset for the next entry
                }
            }
        }
        inputFile.close();
    } else {
        cout << "Error opening booking details file." << endl;
        return;
    }

    // Display all bookings in a table format
    cout << "-------------Current Booking Details-----------" << endl;
    cout << left << setw(15) << "Vendor Name" << setw(12) << "Contact" << setw(30) << "Event Date" << setw(20) << "Service Type" << setw(15) << "Booth" << setw(15) << "Booth Number" << setw(15) << "Total Price" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    for (const auto& booking : bookings) {
        cout << left << setw(15) << booking.vendorName << setw(12) << booking.contact << setw(30) << booking.eventDate << setw(20) << booking.serviceType << setw(15) << booking.booth << setw(15) << booking.boothNumber << "RM" << booking.totalPrice << endl;
    }
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;

    // Prompt the user to choose which booking to cancel
    cout << "Enter the Vendor Company Name you want to cancel (or type 'exit' to cancel): ";
    getline(cin, searchVendorName);
    if (searchVendorName == "exit") {
        cout << "Cancellation canceled." << endl;
        return; // Exit the function
    }

    auto it = bookingMap.find(searchVendorName);
    if (it != bookingMap.end()) {
        found = true;
        BookingDetails& bd = it->second;

        cout << "Booking found. Do you want to cancel it? (yes/no): ";
        string confirmation;
        cin >> confirmation;
        cin.ignore(); // Consume newline character

        if (confirmation == "yes" || confirmation == "YES") {
            string cancelReason;
            cout << "Enter the reason for cancellation: ";
            getline(cin, cancelReason);

            // Save the cancel reason to the cancelReasonFile
            ofstream cancelReasonFile("cancellation_log.txt", ios::app);
            if (cancelReasonFile.is_open()) {
                cancelReasonFile << "User ID: " << userID << "\n";
                cancelReasonFile << "Cancel Reason: " << cancelReason << "\n";
                cancelReasonFile << "Booking Details:\n";
                cancelReasonFile << "Vendor Company Name: " << bd.vendorName << "\n";
                cancelReasonFile << "Contact: " << bd.contact << "\n";
                cancelReasonFile << "Event Date: " << bd.eventDate << "\n";
                cancelReasonFile << "Service Type: " << bd.serviceType << "\n";
                cancelReasonFile << "Booth Location: " << bd.booth << "\n";
                cancelReasonFile << "Booth Number: " << bd.boothNumber << "\n";
                cancelReasonFile << "Total Price: RM" << bd.totalPrice << "\n\n";
                cancelReasonFile.close();
            } else {
                cout << "Error opening cancellation log file." << endl;
            }

            // Remove the booking from the vector and the map
            bookings.erase(remove_if(bookings.begin(), bookings.end(),
                [&bd](const BookingDetails& booking) { return booking.vendorName == bd.vendorName; }),
                bookings.end());
            bookingMap.erase(it);

            cout << "\033[1;32mBooking for vendor company name " << searchVendorName << " has been canceled.\033[0m" << endl;
            cin.ignore();
        } else {
            cout << "Cancellation aborted." << endl;
        }
    } else {
        cout << "No booking found for Vendor Company Name: " << searchVendorName << "." << endl;
    }

    // Write all remaining bookings to the temp file
    for (const auto& booking : bookings) {
        tempFile << "User: " << booking.user << endl;
        tempFile << "Vendor Company Name: " << booking.vendorName << endl;
        tempFile << "Contact: " << booking.contact << endl;
        tempFile << "Event Date: " << booking.eventDate << endl;
        tempFile << "Service Type: " << booking.serviceType << endl;
        tempFile << "Booth Location: " << booking.booth << endl;
        tempFile << "Booth Number: " << booking.boothNumber << endl;
        tempFile << "Total Price: RM" << booking.totalPrice << endl << endl;
    }

    tempFile.close();

    remove("booking_details.txt");
    rename("temp_booking_details.txt", "booking_details.txt");
    
    system("cls");
    cout << "-------------Updated Booking Details-----------" << endl;
    cout << left << setw(15) << "Vendor Name" << setw(12) << "Contact" << setw(30) << "Event Date" << setw(20) << "Service Type" << setw(15) << "Booth" << setw(15) << "Booth Number" << setw(15) << "Total Price" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    for (const auto& booking : bookings) {
        cout << left << setw(15) << booking.vendorName << setw(12) << booking.contact << setw(30) << booking.eventDate << setw(20) << booking.serviceType << setw(15) << booking.booth << setw(15) << booking.boothNumber << "RM" << booking.totalPrice << endl;
    }
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;

    // Return to the process menu
    cout << "Press Enter to continue...";
    cin.ignore();
    system("cls");
    process_menu(userID);
}

    // Method to display all bookings
    void displayAll() const {
        Node* current = head;
        while (current != nullptr) {
            cout << "User: " << current->userID << endl;
            cout << "Vendor Company Name: " << current->name << endl;
            cout << "Contact: " << current->contact << endl;
            cout << "Event Date: " << getEventDate() << endl;
            cout << "Service Type: " << current->service_type << endl;
            cout << "Booth Location: " << current->booth << endl;
            cout << "Total Price: RM" << current->total << endl;
            cout << endl;
            current = current->next;
        }
    }
};

//show start page
struct ConsoleUtils {
    // Function to move the cursor to a specific position in the console
    void gotoxy(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    // Function to print a string with a delay after each character
    void print_delay(string s, int delay) {
        for (int i = 0; i < s.length(); i++) {
            cout << s[i];
            Sleep(delay); // pause the program for delay milliseconds
        }
    }

   void print_title() {
    system("cls");  // Clear the screen

    // Set the text color to yellow
    system("color 0E");

    const string title = "Welcome to Food Feasta Registration System";
    const int title_length = title.length();
    const int console_width = 80;  // Assuming a standard console width
    int box_width = title_length + 10;  // Increased box width for more padding
    box_width = box_width > console_width ? console_width : box_width; // Ensure box fits in console
    int left_padding = (console_width - box_width) / 2;  // Center the box
    left_padding = left_padding < 0 ? 0 : left_padding;  // Ensure padding is not negative

    // Print top border of the box
    gotoxy(left_padding, 5);
    cout << "+";
    for (int i = 0; i < box_width - 2; i++) cout << "-";
    cout << "+" << endl;

    // Print empty lines inside the box for vertical padding
    for (int line = 0; line < 2; line++) {  // Increased vertical padding
        gotoxy(left_padding, 6 + line);
        cout << "|";
        for (int i = 0; i < box_width - 2; i++) cout << " ";
        cout << "|" << endl;
    }

    // Print title within the box
    gotoxy(left_padding + (box_width - title_length) / 2 - 1, 7);  // Center title
    print_delay(title, 20);
 
    // Print empty lines inside the box for vertical padding
    for (int line = 0; line < 2; line++) {  // Increased vertical padding
        gotoxy(left_padding, 8 + line);
        cout << "|";
        for (int i = 0; i < box_width - 2; i++) cout << " ";
        cout << "|" << endl;
    }

    // Print bottom border of the box
    gotoxy(left_padding, 10);
    cout << "+";
    for (int i = 0; i < box_width - 2; i++) cout << "-";
    cout << "+" << endl;
  }
};

void display_menu(){
	system("cls");
	SetConsoleTextAttribute(h,15);
	cout << "=================================================================" << endl;
	cout << "*\t\t\tWelcome to \t\t\t\t*" << endl;
	cout << "*\tFood Feasta Registration and Vendor Booking System\t*"<<endl;
	cout <<"=================================================================" << endl;
	cout<<"*\t\t    _____\t\t\t\t\t*\n";
   	cout<<"*\t\t   /     \\   ____   ____    __ __\t\t*\n";
   	cout<<"*\t\t  /  \\ /  \\_/ __ \\ /     \\ |  |  |\t\t*\n";
    cout<<"*\t\t /    Y    \\  ___/|   |   \\|  |  |\t\t*\n";
    cout<<"*\t\t \\____|____/\\____>____|____|_____|\t\t*\n";
    cout <<"=================================================================" << endl;
    cout <<endl<< "\t\t1. LOGIN" << endl;
    cout << "\t\t2. REGISTER" << endl;
    cout << "\t\t3. ADMIN PANEL" << endl;
    cout << "\t\t4. EXIT" << endl;
}//end of function display_menu

//Feedback
class FeedbackList {
private:
    FeedbackNode* head;

public:
    FeedbackList() : head(nullptr) {}

    ~FeedbackList() {
        FeedbackNode* current = head;
        while (current != nullptr) {
            FeedbackNode* next = current->next;
            delete current;
            current = next;
        }
    }

    void addFeedback(const string& user, const string& fb, int rate) {
        FeedbackNode* newNode = new FeedbackNode(user, fb, rate);
        if (head == nullptr) {
            head = newNode;
        } else {
            FeedbackNode* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void saveFeedbackToFile() {
        ofstream file("feedback.txt", ios::app);
        if (file.is_open()) {
            FeedbackNode* current = head;
            while (current != nullptr) {
                file << "Username: " << current->username << endl;
                file << "Feedback: " << current->feedback << endl;
                file << "Rating: " << current->rating << "/5" << endl;
                file << endl;
                current = current->next;
            }
            file.close();
            cout << "All feedback and ratings saved successfully!" << endl;
        } else {
            cout << "Error opening file to save feedback." << endl;
        }
    }

    void captureFeedback() {
        string username;
        cout << "Please enter your username: ";
        getline(cin, username);

        string feedback;
        cout << "Please enter your feedback about service or system (type 'exit' on a new line to finish):\n";
        string line;
        bool exitFlag = false;

        do {
            getline(cin, line);
            if (line == "exit") {
                if (!feedback.empty()) {
                    exitFlag = true;
                } else {
                    cout << "Feedback cannot be empty. Please enter your feedback or type 'exit' again to cancel: ";
                }
            } else {
                feedback += line + "\n";
            }
        } while (!exitFlag);

        int rating;
        cout << "Please rate your experience (1-5): ";
        while (!(cin >> rating) || rating < 1 || rating > 5) {
            cout << "Invalid rating. Please enter a number between 1 and 5: ";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
        cin.ignore(); // Ignore remaining newline character

        addFeedback(username, feedback, rating);
        cout << "Thank you for providing feedback! Your rating: " << rating << "/5" << endl;
    }
};

//View Feedback
 void viewFeedback() {
    system("cls");
    ifstream feedbackFile("feedback.txt");

    if (feedbackFile.is_open()) {
        string line;

        cout << "====================== Feedback ======================" << endl;

        while (getline(feedbackFile, line)) {
            cout << line << endl;
        }

        cout << "=====================================================" << endl;

        feedbackFile.close();
    } else {
        cout << "Error opening feedback file." << endl;
    }

    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
    system("cls");
}

void process_menu(const string& Username )
{
	
    while (true) {
        system("cls");
        booking B;
        USER U;
        FeedbackList feedbackList;
        
        int choice;

        cout << "HI, " << Username << " What would you like to do today" << endl;
        cout << "1. Booking" << endl;
        cout << "2. View Booking" << endl;
        cout << "3. Update Booking" << endl;
        cout << "4. Cancel Booking" << endl;
        cout << "5. Provide Feedback" << endl;
        cout << "6. Log Out" << endl;
        cout << "Please Enter your choice :";
        
        
        while (!(cin >> choice) || choice < 1 || choice > 6) 
		{
			cout << "Invalid choice. Please enter a valid option (1-6): ";
            cin.clear();
            cin.ignore();
        }
        cin.ignore();

        if (choice == 1) {
        	system("cls");
            B.setName();
            B.setContact();
			B.setEventGroup();
            B.service_cat();
            B.booth_location();
            
            B.setUserID(Username);
            B.saveBookingToFile();

            cout << "Press Enter to continue...";
			cin.ignore(); 
			cin.get();
        } else if (choice == 2) 
		{
            detaildisplay(Username);
            
        }else if (choice == 3) { 
            system("cls");
           B.editBooking(Username); 
        } else if (choice == 4) 
		{
			
            B.cancelBooking(Username);
            
                break;
        }else if (choice == 5) {
        	system("cls");
    char choice;
    do {
        feedbackList.captureFeedback();
        cout << "Do you want to add another feedback? (y/n): ";
        cin >> choice;
        cin.ignore(); // Ignore remaining newline character
    } while (choice == 'y' || choice == 'Y');

    // Save all feedbacks to file
    feedbackList.saveFeedbackToFile();
            cin.ignore();
            system("cls");
        }else if (choice == 6) 
		{
			system("cls");
			cout<<"=------Thanks"<<" "<<Username<<"------="<< endl;
			exit(0);
			 
        }
    }
}

void merge(vector<BookingDetails>& bookings, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<BookingDetails> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = bookings[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = bookings[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].boothNumber <= R[j].boothNumber) {
            bookings[k] = L[i];
            i++;
        } else {
            bookings[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        bookings[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        bookings[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<BookingDetails>& bookings, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(bookings, left, mid);
        mergeSort(bookings, mid + 1, right);

        merge(bookings, left, mid, right);
    }
}

void insertionSort(vector<BookingDetails>& bookings) {
    int n = bookings.size();
    for (int i = 1; i < n; i++) {
        BookingDetails key = bookings[i];
        int j = i - 1;

        while (j >= 0 && bookings[j].boothNumber > key.boothNumber) {
            bookings[j + 1] = bookings[j];
            j = j - 1;
        }
        bookings[j + 1] = key;
    }
}

bool isFloat(const string& str) {
    stringstream ss(str);
    float f;
    return ss >> f && ss.eof();
}

void detaildisplay(const string& userIdfile) {
    system("cls");
    ifstream file("booking_details.txt");

    if (file.is_open()) {
        vector<BookingDetails> bookings;
        string line;
        bool userFound = false;

        while (getline(file, line)) {
            if (line.find("User: " + userIdfile) != string::npos) {
                BookingDetails bd;
                bd.user = userIdfile;
                userFound = true;

                while (getline(file, line) && !line.empty()) {
                    if (line.find("Vendor Company Name: ") != string::npos)
                        bd.vendorName = line.substr(21);
                    else if (line.find("Contact: ") != string::npos)
                        bd.contact = line.substr(9);
                    else if (line.find("Event Date: ") != string::npos)
                        bd.eventDate = line.substr(12);
                    else if (line.find("Service Type: ") != string::npos)
                        bd.serviceType = line.substr(14);
                    else if (line.find("Booth Location: ") != string::npos)
                        bd.booth = line[16];
                    else if (line.find("Booth Number: ") != string::npos) {
                        string boothNumStr = line.substr(14);
                        bd.boothNumber = boothNumStr;  // directly assign booth number as string
                    } else if (line.find("Total Price: RM") != string::npos) {
                        string priceStr = line.substr(15);
                        if (isFloat(priceStr))
                            bd.totalPrice = stof(priceStr);
                        else
                            cout << "Invalid total price: " << priceStr << endl;
                    }
                }
                bookings.push_back(bd);
            }
        }
        file.close();

        if (!userFound) {
            cout << "No booking details found for the user." << endl;
            cout << "Press Enter to continue...";
            cin.ignore();
            system("cls");
            return;
        }

        // Display bookings in table format before sorting
        cout << "-------------Original Booking Details-----------" << endl;
        cout << left << setw(15) << "Vendor Name" << setw(12) << "Contact" << setw(30) << "Event Date" << setw(20) << "Service Type" << setw(15) << "Booth" << setw(15) << "Booth Number" << setw(15) << "Total Price" << endl;
        cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
        for (const auto& booking : bookings) {
            cout << left << setw(15) << booking.vendorName << setw(12) << booking.contact << setw(30) << booking.eventDate << setw(20) << booking.serviceType << setw(15) << booking.booth << setw(15) << booking.boothNumber << "RM" << booking.totalPrice << endl;
        }
        cout << "---------------------------------------------------------------------------------------------------------------------" << endl;

        // Prompt the user for sorting
        char sortChoice;
        cout << "Do you want to sort the bookings by booth number? (y/n): ";
        cin >> sortChoice;
        cin.ignore(); // Ignore remaining newline character

        if (sortChoice == 'y' || sortChoice == 'Y') {
            // Prompt the user to choose sorting algorithm
            char algorithmChoice;
            cout << "Choose sorting algorithm: " << endl;
            cout << "1. Merge Sort" << endl;
            cout << "2. Insertion Sort" << endl;
            cout << "Enter your choice (1/2): ";
            cin >> algorithmChoice;
            cin.ignore(); // Ignore remaining newline character

            if (algorithmChoice == '1') {
                // Sort bookings by booth number using Merge Sort
                mergeSort(bookings, 0, bookings.size() - 1);
            } else if (algorithmChoice == '2') {
                // Sort bookings by booth number using Insertion Sort
                insertionSort(bookings);
            } else {
                cout << "Invalid choice. Skipping sorting." << endl;
            }

            // Display bookings in table format after sorting
            cout << "-------------Sorted Booking Details-----------" << endl;
            cout << left << setw(15) << "Vendor Name" << setw(12) << "Contact" << setw(30) << "Event Date" << setw(20) << "Service Type" << setw(15) << "Booth" << setw(15) << "Booth Number" << setw(15) << "Total Price" << endl;
            cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
            for (const auto& booking : bookings) {
                cout << left << setw(15) << booking.vendorName << setw(12) << booking.contact << setw(30) << booking.eventDate << setw(20) << booking.serviceType << setw(15) << booking.booth << setw(15) << booking.boothNumber << "RM" << booking.totalPrice << endl;
            }
            cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
        }

        cout << "Press Enter to continue...";
        cin.ignore();
        system("cls");
    } else {
        cout << "Error opening booking details file." << endl;
    }
}

string GetHiddenPassword(){
      string password;
      char ch;

      while(true){
        ch = _getch(); // Get a single character without echoing it to the console

        if(ch == 13) 
            break;
        else if(ch == 8){ // Backspace key
            if (!password.empty()){
                cout<<"\b \b"; // Erase the last character from the console
                password.erase(password.length() - 1); // Remove the last character from the string
            }
        }
        else{
            cout << '*'; // Display '*' 
            password += ch; 
        }
       }

      cout<<endl;
      return password;
    }

int main() {
	ConsoleUtils console;
	USER U;
    adminpanel ap;
    int option;
    string Username,email;
    console.print_title();
	system("Pause");
	system("cls");
	
    do {
        display_menu();
        cout << "\t\tEnter your options :";
        cin >> option;
        while (option < 1 || option > 4) 
		{
			cin.clear(); // clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n\033[1;31mInvalid Input. Please enter a valid option (1-4)\033[0m" << endl;
            cout << "Enter your options :";
            cin >> option;
        }
        if (option == 1) {
             Username = U.Login();
            
            system("cls");
            process_menu(Username);
        } else if (option == 2) {
             U.NewUser(); 
        } else if (option == 3) {
            if (ap.admin()) {
            	system("cls");
                adminpage();
            }
        }else if(option == 4){
        	SetConsoleTextAttribute(h,10);
        	cout << "\nExiting the program. Thanks and Goodbye!" << endl;
        	SetConsoleTextAttribute(h,7);
            break;
		}
    } while (option != 4);
    return 0;
}

