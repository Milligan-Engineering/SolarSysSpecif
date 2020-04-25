
#include "LoadInfo.h"
#include "stdafx.h"

char LoadInfo::search(double LoadPower[], const int MAXLOADS, double target)
{
	int index = 0;
	bool found = false;
	while ((!found) && (index < MAXLOADS))
		if (target == LoadPower[index])
			found = true;
		else
			index++;
	if (found)
		return index;
	else
		return -1;
}

char LoadInfo::search2(double LoadCurrent[], const int MAXLOADS, double target)
{
	int index = 0;
	bool found = false;
	while ((!found) && (index < MAXLOADS))
		if (target == LoadCurrent[index])
			found = true;
		else
			index++;
	if (found)
		return index;
	else
		return -1;
}

void LoadInfo::listPrint(string LoadNames[], double LoadPower[], int NumberOfLoads)
{
	cout << "\n";
	for (int i = 0; i < NumberOfLoads; i++)
	{
		cout << LoadNames[i] << " requires " << LoadPower[i] << " Watts\n";
	}
	return;
}

void LoadInfo::listPrint(string LoadNames[], double LoadCurrent[], double load, double defVoltage, int NumberOfLoads)
{
	cout << "\n";
	for (int i = 0; i < NumberOfLoads; i++)
	{
		load = LoadCurrent[i] * defVoltage;
		cout << LoadNames[i] << " requires " << load << " Watts\n";
	}
	return;
}

string LoadInfo::getName()
{
	return LoadNames[MAXLOAD];
}

void LoadInfo::setName(string in)
{
	LoadNames[MAXLOAD] = in;
}

