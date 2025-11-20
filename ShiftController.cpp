#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

void shiftRemote(bool shift);
bool isInteger(string input);

int main();

void shiftController() {
	int choice;
	string input;
	bool running = true;

	cout << setw(26) << setfill('-') << "" << setfill(' ') << endl;
	cout << "Shift Controller" << endl;
	cout << setw(26) << setfill('-') << "" << setfill(' ') << endl;
	cout << "1. Open Shift \n2. Close Shift \n\n9. Return to Main Menu" << endl << endl;

	while (running) {
		cout << ">> Enter a number: ";
		getline(cin, input);
		if (isInteger(input)) {
			choice = stoi(input);
			if (choice == 1) {
				cout << ">> Opening a shift.." << endl << endl;
				shiftRemote(true);
			}
			else if (choice == 2) {
				cout << ">> You are closing a shift.." << endl << endl;
				shiftRemote(false);
			}
			else if (choice == 9) {
				running = false;
				cout << ">> Returning to Main Menu.." << endl << endl;
				main();
				break;
			}
			else {
				cout << ">> Invalid input, please try again.." << endl;
				continue;
			}
		}
		else {
			cout << ">> Invalid input, please try again.." << endl;
			continue;
		}
	}
}