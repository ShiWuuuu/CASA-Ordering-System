#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <string>
#include <chrono>
#include <ctime> // For date and time
using namespace std;

int main();
void printingMenu();
void printOrderSummary(char orderList[100][4][25], int orderCount);
void paymentMethod(double price, char orderList[100][4][25], int orderCount, double subtotal, double totalPrice, double roundedPrice, string paymentType, double amountPaid);
void printReceipt(char orderList[100][4][25], int orderCount, double subtotal, double totalPrice, double roundedPrice, string paymentType, double amountPaid);
void updateOrderReport(char orderList[100][4][25], int orderCount, double totalPrice, string paymentType, double amountPaid);

int invoiceNumber = 0;
int receiptNumber = 0;

void printOrderSummary(char orderList[100][4][25], int orderCount) {

	double subtotal = 0;
	int totalItems = 0;
	double totalPrice = 0;
	double roundedPrice = 0;
	double remainder = 0;
	const double serviceTax = 0.06; //constant number for service tax
	double discountAmount = 0;
	const double discountPercentage = 0.1;

	auto now = chrono::system_clock::now();
	auto in_time_t = chrono::system_clock::to_time_t(now);
	tm buf;
	localtime_s(&buf, &in_time_t);

	invoiceNumber++;

	cout << "\n[Invoice] \n";
	cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
	cout << setw(17) << "" << right << "CASA Fast-Food Restaurant";

	cout << endl << setw(17) << "" << right << "Lot.15, Jalan Tanjung Aru,";
	cout << endl << setw(17) << "" << right << "88100 Kota Kinabalu, Sabah," << endl;
	cout << left << setw(25) << "" << "Malaysia.";
	cout << endl << endl << setw(18) << "" << right << "Tel: +60 88-765 432" << endl;
	cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
	cout << left << "Invoice No." << setw(3) << invoiceNumber << setw(30) << "" << "Date: " << setw(10) << put_time(&buf, "%Y-%m-%d") << endl << endl;

	cout << setfill('-') << setw(60) << "-" << endl; //Draw a line
	cout << setfill(' '); //Reset the format

	//Table titles
	cout << left << setw(10) << "FoodID" << setw(25) << "Name" << right << setw(10) << "Quantity" << setw(15) << "Price(RM)" << endl;

	//Draw a line & reset
	cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;

	//Loop FOR to display all orders accorddingly
	for (int i = 0; i < orderCount; i++) {
		cout << fixed << setprecision(2) << left << setw(10) << orderList[i][0] << setw(25) << orderList[i][1] << right << setw(10) << orderList[i][2] << setw(15) << orderList[i][3] << endl;
		//ExampleOutput: Cheeseburger 2 10.00

		int quantity = atoi(orderList[i][2]); //make the string become integers
		double price = atof(orderList[i][3]); //make the string become double

		subtotal += quantity * price; //subtotal will be sum up the price with the quantity in each iterations
		totalItems += quantity;
	}

	if (subtotal >= 60) {
		discountAmount = - (subtotal * discountPercentage);
	}
	totalPrice = subtotal + (serviceTax * subtotal) + discountAmount;
	roundedPrice = round(totalPrice * 10) / 10;
	remainder = roundedPrice - totalPrice;

	//Draw a line & reset
	cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;

	cout << right << setw(35) << "Total Items:" << setw(25) << totalItems << endl;
	cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
	cout << fixed << setprecision(2) << right << setw(35) << "Subtotal:" << setw(25) << subtotal << endl;
	cout << fixed << setprecision(2) << right << setw(35) << "Service Tax (6%):" << setw(25) << (subtotal * serviceTax) << endl;
	if (subtotal >= 60) {
		cout << fixed << setprecision(0) << right << setw(30	) << "Discount (" << setw(2) << (discountPercentage * 100) << setw(3) << "%):" << setw(25) << setprecision(2) << showpos << discountAmount << noshowpos << endl;
	}
	else {
		cout << fixed << setprecision(0) << right << setw(35) << "Discount (0%):"  << setw(25) << setprecision(2) << showpos << discountAmount << noshowpos << endl;
	}
	cout << fixed << setprecision(2) << right << setw(35) << "Total Payment:" << setw(25) << (totalPrice) << endl;
	cout << fixed << setprecision(2) << right << setw(35) << "Rounded-off:" << setw(25) << showpos << (remainder) << noshowpos << endl;
	cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
	cout << fixed << setprecision(2) << right << setw(35) << "Overall Payment:" << setw(25) << (roundedPrice) << endl;

	//Draw a line & reset
	cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
	if (subtotal >= 60) {
		cout << ">> Hooray! Your total achieved RM60, so you get a 10% discount :)" << endl << endl;
	}

	string paymentType;
	double amountPaid = 0.0;
	while (true) {
		string input;
		cout << ">> Do you want to proceed to payment? (y/n): ";
		getline(cin, input);
		if (input == "y" || input == "Y") {
			cout << ">> Proceeding to payment.." << endl;
			paymentMethod(roundedPrice, orderList, orderCount, subtotal, totalPrice, roundedPrice, paymentType, amountPaid);
			break;
		}
		else if (input == "n" || input == "N") {
			cout << ">> Order has been canceled.\n";
			cout << ">> Do you want to return to: " << endl;
			cout << "1. Main Menu \n2. Place Order" << endl << endl;
			cout << ">> Please enter your choice: ";
			while (true) {
			getline(cin, input);

				if (input == "1") {
					cout << ">> Returning to the main menu..\n\n";
					main();
					break;
				}

				else if (input == "2") {
					cout << ">> Starting a new order..\n\n";
					printingMenu();
					break;
				}

				else {
					cout << ">> Invalid choice, please try again.." << endl;
					continue;
				}
			}
			break; 
		}
		else { 
				cout << ">> Invalid choice, please try again.." << endl;
				continue;
			}
		}
	}

