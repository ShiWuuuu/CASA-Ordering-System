#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

void menu(bool isStaff); //declare function(selection of functions)
void printingMenu();
void authorization(int role);
void printOrderReport();
void shiftController();
void shiftRemote(bool shift);
bool isInteger(string input);
bool isDouble(string input);

bool shiftOpen = true;

void displaySepcial();

void displaySpecial() {
	cout << "          |                  |" << endl;
	cout << " " << setfill('-') << setw(38) << "" << setfill(' ') << endl;
	cout << "| *      TODAY\'S SPECIAL OFFER!      * | \n|        MINIMUM SPEND RM60 TO         |\n| *        GET 10% DISCOUNT!         * |" << endl;
	cout << " " << setfill('-') << setw(38) << "" << setfill(' ') << endl;
}
//Main Menu
int main() {

	string choices;
	int number;
	bool running = true;

	displaySpecial();

	cout << "  Welcome to CASA Fast-Food Restaurant!" << endl << endl;
	cout << "Log in as:" << endl;
	cout << "1. Customer \n2. Staff \n\n0. Exit" << endl << endl;

	while (running) {

		cout << ">> Please enter a number: ";
		getline(cin, choices);

		if (isInteger(choices)) {

			number = stoi(choices); //Make the choice(string) become an integer

			switch (number) {
			case 0:
				cout << ">> Looking forward to seeing you again soon!" << endl;
				running = false;
				break;
			case 1:
				running = false;
				authorization(number);
				break;

			case 2:
				running = false;
				authorization(number);
				break;

			default:
				cout << ">> Please enter a valid number!" << endl;
				break;
			}
		}
		else {
			cout << ">> Please enter a valid number!" << endl;
		}
	}
	return 0;
}

//Choice Checker Function
bool isInteger(string input) {
	// Check if the input string is empty
	if (input.empty()) {
		return false;
	}
	// Check every single character in the string, if found any character that is not integer than return false
	for (int i = 0; i < input.size(); i++) {
		if (!isdigit(input[i])) {
			return false;
		} 
	}
	return true;
}
bool isDouble(string input) {
	bool decimalFound = false;  // To track if there's a decimal point in the string
	bool digitFound = false;    // To ensure that at least one digit is present

	// Check if the input string is empty
	if (input.empty()) {
		return false;
	}

	// Start looping from the first character
	for (int i = 0; i < input.size(); i++) {
		char currentChar = input[i];

		// Allow a leading minus sign, but only at the beginning
		if (i == 0 && currentChar == '-') {
			continue;
		}

		// If the character is a decimal point, ensure it's the first one
		if (currentChar == '.') {
			if (decimalFound) {
				return false;  // More than one decimal point found
			}
			decimalFound = true;
			continue;
		}

		// If the character is a digit, mark that a digit has been found
		if (isdigit(currentChar)) {
			digitFound = true;
			continue;
		}

		// If any other character is found, it's not a valid double
		return false;
	}

	// Ensure that at least one digit was found
	return digitFound;
}


//Authorization Function
void authorization(int role) {
	int number;
	string input;
	int staffID;
	bool isStaff = false;
	bool running = true;
	if (role == 1) {
		cout << endl;
		cout << ">> You are successfully logged in as a customer!\n" << endl;
		menu(false);
	}
	else {
		cout << endl;
		cout << ">> Please enter staff ID: " << endl;
		cout << "0. Exit" << endl << endl;
		while (running) {
			cout << ">> Staff ID: ";
			getline(cin, input);

			if (isInteger(input)) {
				staffID = stoi(input);

				if (staffID == 123) {
					cout << ">> You are successfully logged in as staff!" << endl << endl;
					menu(true);
					break;
				}
				else if (staffID == 0) {
					main();
					break;
				}
				else {
					cout << ">> Authorization failed, please try again.." << endl;
				}
			}
			else {
				cout << ">> Authorization failed, please try again.." << endl;
			}
		}
	}
}
//second menu
void menu(bool isStaff) {

	int number;
	string choices;
	bool running = true;


	cout << setfill('-') << setw(26) << "-" << endl;
	cout << setfill(' ');
	cout << setw(15) << "Menu" << endl;
	cout << setfill('-') << setw(26) << "-" << endl;
	cout << setfill(' ');
	cout << "1. Take Order" << endl;
	if (isStaff == true) {
		cout << "2. Reports \n3. Shifts Controller " << endl;
	}
	cout << endl << "9. Back to Main Menu \n0. Exit" << endl << endl;

	while (running) {

		cout << ">> Please enter a number: ";
		getline(cin, choices);

		if (isInteger(choices)) {

			number = stoi(choices);

			switch (number) {
			case 0:
				cout << ">> Looking forward to seeing you again soon!" << endl;
				running = false;
				break;
			case 1:
				switch (shiftOpen) {
				case true:
					cout << ">> Taking you to the menu.." << endl << endl;
					running = false;
					printingMenu();
					break;
				case false:  
					cout << ">> Sorry, we are closed. Please come again tomorrow.." << endl << endl;
					main();
					running = false;
					break;
				}
				break;
			case 2:
				switch (isStaff) {
        			case true:  
						cout << ">> Analysing order report.." << endl << endl;
						running = false;
						printOrderReport();
            			break;
					
        			case false:  
						cout << ">> Please enter a valid number!" << endl;
						break;
					}
				break;
			case 3:
				switch (isStaff) {
				case true: 
					cout << ">> Preparing shift controller.." << endl << endl;
					running = false;
					shiftController();
					break;
				case false:  
					cout << ">> Please enter a valid number!" << endl;
					break;
				}
				break;
			case 9:
				cout << ">> Backwarding to main menu.." << endl << endl;
				running = false;
				main();
				break;

			default:
				cout << ">> Please enter a valid number!" << endl;
				break;
			}
		}
		else {
			cout << ">> Please enter a valid number!" << endl;
		}
	}
}

//Remote control shift
void shiftRemote(bool shift) {
	shiftOpen = shift;
}
