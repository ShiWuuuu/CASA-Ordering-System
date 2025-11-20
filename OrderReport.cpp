#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <ctime> // For date and time
using namespace std;

void updateOrderReport(char orderList[100][4][25], int orderCount, double roundedPrice, string paymentType, double amountPaid);
void printOrderReport();
void feedbackPrint(double rating);
int main();
bool isInteger(string input);

int reportCount = 0;
int cashPaymentCount = 0;
int eWalletPaymentCount = 0;
double overAllEarned = 0;
double feedback = 0;
double overAllCash;
double overAlleWallet;

char ordersReport[15][3][25] = {
    {"101", "Chicken Burger", "0"},
    {"102", "Beef Burger", "0"},
    {"103", "Cheese Burger", "0"},
    {"104", "Fish Meat Burger", "0"},
    {"105", "Big Burger", "0"},
    {"201", "Cola", "0"},
    {"202", "100Plus", "0"},
    {"203", "Fanta", "0"},
    {"204", "Sarsi", "0"},
    {"205", "Orange Juice", "0"},
    {"301", "Fried Fries", "0"},
    {"302", "Chicken Nuggets (4pc)", "0"},
    {"303", "Chicken Nuggets (8pc)", "0"},
    {"304", "Chicken Nuggets (12pc)", "0"},
    {"305", "Ice Cream", "0"}
};


void feedbackPrint(double rating) {
    feedback = rating;
}

void updateOrderReport(char orderList[100][4][25], int orderCount, double roundedPrice, string paymentType, double amountPaid) {
    // Update quantities and calculate totals for the report
    for (int i = 0; i < orderCount; i++) {
        int quantity = atoi(orderList[i][2]); // Convert string to integer

        // Find matching order in the report and update quantity and earnings
        for (int j = 0; j < 15; j++) {
            if (strcmp(ordersReport[j][0], orderList[i][0]) == 0) {
                int currentQuantity = atoi(ordersReport[j][2]);
                overAllEarned += roundedPrice;
                // Update the quantity and total earned
                sprintf(ordersReport[j][2], "%d", currentQuantity + quantity);
                break;
            }
        }
    }

    // Update payment type counts
    if (paymentType == "Cash") {
        cashPaymentCount++;
        overAllCash += roundedPrice;

    }
    else if (paymentType == "e-Wallet") {
        eWalletPaymentCount++;
        overAlleWallet += amountPaid;
    }
}

void printOrderReport() {
    auto now = chrono::system_clock::now();
    auto in_time_t = chrono::system_clock::to_time_t(now);
    tm buf;
    localtime_s(&buf, &in_time_t);
    cout << setfill('-') << setw(50) << "-" << setfill(' ') << endl;
    cout << left << setw(26) << "[Daily Sales Report]" << right << setw(14) << "Date: " << setw(10) << put_time(&buf, "%Y-%m-%d") << endl;


    cout << setfill('-') << setw(50) << "-" << setfill(' ') << endl;
    // Table titles
    cout << left << setw(10) << "FoodID" << setw(25) << "Food Name" << right << setw(15) << "Quantity" << endl;

    // Draw a line & reset
    cout << setfill('-') << setw(50) << "-" << setfill(' ') << endl;

    for (int i = 0; i < 15; i++) {
        int quantity = atoi(ordersReport[i][2]);

        cout << fixed << setprecision(2) << left << setw(10) << ordersReport[i][0] << setw(25) << ordersReport[i][1] << right << setw(15) << quantity << endl;
    }

    cout << setfill('-') << setw(50) << "-" << setfill(' ') << endl;
    // Print payment type summary
    cout << left << setw(30) << "Total Sales (RM):" << right << setw(20) << overAllEarned << endl;
    cout << left << setw(30) << "Total Cash (RM): " << right << setw(20) << overAllCash << endl;
    cout << left << setw(30) << "Total e-Wallet (RM):"  << right << setw(20) << overAlleWallet << endl;
    cout << setfill('-') << setw(50) << "-" << setfill(' ') << endl << endl;

    cout << setfill('-') << setw(50) << "-" << setfill(' ') << endl;
    cout << setw(26) << "[Daily Performance Report]" << right << setw(14) << "Date: " << setw(10) << put_time(&buf, "%Y-%m-%d") << endl;
    cout << setfill('-') << setw(50) << "-" << setfill(' ') << endl << endl;

    cout << "[Customer Feedback Report]" << endl;
    cout << left << setw(14) << "Average Rating" << right << setfill('.') << setw(36) << setprecision(1) << feedback << endl << endl;
    cout << "[PaymentMethod Breakdown Report]" << endl;
    cout << left << setw(20) << "Cash Payments Counts" << right << setw(30) << cashPaymentCount << endl;
    cout << left << setw(24) << "e-Wallet Payments Counts" << right << setw(26) << eWalletPaymentCount << endl << endl;
    cout << setfill('-') << setw(50) << "-" << setfill(' ') << endl << endl;

    cout << "9. Back to Main Menu \n0. Exit" << endl;
    bool running = true;
    int choice;
    string input;

    while (running) {
        cout << ">> Please enter a number: ";
        getline(cin, input);
        if (isInteger(input)) {
            choice = stoi(input);
            switch (choice) {
            case 9:
                running = false;
                main();
                break;
            case 0:
                running = false;
                cout << ">> Looking forward to seeing you again soon!" << endl;
                break;
            default:
                cout << ">> Invalid input, please enter again.." << endl;
            }
        }
        else {
            cout << ">> Invalid input, please enter again.." << endl;
        }
    }
    return;
}