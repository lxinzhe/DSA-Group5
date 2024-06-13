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

using namespace std;
struct Booking {
    string userID;
    string details;
};

struct UserData {
        string username;
        string password;
        string email;
        UserData* next;

        UserData(const string& uname, const string& pwd, const string& mail)
            : username(uname), password(pwd), email(mail), next(nullptr) {}
};
    
struct FeedbackNode {
    string username;
    string feedback;
    int rating;
    FeedbackNode* next;

    FeedbackNode(const string& user, const string& fb, int rate)
        : username(user), feedback(fb), rating(rate), next(nullptr) {}
};

HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);

void display_menu();
string Login();
void process_menu(const string& Username); 
void adminpage();
void detaildisplay(const string& userIdfile);
string GetHiddenPassword();
void viewFeedback();
    void exitAdminPage();


class USER{
private:


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
        cout << "USER instance destroyed." << endl;
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
    }
    else {
        UserData* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newUser;
    }
    // Save user details to a file
    ofstream file("user_data.txt", ios::app);
    if (file.is_open()) {
        file << username << setw(17) << password << setw(20) << email << endl << endl;
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

    
void cancelBooking() {
    system("cls");

    ifstream file("booking_details.txt");
    ofstream tempFile("temp_booking_details.txt");  

    if (file.is_open() && tempFile.is_open()) {
        string line, userID, bookingLine;
        bool bookingFound = false;

        cout << "Enter the booking username: ";
        cin >> userID;

        while (getline(file, line)) {
            if (line.find("User: " + userID) != string::npos) {
                bookingFound = true;
                bookingLine = ""; // Initialize a new bookingLine
                cout << "-------------Booking Details-----------" << endl;
            }

            if (bookingFound) {
                cout << line << endl;
                bookingLine += line + "\n";

                if (line.find("Total Price:") != string::npos) {
                    char confirm;
                    cout << "Do you want to cancel this booking? (y/n): ";
                    cin >> confirm;

                    if (confirm == 'y' || confirm == 'Y') {
                        string cancelReason;
                        cin.ignore();  
                        cout << "Enter the reason for cancellation: ";
                        getline(cin, cancelReason);

                        ofstream cancelFile("cancellation_log.txt", ios::app);
                        if (cancelFile.is_open()) {
                            cancelFile << "User: " << userID << "\n"<<"------------------"<<endl
                                       << "Booking Details:\n"
                                       << bookingLine <<"--------------------"<<endl 
                                       << "Cancellation Reason: " << cancelReason << "\n\n";
                            cancelFile.close();
                            cout << "Booking canceled successfully." << endl;
                        } else {
                            cout << "Error logging cancellation reason." << endl;
                        }
                    } else {
                        cout << "Booking not canceled." << endl;
                        tempFile << bookingLine << "\n"; // Add the booking back to the temp file
                    }

                    bookingFound = false; // Reset bookingFound
                }
            } else {
                tempFile << line << "\n"; // Add non-booking lines to the temp file
            }
        }

        file.close();
        tempFile.close();

        if (remove("booking_details.txt") != 0) {
            cout << "Error deleting booking_details.txt" << endl;
        }
        
        if (rename("temp_booking_details.txt", "booking_details.txt") != 0) {
            cout << "Error renaming temp_booking_details.txt" << endl;
        }
    } else {
        cout << "Error opening booking details file." << endl;
    }
}
};


class adminpanel : public USER
{
	private:
    string enteredAdmin,adminname,enteredPassword,adminpassword;
		
	public:
		~adminpanel() {
        cout << "Admin panel instance destroyed." << endl;
    }
		struct User {
        string username, password,email;
        };
        
		adminpanel() 
		{
        loadAdmindetails();// Constructor to initialize adminName and adminPassword from a file
        }
        
