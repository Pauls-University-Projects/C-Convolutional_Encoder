//-------------------------------------------
// Coventry University
// Computer Hardware and Software Engineering
// Programming for Engineers
//
// Paul Johannes Aru
// 14.12.2018
//-------------------------------------------



// Libraries:
#include <iostream>
#include <thread>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
#include "EncoderProgram.h"

//Main Functions:
void launchScreen();
void displayInput();
void displayError(string message);
void setACustomPolynomial();
//Main Variables:
vector<int> binaryInput;
int polynomial[9] = { 0, 1, 1, 0, 0, 1, 0, 1, 0 };



int main() {
	launchScreen();
	bool repeat = true;

	//--MAIN LOOP--
	while (repeat == true) {

		//-POLYNOMIAL INPUT-
		cout << "Would You Like to Use a Custom Polynomial? (Y)/(N)" << endl;
		string polynomialChoice;
		cin >> polynomialChoice;
		while (!(polynomialChoice == "Y" || polynomialChoice == "y" || polynomialChoice == "yes" || polynomialChoice == "Yes" || polynomialChoice == "YES" || polynomialChoice == "N" || polynomialChoice == "n" || polynomialChoice == "no" || polynomialChoice == "No" || polynomialChoice == "NO")) {
			cout << "Please Type Either Yes or No." << endl;
			cin >> polynomialChoice;
		}
		if (polynomialChoice == "Y" || polynomialChoice == "y" || polynomialChoice == "yes" || polynomialChoice == "Yes" || polynomialChoice == "YES") {
			setACustomPolynomial();
		} else {
			cout << "Generator Polynomial, Based on my Student ID:" << endl;
		}
		cout << "Output A = (" << polynomial[0] << polynomial[1] << polynomial[2];
		cout << "), Output B = (" << polynomial[3] << polynomial[4] << polynomial[5];
		cout << "), Output C = (" << polynomial[6] << polynomial[7] << polynomial[8] << ")" << endl << endl;

		// Prompt User for Input Type:
		cout << "Would you like to input the binary sequence from Input.txt file or type it in here?" << endl;
		cout << "1 - Input.txt" << endl;
		cout << "2 - Type" << endl;
		// N.B. This is a String Instead of an int to Avoid Issues with Incorrect Input
		string inputChoice = "0";
		cin >> inputChoice;
		cout << endl;
		while (!(inputChoice == "1" || inputChoice == "2")) {
			cout << "Please enter 1 or 2 to indicate your choice!" << endl;
			cin >> inputChoice;
			cout << endl;
		}

		//-FILE INPUT-
		if (inputChoice == "1") {
			ifstream textFile;
			textFile.open("Input.txt");

			if (textFile.good()) {
				char currentCharacter = ' ';
				char previousCharacter = ';';
				int currentInteger = 0;
				int size = 0;

				textFile >> currentCharacter;
				while (!textFile.fail() && previousCharacter == ';' || !textFile.fail() && currentCharacter == ';') {
					currentInteger = currentCharacter - '0';
					// A bit followed by a ';' gets added to the vector:
					if (previousCharacter == ';' && currentInteger == 0 || previousCharacter == ';' && currentInteger == 1) {
						binaryInput.push_back(currentInteger);
						size++;
					}
					// If the file does not start with a bit throw an error:
					if (size == 0) {
						displayError("Input.txt format is corrupt.");
					}
					previousCharacter = currentCharacter;
					textFile >> currentCharacter;
				}
				displayInput();

			} else {
				displayError("Input.txt not found.");
			}
		}

		//-TYPE INPUT-
		else if (inputChoice == "2") {
			string typeInput;
			string currentString;
			int currentInteger = 0;

			cout << "Enter your Binary Input Sequence: ";
			cin >> typeInput;

			// Converting one character at a time to bit:
			for (int i = 0; i < typeInput.size(); i++) {
				currentString = typeInput.substr(i, 1);
				if (currentString == "0" || currentString == "1") {
					currentInteger = stoi(currentString);
					binaryInput.push_back(currentInteger);
				} else {
					displayError(currentString +" is not Binary. Please Only Enter 1's and 0's.");
				}
			}
			displayInput();
		}

		//-Passing Input to EncoderProgram-
		EncoderProgram UserData(binaryInput, polynomial);

		//-Displaying Output-
		UserData.displayTrellis();

		//-Check Whether User Would Like to Save Output-
		string saveQuestion;
		cout << "Would You Like to Save the Trellis Diagram to Output.txt? (Y)/(N)" << endl;
		cin >> saveQuestion;
		while (!(saveQuestion == "Y" || saveQuestion == "y" || saveQuestion == "yes" || saveQuestion == "Yes" || saveQuestion == "YES" || saveQuestion == "N" || saveQuestion == "n" || saveQuestion == "no" || saveQuestion == "No" || saveQuestion == "NO")) {
			cout << "Please Type Either Yes or No." << endl;
			cin >> saveQuestion;
		}
		if (saveQuestion == "Y" || saveQuestion == "y" || saveQuestion == "yes" || saveQuestion == "Yes" || saveQuestion == "YES") {
			UserData.saveTrellis();
		}
		cout << endl;

		//-Check Whether User Would Like to Re-Run Program-
		string runQuestion;
		cout << "Would You Like to Re-Run the Program? (Y)/(N)" << endl;
		cin >> runQuestion;
		while (!(runQuestion == "Y" || runQuestion == "y" || runQuestion == "yes" || runQuestion == "Yes" || runQuestion == "YES" || runQuestion == "N" || runQuestion == "n" || runQuestion == "no" || runQuestion == "No" || runQuestion == "NO")) {
			cout << "Please Type Either Yes or No." << endl;
			cin >> runQuestion;
		}
		if (runQuestion == "Y" || runQuestion == "y" || runQuestion == "yes" || runQuestion == "Yes" || runQuestion == "YES") {
			binaryInput = { };
			repeat = true;
			// Exit message:
		} else {
			// As console uses a different codepage, 'ä' = '„':
			cout << "N„gemist! :)";
			repeat = false;
		}
		cout << endl;
	}
	return 0;
}



