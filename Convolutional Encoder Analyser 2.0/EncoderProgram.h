//-------------------------------------------
// Coventry University
// Computer Hardware and Software Engineering
// Programming for Engineers
//
// Paul Johannes Aru
// 14.12.2018
//-------------------------------------------



// Libraries:
#pragma once
#include<vector>
#include "EncoderData.h"
using namespace std;



class EncoderProgram {
private:
	// Attributes:
	vector<EncoderData> data ;
	// Methods:
	void trellis(ostream& output);
	string stateInBinary(int state);

public:
	// Constructor & Destructor:
	EncoderProgram(vector<int> input, int polynomial[9]);
	~EncoderProgram();
	// Methods:
	void displayTrellis();
	void saveTrellis();
};

