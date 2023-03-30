#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h> 
#include <cstring>
#include <cstdio>
using namespace std;

void logfile(string history, string username)
{
    fstream log; // A class to operate the file and given a name data (allow reading and writting).
    log.open("log.txt", ios_base::app); // ios_base::app used to append the data into file

    if(log.is_open()){  //Check whether the file exist.
        log << username << history << endl; // The value need to be stored inside the file.
    }
    else{
        cout << "File does not exist" << endl; // The file not exist will display it.
    }
    
}

void loadDataFile(vector<vector<int>> &finalData, string username)
{   
    string line, title;
    int col,col2, row;
    ifstream data;          // A class to operate the file and given a name data (only for reading).
    data.open("data.txt");

    data >> col;            // Store the data from file("data.txt") inside col, row and tittle 
    data >> title;
    data >> row;

    if(data.is_open()){     //Check whether the file exist.
        while(!data.eof())  // Automatically run the file line by line until empty space
        {   
            vector<int> rows;
            for (int i=0; i<col; i++)          // Run column by cloumn in one line
            {
                getline(data, line, ',');      // Store data to line and remove the ","
                stringstream finalLine(line);  // Convert string to integer
                finalLine >> col2;             
                rows.push_back(col2);          // Store the data into a vector
            }
            rows.erase(rows.begin());          // Remove the item in the begining of vector(remove rows.at(0))
            finalData.push_back(rows);         // Store the vector into a 2D vector
        }
        data.close();   // close the file
    }
    else 
    {
        cout << "The file is not exist" << endl;
    }

    logfile(" load the data file into vector",username);
}


void printVec(vector<vector<int>> finalData)
{
    for (int i=0; i<finalData.size(); i++){         // The function will run until the i = the length of finalData (line by line)
        for(int j=0; j<finalData[i].size(); j++){   // The function will run until the i = the length of finalData[i] (column by column)
            cout << finalData[i][j]<< " ";        
        }
        cout << endl;
    }
}

void saveAs(vector<vector<int>> finalData, string &filenaming, string username)
{
    ofstream otherFile;          // A class to operate the file and given a name data(only for writing ).
    otherFile.open("test.txt");  // open the file("test.txt").

    if(otherFile.is_open()){                            // Check whether the file exist.
        for (int i=0; i<finalData.size(); i++){         // It will run the 2D vector automatically.
            for(int j=0; j<finalData[i].size(); j++){   // It will run the line 1 in 2D vecotr column by column in one line. 
                otherFile << finalData[i][j]<< ",";     // Save all the value in the 2D vector into file("test.txt").
            }
            otherFile << endl;  // Prevent the data save in same line. 
        }
    }
    otherFile.close();  // Close the ("test.txt")

    cout << "Enter a name to save the file by following format (filename.txt) : ";
    cin >> filenaming;

    char oldname[] = "test.txt";
    char newname[filenaming.length()+1]; // A character array. The length+1 because the last value in string is "\0"

    strcpy(newname, filenaming.c_str()); // The strcpy() used to copy one string to another and 
                                         // c_str() is returns a pointer to an array that  
                                         // contains a null-terminated sequence of characters representing 
                                         // the current value of the string object.

    if (rename(oldname,newname) == 0)  // rename succesfull will show 0, if unsuccesfull will show 1
        cout << "save the file succesfully" << endl; 
    else
        cout << "error" << endl;

    logfile(" has rename the file.",username);
}


void saveReport(string filenaming, string item, string result, string username)
{
    fstream report;                         // A class to operate the file and given a name data(can write and read).
    report.open(filenaming, ios_base::app); // open the file(that rename by user), 
                                            //ios_base::app used to append the data into file.

    if(report.is_open()){                        // Check whether the file exist.
        report << item << "," << result << endl; // Save the item, "," ,and result into file.
                                                 // item is maxmimum, minimum, mean, and etc.
                                                 // reuslt is the statistical computation. 
    }
    report.close(); //// Close the file(that rename by user)

    string history = " has added " + item + " into " + filenaming; 
    logfile(history, username); // logfile function
}



