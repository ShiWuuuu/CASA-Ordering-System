#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
#include <set>     // Include set for tracking printed categories
using namespace std;

void orderPlacement(char orders[15][5][25]);

// Menu List
//-------------------------------------------------------------------
char orders[15][5][25] =
{
    {"Burgers", "101", "Chicken Burger", "1", "5.00"},
    {"Burgers", "102", "Beef Burger", "1", "7.00"},
    {"Burgers", "103", "Cheese Burger", "1", "6.00"},
    {"Burgers", "104", "Fish Meat Burger", "1", "5.50"},
    {"Burgers", "105", "Big Burger", "1", "7.00"},
    {"Drinks", "201", "Cola", "1", "3.00"},
    {"Drinks", "202", "100Plus", "1", "3.00"},
    {"Drinks", "203", "Fanta", "1", "3.00"},
    {"Drinks", "204", "Sarsi", "1", "3.00"},
    {"Drinks", "205", "Orange Juice", "1", "4.50"},
    {"Sides", "301", "Fried Fries", "1", "5.00"},
    {"Sides", "302", "Chicken Nuggets (4pc)", "1", "5.70"},
    {"Sides", "303", "Chicken Nuggets (8pc)", "1", "10.40"},
    {"Sides", "304", "Chicken Nuggets (12pc)", "1", "16.10"},
    {"Sides", "305", "Ice Cream", "1", "1.50"},
};
//-------------------------------------------------------------------

//Print Menu
void printingMenu() {
    set<string> printedCategories; // Set to keep track of printed categories
    // Printing the header
    cout << setw(41) << setfill('-') << "" << setfill(' ') << endl;
    cout << left << setw(8) << "FoodID" << fixed << setprecision(2) << setw(25)
        << "Name" << right << setw(8) << "Price" << endl;
    cout << setw(41) << setfill('-') << "" << setfill(' ') << endl;
    for (int i = 0; i < 15; i++) {
        string category = orders[i][0];
        // Print category title only once
        if (printedCategories.find(category) == printedCategories.end()) {
            cout << setw(16) << "--" << category << "--" << endl;
            printedCategories.insert(category);
        }
        // Print order details
        cout << left << setw(8) << orders[i][1] << fixed << setprecision(2) <<
            setw(25) << orders[i][2] << right << setw(8) << orders[i][4] << endl;
    }
    cout << setw(41) << setfill('-') << "" << setfill(' ') << endl;
    cout << endl;
    orderPlacement(orders);  // Proceed to order placement after printing menu
}