void printReceipt(char orderList[100][4][25], int orderCount, double subtotal, double totalPrice, double roundedPrice, string paymentType, double amountPaid) {
	const double serviceTax = 0.06; // constant number for service tax
	const double discountPercentage = 0.1;
	double discountAmount = 0.0;
	int totalItems = 0;
	auto now = chrono::system_clock::now();
	auto in_time_t = chrono::system_clock::to_time_t(now);
	tm buf;
	localtime_s(&buf, &in_time_t);

	receiptNumber++;
	
	cout << "\n[Receipt] \n";
	cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
	cout << setw(17) << "" << right << "CASA Fast-Food Restaurant";

	cout << endl << setw(17) << "" << right << "Lot.15, Jalan Tanjung Aru,";
	cout << endl << setw(17) << "" << right << "88100 Kota Kinabalu, Sabah," << endl;
	cout << left << setw(25) << "" << "Malaysia.";
	cout << endl << endl << setw(18) << "" << right << "Tel: +60 88-765 432" << endl;
	cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
	cout << left << "Receipt No." << setw(3) << receiptNumber << setw(30) << "" << "Date: " << setw(10) << put_time(&buf, "%Y-%m-%d") << endl << endl;

	// Print header
	cout << setfill('-') << setw(60) << "-" << endl;
	cout << setfill(' '); // Reset format

	// Table titles
	cout << left << setw(10) << "FoodID" << setw(25) << "Name" << right << setw(10) << "Quantity" << setw(15) << "Price(RM)" << endl;

	// Draw a line & reset
	cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;

	// Loop to display all orders
	for (int i = 0; i < orderCount; i++) {
		int quantity = atoi(orderList[i][2]); // Convert string to integer
		double price = atof(orderList[i][3]); // Convert string to double
		totalItems += quantity;

		cout << fixed << setprecision(2) << left << setw(10) << orderList[i][0] << setw(25) << orderList[i][1]
			<< right << setw(10) << quantity << setw(15) << price << endl;
	}
	if (subtotal >= 60) {
		discountAmount = -(subtotal * discountPercentage);
	}

	// Draw a line & reset
	cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;

	// Print totals
	cout << right << setw(35) << "Total Items:" << setw(25) << totalItems << endl;
	cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
	cout << fixed << setprecision(2) << right << setw(35) << "Subtotal:" << setw(25) << subtotal << endl;
	cout << fixed << setprecision(2) << right << setw(35) << "Service Tax (6%):" << setw(25) << (subtotal * serviceTax) << endl;
	if (subtotal >= 60) {
		cout << fixed << setprecision(0) << right << setw(30) << "Discount (" << setw(2) << (discountPercentage * 100) << setw(3) << "%):" << setw(25) << setprecision(2) << showpos << discountAmount << noshowpos << endl;
	}
	else {
		cout << fixed << setprecision(0) << right << setw(35) << "Discount (0%):" << setw(25) << setprecision(2) << showpos << discountAmount << noshowpos << endl;
	}
	cout << fixed << setprecision(2) << right << setw(35) << "Total Payment:" << setw(25) << totalPrice << endl;
	cout << fixed << setprecision(2) << right << setw(35) << "Rounded-off:" << setw(25) << showpos << (roundedPrice - totalPrice) << noshowpos << endl;
	cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
	cout << fixed << setprecision(2) << right << setw(35) << "Overall Payment:" << setw(25) << roundedPrice << endl;
	// Print payment details
	cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
	cout << right << setw(35) << "Payment Method:" << setw(25) << paymentType << endl;
	cout << fixed << setprecision(2) << right << setw(35) << "Amount Paid:" << setw(25) << amountPaid << endl;
	if (paymentType == "Cash") {
		cout << fixed << setprecision(2) << right << setw(35) << "Change:" << setw(25) << (amountPaid - roundedPrice) << endl;
	}
	cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;

	updateOrderReport(orderList, orderCount, roundedPrice, paymentType, amountPaid);
	return;
}
