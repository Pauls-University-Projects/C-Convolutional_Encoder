//-------------------------------------------
// Coventry University
// Computer Hardware and Software Engineering
// Programming for Engineers
//
// Paul Johannes Aru
// 14.12.2018
//-------------------------------------------



// Libraries:
#include "EncoderProgram.h"
#include "EncoderData.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;



//--CONSTRUCTOR THAT STORES AND PROCESSES THE DATA--
EncoderProgram::EncoderProgram(vector<int> input, int polynomial[9]) {
	data.resize(input.size());
	int size = 0;

	for (int i = 0; i < input.size(); i++) {
		// Storing Input:
		data[i].input = input[i];
		// Storing State:
		data[i].state[0] = input[i];
		if (i >= 1) {
			data[i].state[1] = input[i - 1];
		}
		if (i >= 2) {
			data[i].state[2] = input[i - 2];
		}
		// Storing Output:
		data[i].output[0] = (polynomial[0]*data[i].state[0]) ^ (polynomial[1]*data[i].state[1]) ^ (polynomial[2]*data[i].state[2]);
		data[i].output[1] = (polynomial[3] * data[i].state[0]) ^ (polynomial[4] * data[i].state[1]) ^ (polynomial[5] * data[i].state[2]);
		data[i].output[2] = (polynomial[6] * data[i].state[0]) ^ (polynomial[7] * data[i].state[1]) ^ (polynomial[8] * data[i].state[2]);
		size++;
	}
	data.resize(size);
}



//--DESTRUCTOR--
EncoderProgram::~EncoderProgram() {
	
}



//--DISPLAY THE TRELLIS DIAGRAM IN CONSOLE--
void EncoderProgram::displayTrellis() {
	trellis(cout);
}



//--SAVE THE TRELLIS DIAGRAM TO OUTPUT.TXT--
void EncoderProgram::saveTrellis() {
	ofstream outputFile;
	outputFile.open("Output.txt");
	trellis(outputFile);
	outputFile.close();
	cout << "Trellis Diagram Saved to Output.txt in Program Folder" << endl;
}



//--UNIVERSAL TRELLIS DIAGRAM--
void EncoderProgram::trellis(ostream& output) {
	output << endl << "Trellis diagram showing the state changes:" << endl;
	int columnsLeft = data.size();
	int tableColumnLimit;

	// Loop that Limits a Single Trellis Diagram to 20 Columns or Less:
	while (columnsLeft > 0) {
		if (columnsLeft > 20) {
			tableColumnLimit = 20;
		} else {
			tableColumnLimit = columnsLeft;
		}

		// Display the Inputs:
		output << "Input ";
		if (columnsLeft == data.size()) {
			output << ": n/a";
		}
		for (int i = 0; i < tableColumnLimit; i++) {
			int currentColumn = data.size() - columnsLeft + i;
			output << ",   " << data[currentColumn].input;
		}

		// Display the Outputs:
		output << endl << "Output";
		if (columnsLeft == data.size()) {
			output << ": n/a";
		}
		for (int i = 0; i < tableColumnLimit; i++) {
			int currentColumn = data.size() - columnsLeft + i;
			output << ", ";
			output << data[currentColumn].output[0] << data[currentColumn].output[1] << data[currentColumn].output[2];
		}

		// Display the Current State Line with a Length Based on the Number of Columns:
		int width;
		if (columnsLeft == data.size()) {
			width = tableColumnLimit * 5 + 12;
		}
		else {
			width = tableColumnLimit * 5 + 7;
		}
		output << endl << left << setfill('-') << setw(width) << "Current State";
		output << endl;

		// Loop for the 8 States from 000 to 111:
		for (int referenceState = 0; referenceState < 8; referenceState++) {
			output << stateInBinary(referenceState) << "(" << referenceState << "):";
			if (columnsLeft == data.size()) {
				if (referenceState == 0) {
					output << "  x :";
				} else {
					output << "    :";
				}
			}

			// Loop for the 20 or Less Columns in a Splitted Diagram:
			for (int limitedTableColumn = 0; limitedTableColumn < tableColumnLimit; limitedTableColumn++) {
				int currentColumn = data.size() - columnsLeft + limitedTableColumn;
				int stateInDecimal = (4 * data[currentColumn].state[0]) + (2 * data[currentColumn].state[1]) + data[currentColumn].state[2];
				if (stateInDecimal == referenceState) {
					output << "  x :";
				}
				else {
					output << "    :";
				}
			}
			output << endl;
		}
		output << endl;
		// If the Trellis Diagram is longer than 20 Columns, Display Continued:
		if (tableColumnLimit != columnsLeft) {
			output << "Continued:" << endl;
		}
		columnsLeft = columnsLeft - tableColumnLimit;
	}
}

//--DECIMAL STATE VALUE IN BINARY--
string EncoderProgram::stateInBinary(int state) {
	int input = state;
	int output = 0;
	if (input > 3) {
		output = 100;
		input = input - 4;
	} 
	if (input > 1) {
		output = output + 10;
		input = input - 2;
	} 
	if (input > 0) {
		output = output + 1;
	}
	if (output > 11) {
		return std::to_string(output);
	} else if (output > 1) {
		return ("0" + std::to_string(output));
	} else {
		return ("00" + std::to_string(output));
	}
}