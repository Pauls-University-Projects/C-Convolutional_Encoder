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



class EncoderData {
private:

public:
	int input;
	int state[3] = { 0,0,0 };
	int output[3];
	EncoderData();
	~EncoderData();
};

