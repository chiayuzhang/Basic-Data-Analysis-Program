#include <iostream>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h> 
#include <string>
#include <iomanip>  
#include <stdlib.h>
#include <set>
#include "clrscrc.h"

using namespace std;

bool login_successful = false;
long long option, remain = 6;
int s;
string current_user, current_user_type, filenaming = "report.txt";
string output(string file);
void main_one();

// Login
bool checkPasswordStrength(string password);
void createAccount(string current_user, string current_user_type);
void deleteUser(string current_user, string current_user_type);
void logout(string &current_user, string &current_user_type);
void changePassword(string current_user, string current_user_type);

// F2 Data file reader (CHIA YU ZHANG)
void logfile(string history, string username);
void loadDataFile(vector<vector<int>> &finalData, string username);
void saveReport(string filenaming, string item, string result, string username);
void saveAs(vector<vector<int>> finalData, string &filenaming, string username);
void saveHTML(int min, int max, double med, double mean, double var, double sd, string username);

// F3 Statistical Computation (ADAM ZIKRY)
int maximum(const vector<vector<int>> vec, int col);
int minimum(const vector<vector<int>> vec, int col);
int median(const vector<vector<int>> vec, int col);
double mean(const vector<vector<int>> vec, int col);
double variance(const vector<vector<int>> vec, int col);
double standarddev(const vector<vector<int>> vec, int col);
void correlation(const vector<vector<int>> vec, int col1, int col2);
void correlation_r(const vector<vector<int>> vec, int col1, int col2);
void distinct_data(const vector<vector<int>> vec);
void distinct_data_r(const vector<vector<int>> vec);
void histogram(const vector<vector<int>> vec);
void histogram_r(const vector<vector<int>> vec);

//Login page
// User Admin -----> Login_succesful
void showProfilePage(string username, string user_type)
{   
    clrscr();
    cout <<"\t\t\t\t\t\tLogged in user: " << username << endl;
 
    char option;
    
    cout <<"\t\t\t\t  _____________________________________________________ " << endl;
    cout <<"\t\t\t\t |                                                     |" << endl;
    if (user_type == "Administrator")
    {
      cout <<"\t\t\t\t |   Press [c] to create a new user account            |" << endl;
      cout <<"\t\t\t\t |   Press [d] to delete an existing account           |" << endl;
    }
    cout <<"\t\t\t\t |   Press [r] to reset your password                  |" << endl; 
    cout <<"\t\t\t\t |   Press [l] to log out                              |" << endl;     
    cout <<"\t\t\t\t |_____________________________________________________|" << endl;
    
    cout << endl << "Enter your option: ";
    cin >> option;
 
    switch (option)
    {
      case 'c':
        if (user_type == "Administrator")
        {
          createAccount(current_user, current_user_type);
        }
        break;
      
      case 'd':
        if (user_type == "Administrator")
        {
          deleteUser(current_user, current_user_type);
        }
        break;
 
      case 'r':
        changePassword(current_user, current_user_type);
        break;
 
      case 'l':
        logout(current_user, current_user_type);
        break;
 
      default: cout << "Please select a valid option" << endl;
          break;
    }
}

void reportMenu(string filename){
    string line, line1;

    ifstream file;
    file.open(filename);

    getline(file,line1); // take the id, age, data...

    if(file.is_open()){
        while(!file.eof()){
            while(getline(file,line,',')){
                cout << line << " ";  // take the result
            }
            cout << endl;
        }

    }
    file.close();
    cout << "Enter 1 to go back\n";
    cin >> s;
    main_one();
}

