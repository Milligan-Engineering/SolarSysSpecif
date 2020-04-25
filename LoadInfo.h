#pragma once
#include "stdafx.h"

class LoadInfo
{
public:

	char search(double LoadPower[], const int MAXLOAD, double target);
	char search2(double LoadCurrent[], const int MAXLOAD, double target);
	void listPrint(string LoadNames[], double LoadPower[], int NumberOfLoads);
	void listPrint(string LoadNames[], double LoadCurrent[], double load, double defVoltage, int NumberOfLoads);
	string getName();
	void setName(string in);

	double LoadPower[MAXLOAD] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	double LoadCurrent[MAXLOAD] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

private:

	string LoadNames[MAXLOAD];

};

