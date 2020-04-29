
#include "LoadInfo.h"
#include "stdafx.h"

LoadInfo::LoadInfo(double x, double y)//function definition for intializing member variables
{
	for (int i = 0; i < MAXLOAD; i++)
	{
		LoadPower[i] = x;
		LoadCurrent[i] = y;
	}
}

LoadInfo::LoadInfo()//defualt constructor 
{
	//intentionally empty
}

char LoadInfo::search(double LoadPower[], const int MAXLOADS, double target)//function definition for search member function
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

char LoadInfo::search2(double LoadCurrent[], const int MAXLOADS, double target)//function definition for second search member function
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

string LoadInfo::getName(char result)//function definition for accessor 
{
	string out;
	out = LoadNames[result];
	return out;
}

void LoadInfo::setName(string in, int i)//function definition for mutator
{
	LoadNames[i] = in;
}