void saveHTML(int min, int max, double med, double mean, double var, double sd, string username)
{
    string line;
    int r1[] {min,max};                    		// Array that store all the information
    string s1[] {"Minimun", "Maximum",};   
    double r2[] {med, mean, var, sd};        
    string s2[] {"Median", "Mean", "Variance",  
                 "Standard Deviation"};

    fstream corr("correlation.txt", ios::in); // used to open the file and read it.
    fstream dis("distinct.txt", ios::in);     
    fstream his("histogram.txt", ios::in);    

    ofstream file; 						// A class to operate the file and given a name data(can only write).
    file.open("report.html"); // open the file. 
 
    if(file.is_open()){
        // All of line that start will (file <<) will save into a HTML file 
        file << "<!DOCTYPE html>" << endl;
        file << "<html>" << endl;
        file << "<style> table,th,td{border:1px solid black;}"
             << "table {border-collapse: collapse; background-color :#87CEFA}"
             << "thead,tbody {padding: 10px; font-family: \"Time New Roman\"; text-align: center;}"
             << "thead {font-family: \"sans-serif\"; font-size: 20px;}"
             << "tbody {font-size: 20px; white-space: pre;} h1{text-align: center; color: white}"
             << "</style>" << endl;
        file << "<title>Statistics page" << "</title>" <<endl;
        file << "<body style = \"background-color: #191970\">" << endl << "<h1>Statistics Table" 
             << "</h1>"<< endl << "<table width =\"60%\", align = \"center\"> " << endl;
        file << "<thead><th> Statistics " << "</th>"<< "<th> Statistics Compututation" 
             << "</thead>" << endl;
        file << "<tbody>";

        for(int j=0; j<2; j++){             // A for loop use to run same code but different content mutliple times.
            file << "<tr> <td>" << s1[j] << "</td>" << "<td>" 
            << r1[j] <<"</td>"<< "</tr>";   // s1[] and r1[] is the content that need to save
        }
        for (int i=0; i<4; i++) {           // A for loop use to run same code but different content mutliple times.
            file << "<tr> <td>" << s2[i] << "</td>" << "<td>" 
            << r2[i] <<"</td>"<< "</tr>";  // s2[] and r2[] is the content that need to save
        }
        
        file << "<tr> <td> Correlation between any selected 2 columns" << "</td>" << "<td>"; 
        if(corr.is_open()){             // Check whether the file exist
            while(!corr.eof()){         // Automatically check if the next line is not a empty 
                getline(corr,line);     // Store the data inside the file("correlation.txt") into line
                file << line << "<br>" << endl;   // Save the data into HTML file
            }}
        else
            file << 0 << endl;          // It will run when file not exist
        
        file << "</td>" << "</tr>" << endl;

        file << "<tr> <td> Distinct Data" << "</td>" << "<td>"; 
        if(dis.is_open()){              
            while(!dis.eof()){          
                getline(dis,line);      				// Store the data inside the file("distinct.txt") into line
                file << line << "<br>" << endl; // Save the data into HTML file
            }}
        else
            file << 0 << endl;         
        
        file << "</td>" << "</tr>" << endl;

        file << "<tr> <td> Histogram" << "</td>" << "<td style= \"text-align: left;\">"; 
        if(his.is_open()){           
            while(!his.eof()){          
                getline(his,line);      					// Store the data inside the file("histogram.txt") into line
                file << line << "<br>"  << endl;  // Save the data into HTML file
            }}
        else
            file << 0 << endl;          

        file << "</td>" << "</tr>" << endl;
    }
    else    
        cout << "File not exist" << endl; 
    file.close(); // Close the file

    logfile(" generate a HTML file.",username);
}
