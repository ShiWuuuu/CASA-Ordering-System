#include <iostream>
#include <string>
using namespace std;

void printReceipt(char orderList[100][4][25], int orderCount, double subtotal, double totalPrice, double roundedPrice, string paymentType, double amountPaid);
void feedback();
bool isInteger(string input);
bool isDouble(string input);

void paymentMethod(double price, char orderList[100][4][25], int orderCount, double subtotal, double totalPrice, double roundedPrice, string paymentType, double amountPaid) {
	bool running = true;
	int method;
	string input;
	double cash = 0;

	cout << ">> Please complete your payment using any of the available methods listed below." << endl;
	cout << "1. Cash \n2. e-Wallet" << endl << endl;
	while (running) {
		cout << ">> Please select your payment method: ";
		getline(cin, input);

		if (isInteger(input)) {
			method = stoi(input);
			switch (method) {
			case 1:
				paymentType = "Cash";
				running = false;
				while (true) {
					cout << ">> Please enter amount of cash: RM";
					cin >> input;
					if(isDouble(input)){
						cash = stod(input);
						if (cash >= price) {
							amountPaid = cash;
							cout << ">> Successfully paid with cash." << endl;
							break;
						}
						else {
							cout << ">> Insufficient amount or input, please re-enter again." << endl;
						}
					}
					else {
						cout << ">> Invalid input, please try again.." << endl;
						continue;
					}
				}
				break;
			case 2:
				running = false;
				paymentType = "e-Wallet";
				amountPaid = price;
				cout << ">> Payment processing.." << endl;
				cout << ">> Successfully paid with e-Wallet." << endl;
				break;
			default:
				cout << ">> Invalid input, please try again.." << endl;
				break;
			}
		}
		else {
			cout << ">> Invalid payment method selected, please try again." << endl;
			continue;
		}
	}
	printReceipt(orderList, orderCount, subtotal, totalPrice, roundedPrice, paymentType, amountPaid);
	feedback();
	return;
}