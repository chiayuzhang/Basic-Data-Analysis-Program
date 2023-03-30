#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include <iomanip>
#include <fstream>

using namespace std;

string output(string file)
{   
    string line, out;
    fstream dataIn(file, ios::in);
    while (!dataIn.eof()) {
        getline(dataIn, line);
        out += "\n" + line;
    }
    dataIn.close();
    return out;
}

// Function for finding the maximum of the column

int maximum(vector<vector<int>> vec,int col)
{
    int max;
    for (int i=0; i<vec.size(); i++)                      // Going through the row of the vector
        for (int j=0; j < vec[i].size(); j++)             // Going through the columns of the vector
            if (j == col)                                 // if it reaches the column the user selcted
                if (vec[i][col] > max) max = vec[i][col]; // set the max if the value is more than max
    return max;
}

// Function for finding the minimum of the column

int minimum(const vector<vector<int>> vec,int col)
{
    int min;
    vector<int> a;
    for (int i=0; i<vec.size(); i++)
        for (int j=0; j<vec[i].size(); j++)
            if (j == col)                       // detects if it reaches the column the user selected                               
                a.push_back(vec[i][col]);       // gets the vector element from the column chosen by the user and puts it into vector a

    min = *min_element(a.begin(), a.end());     // the min_element will goes through the vector a and find the minimum
    return min;
}

// Function for finding the median of the column

int median(const vector<vector<int>> vec, int col)
{
    int midpoint, n;
    vector<int> vc;

    for (int i=0; i < vec.size(); i++)
        for (int j=0; j < vec[i].size(); j++)
            if (j == col)
            {
                n += 1;                          // getting the amount of data,n
                vc.push_back(vec[i][col]);       // gets the vector element from the column chosen by the user and puts it into vector vc
            }

    sort(vc.begin(), vc.end());                  // sorts vector vc in an ascending order

    if (n % 2 == 0)    // detects if the amount of data is odd or even
    {
         //if even
        midpoint = n/2;
        return (vc[midpoint] + vc[midpoint-1]) / 2;
    }
    
    else 
    {
        //if odd
        midpoint = (n+1)/2;
        return vc[midpoint-1];
    }    
}

// Function for finding the mean of the column

double mean(const vector<vector<int>> vec, int col)
{
    double sum;
    int sz = 0;
    for (int i=0; i < vec.size(); i++){
        for (int j=0; j < vec[i].size(); j++){
            if (j == col){
                sz += 1;                // getting the size of the data
                sum += vec[i][col];     // calculate the sum if the column
            }
        }
    }
    
    double median = sum/sz;    // calculate the median
    return median;
}

// Function for finding the variance of the column

double variance(const vector<vector<int>> vec, int col)
{
    double sum = 0;
    int sz = 0;
    for (int i=0; i < vec.size(); i++){
        for (int j=0; j < vec[i].size(); j++){
            if (j == col){
                sz += 1;                                                                // getting the size of the data
                 // calculate the sum for the numerator of the  variance formula
                sum += (vec[i][col] - mean(vec, col)) * (vec[i][col] - mean(vec, col));
            }
        }
    }
    
    double variance = sum/(sz-1);     // calculate the variance
    return variance;
}

// Function for finding the standard deviation of the column

double standarddev(const vector<vector<int>> vec, int col)
{
    return sqrt(variance(vec, col)); // calculate the standard deviation by square root as per the formula
}

// Function for finding the correlation between two columns

void correlation(const vector<vector<int>> vec, int col1, int col2)
{
    int *arr1, *arr2;
    double mean1 = mean(vec, col1), mean2 = mean(vec,col2), sum1=0, sum2=0, sum3=0, r;
    arr1 = new int[vec.size()];
    arr2 = new int[vec.size()];
    for (int i = 0; i < vec.size(); i++)
        for(int j = 0; j < vec[i].size(); j++)
        {
            if (j == col1)
                arr1[i] = vec[i][j]; // gets the element from column 1 and puts it into arr1
            else if (j == col2) 
                arr2[i] = vec[i][j]; // gets the element from column 2 and puts it into arr2
        }
    cout << "*****************************************************************\n"
         << "| Sum of (X - Mx)(Y - My) | Sum of (X - Mx)2 | Sum of (Y - My)2 |\n"
         << "*****************************************************************\n";   // prints out the table header
    for (int i = 0; i <vec.size(); i++)
    {
        // prints out the result into tabular form
        cout << "|" << setw(25) << (arr1[i]-mean1) * (arr2[i]-mean2) << "|" << setw(18) << pow((arr1[i]-mean1), 2) << "|" << setw(18) << pow((arr2[i]-mean2), 2) << "|\n";
        sum1 += (arr1[i]-mean1) * (arr2[i]-mean2); // sum up the results into sum1
        sum2 += pow((arr1[i]-mean1), 2);           // sum up the results into sum2
        sum3 += pow((arr2[i]-mean2), 2);           // sum up the results into sum3
    }
    cout << "*****************************************************************\n"
         << "| Sum" << setw(21) << sum1 << "| Sum" << setw(14) << sum2 << "| Sum" << setw(14) << sum3 << "|\n" // prints out all the sum from the results
         << "*****************************************************************\n\n";
    
    r =  sum1 / sqrt(sum2 * sum3); // calculate the Pearson Correlation

    cout << "        Sum of (X - Mx)(Y - My)      \n"
         << "-------------------------------------  => R => " << r << "\n" // prints out the result, r
         << "/(Sum of (X - Mx)2)(Sum of (Y - My)2)\n"
         << "\n(nb. the nearer the value is to zero, the weaker the relationship)";

    delete [] arr1; // delete the array to free the memory
    delete [] arr2;
}