		void loadAdmindetails() 
		{
         ifstream file("admin_login.txt"); 
         if (file.is_open()) 
		 {
            file >> adminname >> adminpassword;
            file.close();
         } else 
		 {
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

    ifstream file("admin_login.txt");

    if (file.is_open()) {
        string adminnameFromFile, adminpasswordFromFile;

        while (file >> adminnameFromFile >> adminpasswordFromFile) {
            if (enteredAdmin == adminnameFromFile && enteredPassword == adminpasswordFromFile) {
                loginSuccessful = true;
                break;
            }
        }

        file.close();
    } else {
        cout << "Error opening admin file." << endl;
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
    }else {
        cout << "\n\033[1;31mInvalid Name or Password, Please Try Again\033[0m" << endl;
        system("Pause");
        system("cls");
        return false;
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


    void addinAdmin() {
        int updatechoice;
        cout << "\t\t\t\t\t-------------------------------------" << endl;
        cout << "\t\t\t\t\tEnter 1 for Add New Admin" << endl;
        cout << "\t\t\t\t\tEnter 2 for Update Admin Information" << endl;
        cout << "\t\t\t\t\tEnter 3 for Delete Admin" << endl;
        cout << "\t\t\t\t\tEnter 4 for View deleted Admin" << endl;
        cout << "\t\t\t\t\tEnter 5 for Go Back to Admin Panel" << endl;
        cout << "\t\t\t\t\tYour Choice:";
        cin >> updatechoice;
        if (updatechoice == 1) 
		{
        string newAdminname, newAdminpassword;
        cout << "Enter new admin username: ";
        cin >> newAdminname;
        cout << "Enter new admin password: ";
        cin >> newAdminpassword;

        ofstream file("admin_login.txt",ios::app);

        if (file.is_open()) {
            file << newAdminname << " " << newAdminpassword << endl;
            file.close();
            cout << "New admin added successfully!" << endl;
        } else {
            cout << "Error opening admin file." << endl;
        }
        }else if(updatechoice == 2){
        	 string adminName, newPassword;
            cout << "Enter admin name to update: ";
            cin >> adminName;
            cout << "Enter new password: ";
            cin >> newPassword;
            UpdateAdmin(adminName, newPassword);
	    }else if (updatechoice == 3) {
	    	string adminToDelete;
            cout << "Enter the name of the admin to delete: ";
            cin >> adminToDelete;
            deleteAdmin(adminToDelete, "Admin"); 
            system("Pause");
            system("cls");
            adminpage();
        }else if(updatechoice == 4){
        	viewDeletionLog();
        	system("Pause");
        	system("cls");
            adminpage();
		}else if(updatechoice == 5){
			system("cls");
            adminpage();
		}else {
            cout << "Invalid choice. Please enter a valid option (1-3)" << endl;
            system("Pause");
            system("cls");
            adminpage();
        }
}
    
  void UpdateAdmin(const string& adminName, const string& newPassword) {
    ifstream inFile("admin_login.txt");
    ofstream outFile("temp_admin_login.txt");
    if (!inFile.is_open() || !outFile.is_open()) {
        cout << "Error opening files." << endl;
        return;
    }

    bool adminFound = false;
    string line;
    while (getline(inFile, line)) {
        istringstream iss(line);
        string adminnameFromFile, adminpasswordFromFile;
        if (iss >> adminnameFromFile >> adminpasswordFromFile) {
            if (adminnameFromFile == adminName) {
                adminFound = true;
                outFile << adminName << " " << newPassword << endl;
                cout << "\033[1;32mAdmin password updated successfully!\033[0m" << endl;
            } else {
                outFile << adminnameFromFile << " " << adminpasswordFromFile << endl;
            }
        }
    }

    inFile.close();
    outFile.close();

    if (!adminFound) {
        cout << "No admin found with the specified name." << endl;
    }

    remove("admin_login.txt");
    rename("temp_admin_login.txt", "admin_login.txt");
 }

 void deleteAdmin(const string& adminName,const string& enteredAdmin) {
    ifstream inFile("admin_login.txt");
    ofstream outFile("temp_admin_login.txt");

    if (!inFile.is_open() || !outFile.is_open()) {
        cout << "Error opening files." << endl;
        return;
    }

    bool adminFound = false;
    string line;

    while (getline(inFile, line)) {
        istringstream iss(line);
        string adminnameFromFile, adminpasswordFromFile;
        if (iss >> adminnameFromFile >> adminpasswordFromFile) {
            if (adminnameFromFile == adminName) {
                adminFound = true;
                fflush(stdin);
                cout << "Are you sure you want to delete admin " << adminName << "? (yes/no): ";
                string confirmation;
                string deletionTime = getCurrentTime();
                getline(cin, confirmation);
                if (confirmation == "yes") {
                    cout << "\033[1;32mAdmin " << adminName << " has been deleted at "<<deletionTime<<".\033[0m" << endl;
                    continue; 
                } else {
                    cout << "Admin deletion cancelled." << endl;
                    outFile << line << endl;
                }
            } else {
                outFile << line << endl;
            }
        }
    }

    inFile.close();
    outFile.close();

    if (adminFound) {
        ofstream logFile("admin_deletion_log.txt", ios::app);
        if (logFile.is_open()) {
        	string deletionTime = getCurrentTime();
            logFile << "Admin '" << adminName << "' was deleted at "<< deletionTime<< endl;
            logFile.close();
        }
    }

    if (!adminFound) {
        cout << "No admin found with the specified name." << endl;
    }

    remove("admin_login.txt");
    rename("temp_admin_login.txt", "admin_login.txt");
}

void viewDeletionLog() 
{
    ifstream logFile("admin_deletion_log.txt");
    if (logFile.is_open()) {
        string line;
        while (getline(logFile, line)) {
            cout << line << endl;
        }
        logFile.close();
    } else {
        cout << "Unable to open log file." << endl;
    }
}
    
  void searchbooking(const string& idsearch) {
    ifstream file("booking_details.txt");
    bool found = false;
    string line;
    int bookingCount = 0; // Keep track of the number of bookings found

    while (getline(file, line)) {
        // Check if the line contains "User: " followed by the user ID
        if (line.find("User: " + idsearch) != string::npos) {
            found = true;
            bookingCount++;
            cout << "\nBooking " << bookingCount << " for user " << idsearch << ":" << endl;
            cout << "-----------------------------------" << endl;
            cout << line << endl; // Display the line containing "User: " + idsearch
            // Display additional lines for booking details
            while (getline(file, line) && line != "") {
                cout << line << endl;
            }
        }
    }

    if (!found) {
        cout << "No bookings found for user " << idsearch << "." << endl;
    }
 }

  void optionbooking() {
    int viewchoice;
    cout << "\t\t\t\t\t-------------------------------------" << endl;
    cout << "\t\t\t\t\tEnter 1 for View All Booking" << endl;
    cout << "\t\t\t\t\tEnter 2 for Search Booking" << endl;
    cout << "\t\t\t\t\tEnter 3 for Cancel Booking" << endl;
    cout << "\t\t\t\t\tEnter 4 for View User Cancel Reason" << endl;
    cout << "\t\t\t\t\tEnter 5 for Go Back to Admin Panel" << endl;
    cout << "\t\t\t\t\tYour Choice:";
    cin >> viewchoice;

    if (viewchoice == 1) {
        viewBooking();
        system("Pause");
        system("cls");
        adminpage();
    } else if(viewchoice == 2){
    	string idsearch;
        cout << "Enter the user ID to search for booking: ";
        cin >> idsearch; 
        searchbooking(idsearch);
        system("Pause");
        system("cls");
        adminpage();
	}else if (viewchoice == 3) {
        string usernameToDelete;
        cout << "Enter the username to cancel bookings: ";
        cin >> usernameToDelete;
        cancelBookingByUserID(usernameToDelete);
        system("Pause");
        system("cls");
        adminpage();
    }else if(viewchoice == 4){
    	cancelreason();
    	system("Pause");
    	system("cls");
    	adminpage();
    	
	}else if (viewchoice == 5) {
        system("cls");
        adminpage();
    }else {
        cout << "Invalid choice. Please enter a valid option (1-3)" << endl;
        system("Pause");
        system("cls");
        adminpage();
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

string getCurrentTime() 
{ //get time
    time_t currentTime;
    struct tm* timeInfo;
    char buffer[80];

    time(&currentTime);
    timeInfo = localtime(&currentTime);

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
    return buffer;
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



  void viewuser() {
    char choiceuser;

    while (true) {
        cout << "\t\t\t\t\t-------------------------------------" << endl;
        cout << "\t\t\t\t\tEnter 1 for View Vendor Details" << endl;
        cout << "\t\t\t\t\tEnter 2 for Delete Vendor" << endl;
        cout << "\t\t\t\t\tEnter 3 for View Deleted Vendor" << endl;
        cout << "\t\t\t\t\tEnter 4 for Go Back to Admin Panel" << endl;
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
            		string usernameToDelete;
                    cout << "Enter the username to delete: ";
                    cin >> usernameToDelete;
                    deleteUser(usernameToDelete);
				}
                break;
            case '3':
            	viewUserDeletionLog();
                system("Pause");
                system("cls");
                adminpage();
			case '4' :
				system("Pause");
                system("cls");
                adminpage();
                return; 
            default:
                cout << "Invalid choice. Please enter a valid option (1-3)" << endl;
        }
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
    
    void profit();
    
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
   
   
   friend class booking;
};

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

    void setName() {
        string nameInput;
        cout << "\tPlease Enter your detail for booking" << endl;
        cout << "----------------------------------------------------" << endl;
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

    void setContact() {
        string contactInput;
        cout << "Contact No: ";
        getline(cin, contactInput);
        tail->contact = contactInput;
    }

    int setDuration() {
        int durationInput;
        cout << "Duration (Days): ";
        cin >> durationInput;
        cin.ignore(); // Consume newline character
        tail->duration = durationInput;
        return durationInput;
    }

    void setUserID(const string& userIdfile) {
        tail->userID = userIdfile;
    }
void setEventGroup() {
    if (tail == nullptr) {
        cout << "Error: No booking to set event group for." << endl;
        return;
    }
    char eventInput;
    cout << "Event [A]Food Feasta Carnival Kuala Lumpur" <<
        endl << "From 3 March 2024 - 13 March 2024" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Event [B]Food Feasta Carnival Johor" <<
        endl << "From 17 March 2024 - 27 March 2024" << endl;
    cout << "----------------------------------------------" << endl;
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

    string getEventDate() const {
        if (tail->eventgrp == 'A' || tail->eventgrp == 'a') {
            return "3 March 2024 - 13 March 2024";
        } else {
            return "17 March 2024 - 27 March 2024";
        }
    }

    string service_cat() {
        char codeInput;
                cout << "---------------------------------" << endl;
        cout << "[A]Food & Beverages" << endl;
        cout << "[B]Art & Craft" << endl;
        cout << "[C]Accessories" << endl;
        cout << "[D]Stationeries" << endl;
        cout << "[E]Home & Living" << endl;
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

        return tail->service_type;
    }

    char booth_location() {
        char boothInput;
                cout << "------------------------------------" << endl;
        cout << "[A]Lot A, Price = RM900" << endl;
        cout << "[B]Lot B, Price = RM650" << endl;
        cout << "[C]Lot C, Price = RM550" << endl;
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

        return boothInput;
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

    // Additional functionalities can be added as needed
        string getEmailFromUsername(const string& username) 
	{
    ifstream file("user_data.txt");

    if (file.is_open()) 
	{
        string usernameFromFile, passwordFromFile, emailFromFile;

        while (file >> usernameFromFile >> passwordFromFile >> emailFromFile) 
		{
            if (username == usernameFromFile) 
			{
                file.close();
                return emailFromFile;
            }
        }

        file.close();
    } else {
        cout << "Error opening file to get email from username." << endl;
    }

    
    return "";
}
bool caseInsensitiveMatch(string str1, string str2) {
    // Convert both strings to lower case before comparison
    transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
    transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
    return (str1 == str2);
}

void editBooking() {
    string searchID;
    cout << "Enter the User ID of the booking you want to update (or type 'exit' to cancel): ";
    getline(cin, searchID);

    if (caseInsensitiveMatch(searchID, "exit")) {
        cout << "Update canceled." << endl;
        return; // Exit the function
    }

    ifstream inputFile("booking_details.txt");
    ofstream tempFile("temp_booking_details.txt");

    bool found = false;
    Node* current = nullptr;

    if (inputFile.is_open() && tempFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            if (line.find("User: ") != string::npos && caseInsensitiveMatch(line.substr(6), searchID)) {
                found = true;
                cout << "Booking found. You can now update it." << endl;

                // Read the entire booking block
                vector<string> bookingBlock;
                bookingBlock.push_back(line); // User ID line

                while (getline(inputFile, line) && !line.empty()) {
                    bookingBlock.push_back(line);
                }

                // Create a new Node for editing
                current = new Node();
                if (head == nullptr) {
                    head = current;
                    tail = current;
                } else {
                    tail->next = current;
                    tail = current;
                }

                // Parse the booking block into the current Node
                for (const auto& bookingLine : bookingBlock) {
                    if (bookingLine.find("Vendor Company Name: ") != string::npos) {
                        current->name = bookingLine.substr(21);
                    } else if (bookingLine.find("Contact: ") != string::npos) {
                        current->contact = bookingLine.substr(9);
                    } else if (bookingLine.find("Event Date: ") != string::npos) {
                        // Event date is derived from event group
                    } else if (bookingLine.find("Service Type: ") != string::npos) {
                        current->service_type = bookingLine.substr(14);
                    } else if (bookingLine.find("Booth Location: ") != string::npos) {
                        current->booth = bookingLine[16];
                    } else if (bookingLine.find("Booth Number: ") != string::npos) {
                        // Booth number handling can be done here
                    } else if (bookingLine.find("Total Price: RM") != string::npos) {
                        current->total = stof(bookingLine.substr(15));
                    }
                }

                // Prompt and update other booking information
                cout << "Vendor Company Name: ";
                string nameInput;
                getline(cin, nameInput);
                current->name = nameInput;
                
                cout << "Contact No: ";
                string contactInput;
                getline(cin, contactInput);
                current->contact = contactInput;

                // Ensure event group is set correctly
                setEventGroup();
                cin.ignore(); // Consume newline character

                string serviceTypeInput = service_cat(); // Assuming this function sets the service type in tail

                char boothInput = booth_location(); // Assuming this function sets the booth location in tail

                // Write the updated booking to the temp file
                tempFile << "User: " << searchID << endl;
                tempFile << "Vendor Company Name: " << current->name << endl;
                tempFile << "Contact: " << current->contact << endl;
                tempFile << "Event Date: " << getEventDate() << endl;
                tempFile << "Service Type: " << current->service_type << endl;
                tempFile << "Booth Location: " << current->booth << endl;
                tempFile << "Booth Number: " << current->booth << getBoothNumber(current->booth) << endl;
                tempFile << "Total Price: RM" << calculateBoothPrice(current->booth) << endl;
                tempFile << endl << endl;

                cout << "Booking updated successfully!" << endl;
                cout << "Do you want to continue updating? (yes/no): ";
                string continueUpdating;
                getline(cin, continueUpdating);
                if (!caseInsensitiveMatch(continueUpdating, "yes")) {
                    break; // Exit the loop and function
                }
            } else {
                tempFile << line << endl;
            }
        }

        inputFile.close();
        tempFile.close();

        if (!found) {
            cout << "Booking with User ID " << searchID << " not found." << endl;
        } else {
            // Replace the original file with the updated temporary file
            remove("booking_details.txt");
            rename("temp_booking_details.txt", "booking_details.txt");
        }
    } else {
        cout << "Error opening files for booking update." << endl;
    }
}
    friend class adminpanel;
    friend class USER; 

};



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

string Login() {
    string enteredUsername, enteredPassword;
    bool loginSuccessful = false;

    do {
    	system("cls");
    	cout << "===================================" << endl;
    	cout <<"              LOGIN                 "<<endl;
    	cout << "===================================" << endl;
        cout << "Enter your username: ";
        cin >> enteredUsername;

        cout << "Enter your password: ";
        enteredPassword = GetHiddenPassword();

        ifstream file("user_data.txt");

        if (file.is_open()) {
            string usernameFromFile, passwordFromFile, emailFromFile;

            while (file >> usernameFromFile >> passwordFromFile >> emailFromFile) {
                if (enteredUsername == usernameFromFile && enteredPassword == passwordFromFile) {
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
            cout << "\033[1;31mInvalid username or password. Please try again.\033[0m" ;
            cin.get();
            cin.ignore();
        }
    } while (!loginSuccessful);
    

    return enteredUsername;
}//for user login

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
           B.editBooking(); 
        } else if (choice == 4) 
		{
            U.cancelBooking();
        	cout << "Press Enter to go back to the main menu...";
    		cin.get();
    		system("cls");
    		process_menu(Username);
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


void detaildisplay(const string& userIdfile) 
{
    system("cls");
    ifstream file("booking_details.txt");

    if (file.is_open()) 
    {
        string line;
        bool displayBooking = false;
        bool userFound = false; // Flag to track if user details are found

        while (getline(file, line)) 
        {
            if (line.find("User: " + userIdfile) != string::npos) 
            {
                displayBooking = true; 
                userFound = true; // Set the flag to true when user details are found
                cout << "-------------Booking Details-----------" << endl;
            }

            if (displayBooking) 
            {
                cout << line << endl;

                if (line.find("Total Price:") != string::npos) 
                {
                    displayBooking = false; 
                    cout << "---------------------------------------" << endl;
                    cout << "Press Enter to continue...";
                    cin.ignore();
                    system("cls");
                }
            }
        }

        file.close();

        if (!userFound) 
        {
            cout << "No booking details found for the user." << endl;
            cout << "Press Enter to continue...";
            cin.ignore();
            system("cls");
        }
    } 
    else 
    {
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
            Username = Login();
            
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
