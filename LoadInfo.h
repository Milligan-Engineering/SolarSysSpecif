#pragma once
#include "stdafx.h"

class LoadInfo
{
private:

	string LoadNames[MAXLOAD];

public:

	char search(double LoadPower[], const int MAXLOAD, double target);
	char search2(double LoadCurrent[], const int MAXLOAD, double target);
	//void listPrint(string LoadNames[], double LoadPower[], int NumberOfLoads);
	//void listPrintb(string LoadNames[], double LoadCurrent[], double load, double defVoltage, int NumberOfLoads);
	string getName(char result);
	void setName(string in, int i);

	friend void listPrint(LoadInfo info, int NumberOfLoads);
	friend void listPrintb(LoadInfo info, double load, double defVoltage, int NumberOfLoads);

	double LoadPower[MAXLOAD] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	double LoadCurrent[MAXLOAD] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

};