void correlation_r(const vector<vector<int>> vec, int col1, int col2)
{
    int *arr1, *arr2;
    double mean1 = mean(vec, col1), mean2 = mean(vec,col2), sum1=0, sum2=0, sum3=0, r;
    arr1 = new int[vec.size()];
    arr2 = new int[vec.size()];
    for (int i = 0; i < vec.size(); i++)
        for(int j = 0; j < vec[i].size(); j++)
        {
            if (j == col1)
                arr1[i] = vec[i][j];
            else if (j == col2) arr2[i] = vec[i][j];
        }
    fstream cout("correlation.txt", ios::out);
    cout << "*****************************************************************\n"
         << "| Sum of (X - Mx)(Y - My) | Sum of (X - Mx)2 | Sum of (Y - My)2 |\n"
         << "*****************************************************************\n";
    for (int i = 0; i <vec.size(); i++)
    {
        cout << "|" << setw(25) << (arr1[i]-mean1) * (arr2[i]-mean2) << "|" << setw(18) << pow((arr1[i]-mean1), 2) << "|" << setw(18) << pow((arr2[i]-mean2), 2) << "|\n";
        sum1 += (arr1[i]-mean1) * (arr2[i]-mean2);
        sum2 += pow((arr1[i]-mean1), 2);
        sum3 += pow((arr2[i]-mean2), 2);
    }
    cout << "*****************************************************************\n"
         << "| Sum" << setw(21) << sum1 << "| Sum" << setw(14) << sum2 << "| Sum" << setw(14) << sum3 << "|\n"
         << "*****************************************************************\n\n";
    
    r =  sum1 / sqrt(sum2 * sum3);

    cout << "        Sum of (X - Mx)(Y - My)      \n"
         << "-------------------------------------  => R => " << r << "\n"
         << "/(Sum of (X - Mx)2)(Sum of (Y - My)2)\n"
         << "\n(nb. the nearer the value is to zero, the weaker the relationship)";

    delete [] arr1;
    delete [] arr2;
}


// Function for printing out the distinct data table

void distinct_data(const vector<vector<int>> vec)
{
    vector<int> vc, dn;
    set<int> s;
    
  
    for (int i=0; i<vec.size(); i++)
        for(int j=0; j<vec[i].size(); j++)
            vc.push_back(vec[i][j]);            // set all elements from vec into vc

    for (int i=0; i<vc.size(); i++) 
        s.insert(vc[i]);                        // insert all elements from vc into set s
    cout << "_______________________" << endl;
    cout << "| Distinct Data Table |" << endl;
    cout << "=======================" << endl;  // prints table header
    cout << "| Number | Frequency  |" << endl;
    cout << "=======================" << endl;

    for (auto val : s)
    {
        int freq = count(vc.begin(), vc.end(), val); // counts the frequency for element
        if (freq == 1)        // if frequency is equal to 1, set the elements into dn
            dn.push_back(val);
        cout << "| "<< setw(7) << left << val << "| " << setw(10) << left << freq << " |" << endl; // prints out the element and frequency in a tabular form
    }
    cout << "=======================" << "\n" << "Distinct Numbers:";
    for (int i=0; i<dn.size(); i++)
        cout << " " << dn[i];       // prints out the distinct numbers
   cout << "\n"; 
}

