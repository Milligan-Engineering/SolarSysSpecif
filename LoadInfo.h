#pragma once
#include "stdafx.h"

class LoadInfo
{
private:

	string LoadNames[MAXLOAD];

public:

	char search(double LoadPower[], const int MAXLOAD, double target);//precondition: user enters a variable of type double
	//postcondition: function returns a character "-1" if target not found and a character displaying the corresponding array position if found
	
	char search2(double LoadCurrent[], const int MAXLOAD, double target);//precondition: user enters a variable of type double
	//postcondition: function returns a character "-1" if target not found and a character displaying the corresponding array position if found
	
	string getName(char result);//precondition: accessor function searches private member variable LoadNames
	//postcondition: function returns a string containg the desired array variable of the private member variable LoadNames

	string getName(int i);//precondition: accessor function searches private member variable LoadNames
	//postcondition: function returns a string containg the desired array variable of the private member variable LoadNames

	void setName(string in, int i);//precondition: mutator function takes user inputted strings
	//postcondition: function places input strings in corresponding array positions of private member variable LoadNames

	void listPrint(string name, double LoadPower[], int numbLoads);//precondtion: declared member variables 
	//postcondition: Prints load names and powers

	void listPrint(string name, double LoadCurrent[], double load, double defVoltage, int numbLoads);//precondtion: declared member variables 
	//postcondition: Prints load names and powers


	//member variables:
	double LoadPower[MAXLOAD] = { 0,0,0,0,0,0,0,0,0,0 };
	double LoadCurrent[MAXLOAD] = { 0,0,0,0,0,0,0,0,0,0 };

};

