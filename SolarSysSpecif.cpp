
//File Name: SolarSysSpecif.cpp
//Author: Erin Forgety
//Email Address: efforgety@my.milligan.edu
//Term Project: Solar System Specifier
//Description: This program uses calculations to determine the number of solar panels needed to run a system based on user inputs.
// Added accessors and friend functions 
//Last Changed: 04/28/2020


#include <iostream>
#include <string>
#include <numeric>
#include <cmath>
#include <fstream>
#include <sstream>
#include "stdafx.h"
#include "LoadInfo.h"

using namespace std;

ifstream inStream;
ofstream outStream; 

const int MINLOADS = 1, MAXLOADS = 10, MAXVALS = 10;
int NumberOfLoads, numbIV;
double Current, totalLoad, RunTime, wattsNeeded, panelWatts, LoadDmnd, load, hours, defVoltage = 12.0, target, Latitude, Longitude, energyReq, insolation;
double Location[3][2] = { {0,1}, {2,3}, {4,5} };
string Device, Units = "Kwh/day/m^2", Local;
string InsolationVals[MAXVALS];
char aString[] = "Average Insolation", ans, answ, result;

double PowerDmnd(double totalLoad); //precondition: uses pre-defined varaible total load
//postcondition: Function returns a value of variable type double after converting the power demand from watts to kilowatts

void listPrint(string InsolationVals[], int numbIV);// precondition: uses previously-filled array of Insolation values
//postcondition: Function writes a message to the screen displaying the string stored in each array position

void getHours(double& hours);//precondition:user inputs the number of hours the system will run and confirms their input
//postcondition: Function loops through the input process until the user verfies the input is correct and returns a variable RunTime of type double

void newLine();//precondition: user inputs any character
//postcondition: Function adds a new line to the screen 

double calcEnergy(double RunTime, double LoadDmnd);//precondition: uses predefined values for run time and load demand
//postcondition: Function calculates the Energy required for the system and returns a variable of type double for energy required
double calcWatts(double insolation);


void listPrint(LoadInfo info, int NumberOfLoads);
void listPrintb(LoadInfo info, double load, double defVoltage, int NumberOfLoads);