//--OUTPUTS BINARYINPUT VECTOR--
void displayInput() {
	cout << "Your Input: ";
	for (int i = 0; i < binaryInput.size(); i++) {
		cout << binaryInput[i];
	}
	cout << endl;
}



//--OUTPUTS ERROR MESSAGES--
void displayError(string message) {
	cout << "########################################################################" << endl;
	cout << "Error: " << message << endl;
	cout << "The Program Will Attempt to Continue." << endl;
	cout << "########################################################################" << endl;
}

//--CUSTOM POLYNOMIAL INPUT--
void setACustomPolynomial() {
	string typeInput;
	string currentString;
	int currentInteger = 0;

	// Loop that covers all 3 outputs:
	for (int output = 0; output < 9; output=output+3) {
		cout << "Enter Your Custom 3-Bit Value for Output ";
		switch (output) {
			case 0: cout << "A:" << endl;
				break;
			case 3: cout << "B:" << endl;
				break;
			case 6: cout << "C:" << endl;
				break;
		}

		// Input and Verification:
		cin >> typeInput;
		while (typeInput.size() != 3) {
			cout << "Please Only Type 3 Digits." << endl;
			cin >> typeInput;
		}

		// Converting one character at a time to bit:
		for (int i = 0; i < 3; i++) {
			currentString = typeInput.substr(i, 1);
			if (currentString == "0" || currentString == "1") {
				currentInteger = stoi(currentString);
				polynomial[output+i] = currentInteger;
			} else {
				displayError(currentString + " is not Binary. Please Only Enter 1's and 0's.");
			}
		}
	}
}



//--START-UP SCREEN--
void launchScreen() {

	cout << "   ____                      _       _   _                   _ " << endl;
	cout << "  / ___|___  _ ____   _____ | |_   _| |_(_) ___  _ __   __ _| |" << endl;
	cout << " | |   / _ \\| '_ \\ \\ / / _ \\| | | | | __| |/ _ \\| '_ \\ / _` | |" << endl;
	cout << " | |__| (_) | | | \\ V / (_) | | |_| | |_| | (_) | | | | (_| | |" << endl;
	cout << "  \\____\\___/|_| |_|\\_/ \\___/|_|\\__,_|\\__|_|\\___/|_| |_|\\__,_|_|" << endl << endl;
	cout << "  _____                     _           " << endl;
	cout << " | ____|_ __   ___ ___   __| | ___ _ __ " << endl;
	cout << " |  _| | '_ \\ / __/ _ \\ / _` |/ _ \\ '__|" << endl;
	cout << " | |___| | | | (_| (_) | (_| |  __/ |   " << endl;
	cout << " |_____|_| |_|\\___\\___/ \\__,_|\\___|_|   " << endl << endl << endl;
	cout << "Coventry University" << endl;
	cout << "Computer Hardware and Software Engineering" << endl;
	cout << "Programming for Engineers Coursework" << endl << endl;
	cout << "Paul Johannes Aru" << endl;
	cout << "Student ID: 7155312" << endl;
	cout << "December, 2018" << endl << endl << endl;
	for (int i = 0; i < 10; i++) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		cout << "	.";
	}
	for (int i = 0; i < 100; i++) {
		cout << endl;
	}

}