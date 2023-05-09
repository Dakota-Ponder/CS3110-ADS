//
// Created by dlpon on 2/1/2022.
//

// Write a program that reads year values from a file and determines
// whether the year is a leap year or not.
#include <iostream>
using namespace std;


int main()
{
    // Declaring variables
    int year;

    cout << "Enter a year: " << endl;
    cin >> year;
    // While loop to read through file
    while(year < 2022)
    {
        // Add code to process year value here
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) // If the year is evenly divisible by 4 and 100
        {
            cout << year << " is a leap year." << endl;
        }
        else
        {
            cout << year << " is not a leap year." << endl;
        }
        cin >> year;

    }
    return 0;
}