int main()
{
	LoadInfo loads;
	LoadInfo info;

	outStream.open("outfile.dat", ios::app);
	if (outStream.fail())
	{
		cout << "Output file opening failed.\n";
		exit(1);
	}

	cout << "Welcome to the Solar System Specifier Program \n\n";
	int choice;
	do
	{
		cout << "\nWould you like to enter Insolation values or run a system analysis?\nEnter 1 for Insolation\nEnter 2 for Analysis\nPlease note that you must enter at least one Insolation value before running your first analysis\n";
		cout << "Enter integer numbers only. Any other character (a.,/ etc.) will crash the program. Please enter carefully.\n";
		cin >> choice;
		
		while ((choice != 1) && (choice != 2))
		{
			cout << "Invalid Input: ";
			cout << "Please enter either '1' or '2'\n";
			cin >> choice;
		} 

		double totalLoad = 0.0;
		switch (choice)
		{
		case 1:
			cout << "You will be entering Insolation values\n";
			cout << "Enter number of Insolation values you want to add to file. Maximum of 10 at a time.\nThis number must be an integer value. Entering any other character will crash the program.\n";
			cin >> numbIV;

			while ((numbIV < MINLOADS) || (numbIV > MAXVALS))//verifies that the number is within the given range
			{
				cout << "Number must be between " << MINLOADS << " and " << MAXVALS << " . Please enter number again.\n";
				cin >> numbIV;
			}
			cout << "You will be entering " << numbIV << " Insolation values. Please enter numerical values only.\n";// Echoes number
			
			for (int m = 0; m < numbIV; m++)
			{
				cout << "\nEnter Insolation value " << m + 1 << " : ";
				cin >> InsolationVals[m];
			}
			for (int k = 0; k < numbIV; k++)
			{

				outStream << aString << " : " << InsolationVals[k] << endl; //Outputs array to txtFile
			}
			listPrint(InsolationVals, numbIV);//echoes insolation

			for (int i = 0; i < 3; i++) 
			{
				for (int j = 0; j < 2; j++)
				{
					cout << "Location " << i << " at Latitude x[" << i 	<< "][ and Longitude " << j << "]: ";
					cout << Location[i][j] << endl;
				}
			}

		case 2:
			cout << "You will be running a system analysis\n";

			inStream.open("outfile.dat");
			if (inStream.fail())
			{
				cout << "Input file opening failed.\n";
				exit(1);
			}
			inStream >> aString;
			inStream >> InsolationVals[0];
			cout << aString << " : " << InsolationVals[0] << " " << Units << "\n";//echoes insonolation
			
			insolation = stod(InsolationVals[0]);


			// Retrieve and validate number of loads using a while
			cout << "How many loads will you be powering?\nThis number must be an integer. Entering any other character will crash the program.\n";
			cin >> NumberOfLoads;

			while ((NumberOfLoads < MINLOADS) || (NumberOfLoads > MAXLOADS))//verifies that the number of loads is within the given range
			{
				cout << "Number of loads must be between " << MINLOADS << " and " << MAXLOADS << " loads. Please enter number again.\n";
				cin >> NumberOfLoads;
			}
			cout << "You will be powering " << NumberOfLoads << " loads.\n";// Echoes number of loads

			for (int i = 0; i < NumberOfLoads; i++)
			{
				cout << "\nEnter name of Load " << i + 1 << " : ";
				// Need to use mutator here
				string tempStr;
				cin >> tempStr;
				loads.setName(tempStr);
	
			}
			int choice;
			do
			{
				cout << "\nWill you be entering Load demands in Watts or Amps?\nEnter 1 for Watts\nEnter 2 for Amps\n";
				cout << "Enter integer numbers only. Any other character (.,/ etc.) will crash the program. Please enter carefully.\n";
				cin >> choice;
				do
				{
					cout << "Invalid Input: ";
					cout << "Please enter either '1' or '2'\n";
					cin >> choice;
				}while ((choice != 1) && (choice != 2));

				double totalLoad = 0.0;
				switch (choice)
				{
				case 1:
					cout << "You will be entering Loads in Watts. Please enter numerical values only.\n";

					for (int j = 0; j < NumberOfLoads; j++)
					{
						cout << "\nEnter power demand of Load " << j + 1 << " : ";
						cin >> loads.LoadPower[j];
						totalLoad += loads.LoadPower[j];
					}

					cout << "\nWould you like to check the array you filled for a target value?\nType 'y' for yes or 'n' for no\n";
					cin >> ans;
					do
					{
						cout << "Enter the power value you want to search for\n";
						cin >> target;
						result = loads.search(loads.LoadPower, MAXLOADS, target);
						if (result == -1)
						{
							cout << target << " is not stored in the array\n";
						}
						else
						{
							string tempStrb;
							tempStrb = loads.getName(result);
							cout << target << " is stored in array position " << tempStrb << endl << "\n";	
						}

						cout << "Would you like to search again? Type y/n\n";
						cin >> answ;

					} while ((answ != 'n') && (answ != 'N')); 

					listPrint(info, NumberOfLoads);
					cout << "\nThe total load is " << totalLoad << " watts";
					LoadDmnd = PowerDmnd(totalLoad);
					cout << "\nThe total power demand of your loads is " << LoadDmnd << " Kw\n";
					outStream << LoadDmnd;
					break;


				case 2:
					cout << "You will be entering Loads in Amps. Please enter numerical values only\n";

					for (int k = 0; k < NumberOfLoads; k++)
					{
						cout << "\nEnter current demand of Load " << k + 1 << " : ";
						cin >> loads.LoadCurrent[k];
						totalLoad += loads.LoadCurrent[k];
					}

					cout << "\nWould you like to check the array you filled for a target value?\nType 'y' for yes or 'n' for no\n";
					cin >> ans;
					do
					{
						cout << "Enter the current value you want to search for\n";
						cin >> target;
						result = loads.search2(loads.LoadCurrent, MAXLOADS, target);
						if (result == -1)
						{
							cout << target << " is not stored in the array\n";
						}
						else
						{
							cout << target << " is stored in array position " << loads.getName(result) << endl << "\n";
						}
						cout << "Would you like to search again? Type y/n\n";
						cin >> answ;

					} while ((answ != 'n') && (answ != 'N'));

					listPrintb(info, load, defVoltage, NumberOfLoads);
			
					totalLoad = totalLoad * defVoltage;
					cout << "\nThe total load is " << totalLoad << " watts";
					LoadDmnd = PowerDmnd(totalLoad);
					cout << "\nThe total power demand of your loads is " << LoadDmnd << " Kw\n";
					outStream << LoadDmnd;
					break;

				}
			} while (choice < 1);


			getHours(RunTime);//gets and verifies user input for system run time

			energyReq = calcEnergy(RunTime, LoadDmnd);//calculates energy required to power system and places value in variable energyReq
			wattsNeeded = calcWatts(insolation);//calculates required wattage to run system and places value in variable wattsNeeded 
			
			cout << "\nThe Energy required to run the system for " << RunTime << " hours is " << energyReq << " Kwh/day\n";
			cout << "\nThe required power supplied to run your system is " << wattsNeeded << " W\n";
			
			cout << "\nWhat rating (Watts) Solar Panels will you be using to power your loads?\nPlease enter a numeric value only\n";
			cin >> panelWatts;

			double numbPanels;//declares variable for number of panels
			numbPanels = wattsNeeded / panelWatts;//calculates the number of panels required to power the system
			cout << "\nYou will need " << ceil(numbPanels) << " solar panels to power your loads\n";
			//ceiling function rounds number of panels to the nearest whole number
			break;
			
		}
	} while (choice < 1);

		//close file stream
		inStream.close();
		outStream.close();

		cout << "\nThank you for using the Solar System Specifier Program! Press any key to exit.";
	return 0;
}