//Stastical Computation Menu
void main_two()
{   
    clrscr();
    cout <<"\t\t\t\t  ___________________________________________________________" << endl;
    cout <<"\t\t\t\t |                                                           |" << endl;  //Stastical Computation Menu
    cout <<"\t\t\t\t |-----------------------------------------------------------|" << endl;
    cout <<"\t\t\t\t |   Please Choose any option below                          |" << endl;
    cout <<"\t\t\t\t |                                                           |" << endl;
    cout <<"\t\t\t\t |   Press [1] Find Maximum                                  |" << endl; // Function for finding the maximum of the column
    cout <<"\t\t\t\t |   Press [2] Find Minimum                                  |" << endl; // Function for finding the minimum of the column
    cout <<"\t\t\t\t |   Press [3] Median                                        |" << endl; // Function for finding the median of the column
    cout <<"\t\t\t\t |   Press [4] Mean                                          |" << endl; // Function for finding the mean of the column
    cout <<"\t\t\t\t |   Press [5] Variance                                      |" << endl; // Function for finding the variance of the column
    cout <<"\t\t\t\t |   Press [6] Standard Deviation                            |" << endl; // Function for finding the standard deviation of the column
    cout <<"\t\t\t\t |   Press [7] Correlation between any selected 2 columns    |" << endl; // Function for finding the correlation between two columns
    cout <<"\t\t\t\t |   Press [8] Distinct data members                         |" << endl; // Function for printing out the distinct data table
    cout <<"\t\t\t\t |   Press [9] Print A Histogram                             |" << endl; // Funtion to print the histogram
    cout <<"\t\t\t\t |   Press [10] Exit                                         |" << endl; // Exit the program
    cout <<"\t\t\t\t |___________________________________________________________|" << endl;

    int col, col2, max, min, med,s;
    double m, varianc, sd;
    string history;
    char sel;
    vector<vector<int>> finalData;
    loadDataFile(finalData, current_user);
    cout << " Do you want to rename the file (y/n) : ";
    cin >> sel;
    if (sel == 'y') saveAs(finalData, filenaming, current_user);
    cout << "Your Option: ";
    cin >> option;

    switch (option) {
        case 1:
        cout << "Choose a column (1. Age, 2. Math, 3. Science, 4. Malay): ";
        cin  >> col;
        if (!(col >= 1 && col <= 4))
        {
          do{
            cout << "Please choose a column within the range 1 to 4\n";
            cin >> col;
          }
          while(!(col >= 1 && col <= 4));
        }
        max = maximum(finalData,col-1);
        cout << "Maximum for column " << col << " : " << max << endl;      // Get the maximum
        history =  " has computed maximum  ";
        saveReport(filenaming,"Maximum", to_string(max), current_user);
        logfile(history,current_user);
        break;

        case 2:
        cout << "Choose a column (1. Age, 2. Math, 3. Science, 4. Malay): ";
        cin  >> col;
        if (!(col >= 1 && col <= 4))
        {
          do{
            cout << "Please choose a column within the range 1 to 4\n";
            cin >> col;
          }
          while(!(col >= 1 && col <= 4));
        }
        min =minimum(finalData,col-1);       // Get the minimum
        cout << "Minimum for column " << col << " : " << min << endl;
        history = " has computed minimum  ";
        saveReport(filenaming,"Minimum",to_string(min), current_user);
        logfile(history,current_user);
        break;

        case 3:
        cout << "Choose a column (1. Age, 2. Math, 3. Science, 4. Malay): ";
        cin  >> col;
        if (!(col >= 1 && col <= 4))
        {
          do{
            cout << "Please choose a column within the range 1 to 4\n";
            cin >> col;
          }
          while(!(col >= 1 && col <= 4));
        }
        med =median(finalData,col-1);        // Get the median
        cout << "Median for column " << col << " : " << med << endl;
        history = " has computed median  ";
        saveReport(filenaming,"Median",to_string(med), current_user);
        logfile(history,current_user);
        break;

        case 4:
        cout << "Choose a column (1. Age, 2. Math, 3. Science, 4. Malay): ";
        cin  >> col;
        if (!(col >= 1 && col <= 4))
        {
          do{
            cout << "Please choose a column within the range 1 to 4\n";
            cin >> col;
          }
          while(!(col >= 1 && col <= 4));
        }
        m =mean(finalData,col-1);             // Get the mean
        cout << "Mean for column " << col << " : " << m << endl;
        history = " has computed mean ";
        saveReport(filenaming,"Mean",to_string(m), current_user);
        logfile(history,current_user);
        break;

        case 5:
        cout << "Choose a column (1. Age, 2. Math, 3. Science, 4. Malay): ";
        cin  >> col;
        if (!(col >= 1 && col <= 4))
        {
          do{
            cout << "Please choose a column within the range 1 to 4\n";
            cin >> col;
          }
          while(!(col >= 1 && col <= 4));
        }
        varianc=variance(finalData,col-1); 
        cout << "Variance for column " << col << " : " << varianc << endl;     // Get the variance
        history = " has computed variance ";
        saveReport(filenaming,"Variance",to_string(varianc), current_user);
        logfile(history,current_user);
        break;

        case 6:
        cout << "Choose a column (1. Age, 2. Math, 3. Science, 4. Malay): ";
        cin >> col;
        if (!(col >= 1 && col <= 4))
        {
          do{
            cout << "Please choose a column within the range 1 to 4\n";
            cin >> col;
          }
          while(!(col >= 1 && col <= 4));
        }
        sd =standarddev(finalData,col-1);       // Get the standard deviation
        cout << "Standard Deviation for column " << col << " : " << sd << endl;
        history = " has computed standard deviation ";
        saveReport(filenaming,"Standard deviation",to_string(sd), current_user);
        logfile(history,current_user);
        break;

        case 7:
        cout << "Choose a column (1. Age, 2. Math, 3. Science, 4. Malay): ";
        cin >> col;
        if (!(col >= 1 && col <= 4))
        {
          do{
            cout << "Please choose a column within the range 1 to 4\n";
            cin >> col;
          }
          while(!(col >= 1 && col <= 4));
        }
        cout << "Choose a different second column (1. Age, 2. Math, 3. Science, 4. Malay): ";
        cin >> col2;
        if (!(col >= 1 && col <= 4 && col != col2))
        {
          do{
            cout << "Please choose a column within the range 1 to 4 or choose a different column\n";
            cin >> col;
          }
          while(!(col >= 1 && col <= 4));
        }
        correlation(finalData,col-1,col2-1);      // Get the correlation
        correlation_r(finalData,col-1,col2-1);
        history = " has computed correlation ";
        saveReport(filenaming,"Correlation",output("correlation.txt"), current_user);
        logfile(history,current_user);
        break;

        case 8:
        distinct_data(finalData);             // Get the distinct data
        distinct_data_r(finalData);            
        history = " has computed distinct data ";
        saveReport(filenaming,"Distinct data",output("distinct.txt"), current_user);
        logfile(history,current_user);
        break;

        case 9:
        histogram(finalData);                   // Print the histogram
        histogram_r(finalData);             
        history = " has computed histogram ";
        saveReport(filenaming,"Histogram",output("histogram.txt"), current_user);
        logfile(history,current_user);
        break;

        case 10:
        main_one();
        break;

        default:
        cout << "Invalid Input,Please try again." << endl;  
        system("PAUSE");                                               // pause the run program
        clrscr();                                                      // clear screen
        main_two(); 
    }

    saveHTML(min, max, med, m, varianc, sd, current_user);
    cout << "\nPress enter 1 to continue\n";
    cin >> s;
    cin.ignore(10, '\n'); 
    main_two();                                                    
 } 

