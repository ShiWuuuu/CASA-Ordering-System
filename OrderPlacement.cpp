#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

//declaration of functions
void orderPlacement(char orders[15][5][25]); //get the array from orderMenu
void printOrderSummary(char orderList[100][4][25], int orderCount); //take order and calculate order count
bool isInteger(string input);

void orderPlacement(char orders[15][5][25]) {

	string foodID;
	char orderList[100][4][25]; // 100 orders max, each with ID, Qty, and Price
	int orderCount = 0; // Tracks number of orders
	int quantity; //this quantity act as a string and will insert to array
	string quantityString;
	string input;

	while (orderCount < 101){

		bool itemFound = false; // Reset itemFound for each iteration
		cout << ">> Place your order by entering FoodID (e.g. 101): ";
		getline(cin, input);
		if (isInteger(input)) {
			for (int i = 0; i < 15; i++) {
				// Use strcmp to compare C-strings
				if (strcmp(orders[i][1], input.c_str()) == 0) {
					cout << ">> " << orders[i][2] << " has been selected.\n" << endl;
					itemFound = true;
					foodID = input;
				}
			}
			if (!itemFound) {
				cout << ">> Invalid FoodID. Please try again." << endl;
				continue;
			}
		}
		else {
			cout << ">> Invalid FoodID. Please try again." << endl;
			continue;
		}
		while (true) {
			cout << ">> Quantity of food: ";
			getline(cin, input);
			if (isInteger(input)) {
				quantity = stoi(input);
				if (quantity < 1) {
					cout << ">> Quantity must be at least 1. Please try again." << endl;
					continue; // Skip the rest of the loop and prompt for input again
				}
				else {
					quantityString = input;
					break;
				}
			}
			else {
				cout << ">> Invalid input. Please enter a valid positive quantity." << endl;
				continue;
			}
			if (quantity < 1) {
				cout << ">> Quantity must be at least 1. Please try again." << endl;
				continue; // Skip the rest of the loop and prompt for input again
			}
		}

		for (int i = 0; i < 15; i++) {
			// Use strcmp to compare C-strings
			if (strcmp(orders[i][1], foodID.c_str()) == 0) {
				//Collect selected entity then save it in oderList array
				strcpy(orderList[orderCount][0], orders[i][1]); // Copy FoodID
				strcpy(orderList[orderCount][1], orders[i][2]); // Copy FoodName
				strcpy(orderList[orderCount][2], quantityString.c_str()); // Copy FoodQuantity
				strcpy(orderList[orderCount][3], orders[i][4]); // Copy Price

				orderCount++;
				itemFound = true;

				cout << endl << quantity << " x " << orders[i][2] << " added to your order." << endl;
				cout << ">> Current orders amount (" << orderCount << "/100)." << endl;
				break; // Exit loop after finding the item

			}
		}

		if (!itemFound) {
			cout << ">> Invalid FoodID. Please try again." << endl;
			continue;
		}

		if (orderCount < 101) {
			string choice;
			while (true) {
				cout << endl << ">> Do you wish to place another order? (y/n): ";
				getline(cin, choice);

				if (choice == "y" || choice == "Y") {
					break; // Exit inner loop to continue ordering
				}
				else if (choice == "n" || choice == "N") {
					// Exit the outer loop and proceed to finalization
					printOrderSummary(orderList, orderCount);
					return; // Exit function to avoid finalizing multiple times
				}
				else {
					cout << ">> Unknown input. Please enter 'y' for yes or 'n' for no." << endl;
				}
			}
		}
		else {
			cout << ">> Order limit reached! No more orders can be placed." << endl;
			printOrderSummary(orderList, orderCount);
			return; // Exit function as the order list is full
		}
	}
}