void distinct_data_r(const vector<vector<int>> vec)
{
    vector<int> vc, dn;
    set<int> s;
    
  
    for (int i=0; i<vec.size(); i++)
        for(int j=0; j<vec[i].size(); j++)
            vc.push_back(vec[i][j]);

    for (int i=0; i<vc.size(); i++)
        s.insert(vc[i]);
    fstream cout("distinct.txt", ios::out);
    cout << "_______________________" << endl;
    cout << "| Distinct Data Table |" << endl;
    cout << "=======================" << endl;
    cout << "| Number | Frequency  |" << endl;
    cout << "=======================" << endl;

    for (auto val : s)
    {
        int freq = count(vc.begin(), vc.end(), val);
        if (freq == 1)  
            dn.push_back(val);
        cout << "| "<< setw(7) << left << val << "| " << setw(10) << left << freq << " |" << endl;
    }
    cout << "=======================" << "\n" << "Distinct Numbers:";
    for (int i=0; i<dn.size(); i++)
        cout << " " << dn[i];
   cout << "\n";
}

// Funtion to print the histogram

void histogram(const vector<vector<int>> vec)
{
    vector<int> vc;
    set<int> s;
    int sum[10] = {0,0,0,0,0,0,0,0,0,0}, pos = 0, point = 100;

    for (int i=1; i<vec.size(); i++)
        for(int j=0; j<vec[i].size(); j++)
        {
            vc.push_back(vec[i][j]);        // puts all the elements from vec into vc
            s.insert(vec[i][j]);            // inserts the the elements from vec into set s
        }
    
    cout << "Count Midpoint\n"; 

    for (auto val : s)
    {
        // calculate the frequency for each element and adds it into sum array for its range
        int freq = count(vc.begin(), vc.end(), val);
        if (val > 90) sum[0] += freq;
        else if (val > 80) sum[1] += freq;
        else if (val > 70) sum[2] += freq;
        else if (val > 60) sum[3] += freq;
        else if (val > 50) sum[4] += freq;
        else if (val > 40) sum[5] += freq; 
        else if (val > 30) sum[6] += freq;
        else if (val > 20) sum[7] += freq;
        else if (val > 10) sum[8] += freq;
        else sum[9] += freq;
    }
    
    while (pos != 10)
    {   
        cout << setw(6) << left << sum[pos] << setw(2) << (point+(point-10))/2 << "|"; // prints out the midpoint
        for (int i = 0; i <sum[pos]; i++)
        {
            cout << "=";  // prints the bar based on the sum from each range
        }
        cout << endl;
        point -= 10;
        pos++;
    }

    // prints histogram footer
    cout << "        +---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+ Frequency\n"
         << "        0         10        20        30        40        50        60        70        80        90        100\n";
}

void histogram_r(const vector<vector<int>> vec)
{
    vector<int> vc;
    set<int> s;
    int sum[10] = {0,0,0,0,0,0,0,0,0,0}, pos = 0, point = 100;

    for (int i=1; i<vec.size(); i++)
        for(int j=0; j<vec[i].size(); j++)
        {
            vc.push_back(vec[i][j]);
            s.insert(vec[i][j]);
        }
    
    fstream cout("histogram.txt", ios::out);
    cout << "Count Midpoint\n";

    for (auto val : s)
    {
        int freq = count(vc.begin(), vc.end(), val);
        if (val > 90) sum[0] += freq;
        else if (val > 80) sum[1] += freq;
        else if (val > 70) sum[2] += freq;
        else if (val > 60) sum[3] += freq;
        else if (val > 50) sum[4] += freq;
        else if (val > 40) sum[5] += freq;
        else if (val > 30) sum[6] += freq;
        else if (val > 20) sum[7] += freq;
        else if (val > 10) sum[8] += freq;
        else sum[9] += freq;
    }
    
    while (pos != 10)
    {   
        cout << setw(6) << left << sum[pos] << setw(2) << (point+(point-10))/2 << "|";
        for (int i = 0; i <sum[pos]; i++)
        {
            cout << "=";
        }
        cout << endl;
        point -= 10;
        pos++;
    }

    cout << "        +---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+ Frequency\n"
         << "        0         10        20        30        40        50        60        70        80        90        100\n";
}

// main()
// {
//     int id = 1191103291;
//     string out;
//     vector<vector<int>> vec;

//     loadDataFile(vec,id);
//     // int max = maximum(vec, 2);
//     // cout << "THE MAX ----------> " << max << endl;
//     // int min = minimum(vec, 2);
//     // cout << "THE MIN ----------> " << min << endl;
//     histogram_r(vec);
//     histogram(vec);
//     distinct_data_r(vec);
//     correlation_r(vec, 1, 2);

//     return 0;
// }