void main_one()
{   
    clrscr();
    cout <<setw (60)<< "Welcome : "<< current_user << endl;                               //set the line to 60 width 
    cout <<"\t\t\t\t  _____________________________________________________" << endl;
    cout <<"\t\t\t\t |                                                     |" << endl;
    cout <<"\t\t\t\t |                    WELCOME                          |" << endl;
    cout <<"\t\t\t\t |                      To                             |" << endl;
    cout <<"\t\t\t\t |            Basic Data Analysis Program              |" << endl;
    cout <<"\t\t\t\t |-----------------------------------------------------|" << endl;
    cout <<"\t\t\t\t |-----------------------------------------------------|" << endl;
    cout <<"\t\t\t\t |   Please Choose any option below                    |" << endl;
    cout <<"\t\t\t\t |                                                     |" << endl;
    cout <<"\t\t\t\t |   Press [1] Statistical Computation Menu            |" << endl;
    cout <<"\t\t\t\t |   Press [2] Report Menu                             |" << endl;   // Print report in HTML Format
    cout <<"\t\t\t\t |   Press [3] Restart Password                        |" << endl;   // Reset Password
    cout <<"\t\t\t\t |   Press [4] Log out                                 |" << endl;   //return to Login page
    cout <<"\t\t\t\t |                                                     |" << endl;
    cout <<"\t\t\t\t |_____________________________________________________|" << endl;


    cout << "Your Option: ";
    cin >> option;

    switch(option){
        case 1:
        main_two();
        break;

        case 2:
        reportMenu(filenaming);
        break;

        case 3:
        changePassword(current_user, current_user_type);
        break;

        case 4:
        logout(current_user, current_user_type);
        break;
                                 
        default:
        cout << "Invalid Input,Please try again." << endl;               
        system("PAUSE");                                  //pause the run program
        clrscr();                                         //clear the screen
        main_one();
    }
}

void showLoginPage(string &current_user, string &current_user_type)
{
    bool login_successful = false;
    string input_username, input_password, username, password, user_type, status;
    clrscr();
    cout <<"\t\t\t\t  _____________________________________________________" << endl;
    cout <<"\t\t\t\t |                                                     |" << endl;
    cout <<"\t\t\t\t |                        WELCOME                      |" << endl;
    cout <<"\t\t\t\t |_____________________________________________________|" << endl;
    cout <<"\t\t\t\t |                                                     |" << endl;
    cout <<"\t\t\t\t |     Enter your username and password to login       |" << endl;   
    cout <<"\t\t\t\t |_____________________________________________________|" << endl;
 
    while (!login_successful){
      cout << endl << "Please put your Username: ";
      cin >> input_username;
      cout << endl << "Please put your Password: ";
      cin >> input_password;
 
      ifstream user_info("users/user_" + input_username + ".txt");
      getline(user_info, username);
      getline(user_info, password);
      getline(user_info, user_type);
      getline(user_info, status);
      user_info.close();
 
    if (input_username == username && input_password == password)
      { 
        if (status == "deleted")
        {
          cout << endl << "Your account has been deleted by an administrator." << endl;
          cout << endl << "Please try again." << endl;
          login_successful = false;
        } 
        else{
            if(user_type == "Buyer" )
            {
             cout<< endl << "You have logged in successfully!" << endl;
             cout << "_____________________________________________________" << endl << endl;
             current_user = username;
             current_user_type = user_type;
             cout << "Enter 1 to continue\n";
             cin >> s;              
             main_one();
            }
            else
            {
            cout << endl << "You have logged in successfully!" << endl;
            cout << "_____________________________________________________" << endl << endl;
            login_successful = true;
            current_user = username;
            current_user_type = user_type;
            cout << "Enter 1 to continue\n";
            cin >> s;              
            showProfilePage(current_user, current_user_type);
            }
        }
      }
        else
        {
        cout << endl << "Invaild username or password. Please try again." << endl;
        login_successful = false;
        }
    }
}

int main()
{
    showLoginPage(current_user, current_user_type);
    
    return 0;
}



