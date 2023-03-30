#include<fstream>
#include<iostream>
#include<string>
 
using namespace std;
 
void showProfilePage(string username, string user_type);      
void showLoginPage(string &current_user, string &current_user_type);
// bool checkPasswordStrength(string password);
// void createAccount();
// void deleteUser();
// void showLoginPage();
// void logout();
// void changePassword();

bool checkPasswordStrength(string password) 	// This function will check password strength
                                      
{
    bool charFound = false;
    bool numFound = false;
 
    if(isalpha(password.at(0)) == false)
    {
        cout << endl << "The password must start with a character" << endl;
        return false;
    }
 
    for (int i = 0; i < password.length(); i++) 
    {
        if(isupper(password.at(i)))
        {
            charFound = true;
            break;
        }
    }
 
    for (int i = 0; i < password.length(); i++) 
    {
        if(isdigit(password.at(i)))
        {
            numFound = true;
            break;
        }
    }
 
    if(!charFound) 
    {
        cout << endl << "The password must contain a upper case charater" << endl;
    }
 
    if(!numFound) 
    {
        cout << endl << "The password must contain a number" << endl;
    }
 
 
    return charFound && numFound;
}

void logout(string &current_user, string &current_user_type)			// This function is to log out the user from the system
{
  current_user = "";
  current_user_type = "";
 
  cout  << endl << "Successfully logged out." << endl;
  cout << "_____________________________________________________" << endl << endl;
 
  showLoginPage(current_user, current_user_type);
}

void changePassword(string current_user, string current_user_type)  //  This function is to change the user password 																
                                                                    //  and replace the new password with the old one
{
    string new_password;
    bool isPasswordValid = false;
 
    cout << "_____________________________________________________" << endl << endl;
 
    while(!isPasswordValid)
    {
        cout << endl;
        cout << "Enter a new password: ";
        cin >> new_password;
        isPasswordValid = checkPasswordStrength(new_password);
    }
    
    ofstream user_info;
    user_info.open("users/user_" + current_user + ".txt");
    user_info << current_user << endl << new_password << endl << current_user_type << endl << "active";
    user_info.close();
 
    cout << endl << endl << "Your password has been changed successfully!" << endl;
    cout  << "Please login again." << endl;
    cout << "_____________________________________________________" << endl << endl;
 
    logout(current_user, current_user_type);
}

void createAccount(string current_user, string current_user_type) 	// This function is to create new users 																															
                                                                    // and save it into a txt file under
                                                                    // the folder called "users"
{
    string username, password, user_type, status;
    bool isPasswordValid = false;

    cout << "\t\t\t\t\t\tNow create your account :" << endl;
    cout << "\t\t\t\t_____________________________________________________";
    cout << endl;
    cout << "Please choose an Username: ";
    cin >> username;

    while(!isPasswordValid)
    {
        cout << endl;
        cout << "Please choose a Password: ";
        cin >> password;
        isPasswordValid = checkPasswordStrength(password);
    }

    cout << endl;
    cout << "Select user type: [Administrator/Buyer] ";
    cin >> user_type;
    cout << endl;

    ofstream user_info;
    user_info.open("users/user_" + username + ".txt");
    user_info << username << endl << password << endl << user_type << endl << "active";
    user_info.close();

    cout << "The new account has been created successfully." << endl << endl;
    cout << "_____________________________________________________" << endl << endl;

    showProfilePage(current_user, current_user_type);
}



void deleteUser(string current_user, string current_user_type)  // This function delete the existing account
																// By deleting the account, account's status
                                                                // will change to "deleted"
{
    string input_username, username, password, user_type, status;
    cout << "\t\t\t\t\t\tYour account will be deleted and can't use anymore :" << endl;
    cout << "\t\t\t\t__________________________________________________________________________________" << endl;
    cout << endl;
 
    cout << "Enter the username that you want to delete: ";
    cin >> input_username;
    cout << endl;
 
    ifstream user_info("users/user_" + input_username + ".txt");
    getline(user_info, username);
    getline(user_info, password);
    getline(user_info, user_type);
    getline(user_info, status);
    user_info.close();
 
    cout << endl << endl << "Press y to confirm" << endl << endl;
    char option;
    cin >> option;
 
    if (option == 'y'){
      ofstream write_user_info;
      write_user_info.open("users/user_" + username + ".txt");
      write_user_info << username << endl << password << endl << user_type << endl << "deleted";
      write_user_info.close();
 
      cout << "The account has been deleted successfully." << endl << endl;
      cout << "_____________________________________________________" << endl << endl;
 
      showProfilePage(current_user, current_user_type);
    }
}