double PowerDmnd(double totalLoad)//function definition for conversion calculation of the total load
{
	const double conv = 1000.0;
	double convert;
	convert = totalLoad / conv;
	return convert;
}


void listPrint(string InsolationVals[], int numbIV)//function definition for printing insolation values
{
	for (int i = 0; i < NumberOfLoads; i++)
	{
		cout << "\nAverage Insolation " << i + 1 << " is " << InsolationVals[i] << Units << "\n\n";
	}
	return;
}

void newLine()
{
	char symbol;
	do
	{
		cin.get(symbol);
	} while (symbol != '\n');
}

void getHours(double& hours)
{
	char ans;
	do
	{
		cout << "Enter number of hours the system will run per day\n";
		cin >> hours;
		cout << "You entered " << hours
			<< ". Is that correct? (yes/no): \n";
		cin >> ans;
		newLine();
	} while ((ans != 'Y') && (ans != 'y'));
}

string printNames(string LoadNames[], char result)
{
	return LoadNames[result];
}

double calcEnergy(double RunTime, double LoadDmnd)
{
	double Energy = 0.0;
	const double conv = 1000.0;

	Energy = RunTime * LoadDmnd; //Calculates the neccessary energy that needs to be generated by the solar panels.
	return Energy;
}

double calcWatts(double insolation)
{
	double Energy = 0.0;
	const double conv = 1000.0;
	double watts;

	Energy = calcEnergy(RunTime, LoadDmnd);
	watts = (Energy / insolation) * conv; //Determines total Watts needed to generate enough energy for the system.
	return watts;
}

void listPrint(LoadInfo info, int NumberOfLoads)
{
	cout << "\n";
	for (int i = 0; i < NumberOfLoads; i++)
	{
		cout << info.LoadNames[i] << " requires " << info.LoadPower[i] << " Watts\n";
	}
	return;
}

void listPrintb(LoadInfo info, double load, double defVoltage, int NumberOfLoads)
{
	cout << "\n";
	for (int i = 0; i < NumberOfLoads; i++)
	{
		load = info.LoadCurrent[i] * defVoltage;
		cout << info.LoadNames[i] << " requires " << load << " Watts\n";
	}
	return;
}
