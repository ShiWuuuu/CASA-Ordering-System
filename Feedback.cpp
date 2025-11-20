#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int totalStars = 0;
int feedbackCounts = 0;
double rating = 0;

void feedback();
void feedbackCalculating(int stars);
void feedbackPrint(double rating);
bool isInteger(string input);
int main();


void feedback() {
	int stars;
	string input;
	bool running = true;
	string comments;
	cout << ">> Thank you for your order(s)." << endl;

	while (running) {
		cout << ">> Please rate your ordering experience from 1 to 5 stars: ";
		cin >> input;

		if (isInteger(input)) {
			stars = stoi(input);

			switch (stars) {
			case 1:
				cout << endl << ">> Rating: 1 star - We're sorry to hear you had a bad experience." << endl;
				running = false;
				break;
			case 2:
				cout << endl << ">> Rating: 2 stars - We appreciate your feedback and we will work to improve." << endl;
				running = false;
				break;
			case 3:
				cout << endl << ">> Rating: 3 stars - Thank you for your feedback. We will aim to do better." << endl;
				running = false;
				break;
			case 4:
				cout << endl << ">> Rating: 4 stars - We are glad you had a good experience!" << endl;
				running = false;
				break;
			case 5:
				cout << endl << ">> Rating: 5 stars - Thank you for the excellent feedback!" << endl;
				running = false;
				break;
			default:
				cout << ">> Invalid input, please enter again.." << endl;
			}
		}
		else {
			cout << ">> Invalid input, please enter again.." << endl;
		}
	}

	// Clear the input buffer before getline
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

	//Feedback with comments
	cout << ">> Any suggestions/complains?" << endl;
	cout << ">> ";

	getline(cin, comments);

	cout << ">> Submitted comments: " << comments << endl << endl;

	ofstream feedbackFile("feedback.txt", ios::app);
	if (feedbackFile.is_open()) {
		feedbackFile << "Comments: " << comments << "\n\n";
		feedbackFile.close();
		cout << ">> Thank you for your valuable feedback!\n>> Your feedback has been saved." << endl;
	}
	else {
		cerr << ">> Error: Could not open the file." << endl;
	}

	feedbackCalculating(stars);

}
void feedbackCalculating(int stars) {
	totalStars += stars;
	feedbackCounts += 1;

	if (feedbackCounts > 0) {
		rating = static_cast<double>(totalStars) / feedbackCounts;
	}
	cout << endl << ">> Rating average: " << rating << " star(s) with " << feedbackCounts << " feedback(s)." << endl;
	feedbackPrint(rating);
	main();
}