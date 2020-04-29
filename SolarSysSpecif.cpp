
//File Name: SolarSysSpecif.cpp
//Author: Erin Forgety
//Email Address: efforgety@my.milligan.edu
//Term Project: Solar System Specifier
//Description: This program uses calculations to determine the number of solar panels needed to run a system based on user inputs.
//Fixed listPrint
//Last Changed: 04/28/2020


#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include "stdafx.h"
#include "LoadInfo.h"

using namespace std;

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

double calcWatts(double insolation);//precondition: uses predfined value for insolation and calls function calcEnergy 
//postcondition: Function calculates the Wattage required to power the system and returns a variable of typ double for watts needed


//declare variables
const int MINLOADS = 1, MAXLOADS = 10, MAXVALS = 100;
const double defVoltage = 12.0;
int numbLoads, numbIV;
double Current, RunTime, LoadDmnd, Latitude, Longitude;
double totalLoad, energyReq, wattsNeeded, panelWatts, load, hours, insolation, target;
double Location[3][2] = { {0,1}, {2,3}, {4,5} };
string Device, Local, name, Units = "Kwh/day/m^2";
string InsolationVals[MAXVALS];
char ans, answ, result, aString[] = "AverageInsolation";


//declare file streams
ifstream inStream;
ofstream outStream;



int main()
{
	//declare class object
	LoadInfo loads;

	outStream.open("outfile.dat", ios::app);//opens output file
	if (outStream.fail())//exits program if output file opening fails
	{
		cout << "Output file opening failed.\n";
		exit(1);
	}


	cout << "Welcome to the Solar System Specifier Program \n\n";
	int choice;

	//implements a swticth menu
	do
	{
		cout << "\nWould you like to enter Insolation values or run a system analysis?\nEnter 1 for Insolation\nEnter 2 for Analysis"
			<< "\nPlease note that you must enter at least one Insolation value before running your first analysis\n"
			<< "\nEnter integer numbers only. Any other character (a.,/ etc.) will crash the program. Please enter carefully.\n";
		cin >> choice;
		
		while ((choice != 1) && (choice != 2))//validates choice input
		{
			cout << "Invalid Input: ";
			cout << "Please enter either '1' or '2'\n";
			cin >> choice;
		} 

		double totalLoad = 0.0;

		switch (choice)//switches between entering Insolation values and running a system analyses
		{
		case 1:
			cout << "You will be entering Insolation values\n";
			cout << "Enter number of Insolation values you want to add to file. Maximum of 10 at a time."
				<< "\nThis number must be an integer value. Entering any other character will crash the program.\n";
			cin >> numbIV;

			//verifies that the number is within the given range
			while ((numbIV < MINLOADS) || (numbIV > MAXVALS))
			{
				cout << "Number must be between " << MINLOADS << " and " << MAXVALS << " . Please enter number again.\n";
				cin >> numbIV;
			}

			cout << "You will be entering " << numbIV << " Insolation values."
				<< "\nPlease enter numerical values only.\n";// Echoes number of values
			
			//retrieves user input of insolation values
			for (int m = 0; m < numbIV; m++)
			{
				cout << "\nEnter Insolation value " << m + 1 << " : ";
				cin >> InsolationVals[m];
			}

			//sends user input to output file
			for (int k = 0; k < numbIV; k++)
			{
				outStream << aString << " " << InsolationVals[k] << endl; //Outputs array to txtFile
			}

			listPrint(InsolationVals, numbIV);//prints Insolation values

			cout << "\nHere is a multidimensional array of system locations\n";

			//Prints multidimensional array of locations
			for (int i = 0; i < 3; i++) 
			{
				for (int j = 0; j < 2; j++)
				{
					cout << "Location " << i << " at Latitude x[" << i 	<< "] and Longitude [" << j << "]: ";
					cout << Location[i][j] << endl;
				}
			}
			
			//end of entering Insolation values
			break;

		case 2:
			cout << "\nYou will be running a system analysis\n";


			inStream.open("outfile.dat");//opens input file
			if (inStream.fail())//exits program is input file opening fails
			{
				cout << "Input file opening failed.\n";
				exit(1);
			}

			//reads Insolation value from file 
			inStream >> aString;
			inStream >> InsolationVals[0];
			cout << aString << " : " << InsolationVals[0] << " " << Units << "\n";//prints Insolation value retrieved from file 
			
			insolation = stod(InsolationVals[0]);//converts file input from string to double

			// Retrieves number of loads
			cout << "How many loads will you be powering?\nThis number must be an integer."
				<< "Entering any other character will crash the program.\n";
			cin >> numbLoads;

			//Validates that the input lies within the given range
			while ((numbLoads < MINLOADS) || (numbLoads > MAXLOADS))//verifies that the number of loads is within the given range
			{
				cout << "Number of loads must be between " << MINLOADS << " and " << MAXLOADS << " loads. Please enter number again.\n";
				cin >> numbLoads;
			}

			cout << "You will be powering " << numbLoads << " loads.\n";// Echoes number of loads

			//Retrieves names of loads and stores them in the class LoadInfo
			for (int i = 0; i < numbLoads; i++)
			{
				cout << "\nEnter name of Load " << i + 1 << " : ";
				string tempStr;
				cin >> tempStr;
				loads.setName(tempStr, i);//mutator function required to send names to the private member LoadNames in the class LoadInfo
			}


			int choice;

			//implements a new switch menu
			do
			{
				cout << "\nWill you be entering Load demands in Watts or Amps?\nEnter 1 for Watts\nEnter 2 for Amps\n"
					<< "Enter integer numbers only. Any other character (.,/ etc.) will crash the program."
					<< "\nPlease enter carefully.\n";
				cin >> choice;

				//validates choice input 
				while ((choice != 1) && (choice != 2))
				{
					cout << "Invalid Input: ";
					cout << "Please enter either '1' or '2'\n";
					cin >> choice;
				}

				double totalLoad = 0.0;

				switch (choice)// swithces between power-entry and current-entry system anaysis 
				{
				case 1:
					cout << "You will be entering Loads in Watts. Please enter numerical values only.\n";

					//retrives power values for each load and stores them in the class LoadInfo
					for (int j = 0; j < numbLoads; j++)
					{
						cout << "\nEnter power demand of Load " << j + 1 << " : ";
						cin >> loads.LoadPower[j];
						totalLoad += loads.LoadPower[j];//sums the loads in the array to get a value for the total load
					}

					cout << "\nWould you like to check the array you filled for a target value?\nType 'y' for yes or 'n' for no\n";
					cin >> ans;

					//checks array for user specified value
					while ((ans != 'n') && (ans != 'N'))
					{
						cout << "Enter the power value you want to search for\n";
						cin >> target;

						result = loads.search(loads.LoadPower, MAXLOADS, target);//calls member function to search member variable LoadPower
						if (result == -1)
						{
							cout << target << " is not stored in the array\n";
						}
						else
						{
							string tempStrb;
							tempStrb = loads.getName(result);//function accesses private member variable LoadNames and stores name in temporary string
							cout << target << " is stored in array position " << tempStrb << endl << "\n";	
						}

						cout << "Would you like to search again? Type y/n\n\n";
						cin >> ans;

					}  
		
					loads.listPrint(name, loads.LoadPower, numbLoads);//calls function to print load names and powers
					
					cout << "\nThe total load is " << totalLoad << " watts";

					LoadDmnd = PowerDmnd(totalLoad);//calls function to convert power demand

					cout << "\nThe total power demand of your loads is " << LoadDmnd << " Kw\n";

					break;


				case 2:
					cout << "You will be entering Loads in Amps. Please enter numerical values only\n";

					//retrieves current values and places them in their member variable
					for (int k = 0; k < numbLoads; k++)
					{
						cout << "\nEnter current demand of Load " << k + 1 << " : ";
						cin >> loads.LoadCurrent[k];
						totalLoad += loads.LoadCurrent[k];//sums currents in array to get a value for the total current
					}

					cout << "\nWould you like to check the array you filled for a target value?\nType 'y' for yes or 'n' for no\n";
					cin >> ans;

					//searches array for a user specified value
					while ((ans != 'n') && (ans != 'N'))
					{
						cout << "Enter the current value you want to search for\n";
						cin >> target;
						result = loads.search2(loads.LoadCurrent, MAXLOADS, target);//calls member function to perform seach
						if (result == -1)
						{
							cout << target << " is not stored in the array\n";
						}
						else
						{
							string name;
							name = loads.getName(result);//accesses private member variable LoadNames
							cout << target << " is stored in array position " << name << endl << "\n";
						}
						cout << "Would you like to search again? Type y/n\n\n";
						cin >> ans;

					} 

					loads.listPrint(name, loads.LoadCurrent, load, defVoltage, numbLoads);//calls function to print load names and powers
			
					totalLoad = totalLoad * defVoltage;//calculates load by multiplying total current by default volatage
					cout << "\nThe total load is " << totalLoad << " watts";

					LoadDmnd = PowerDmnd(totalLoad);//calls function to convert to Kw and stores value in LoadDmnd

					cout << "\nThe total power demand of your loads is " << LoadDmnd << " Kw\n";
			
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

		cout << "\nThank you for using the Solar System Specifier Program!";
	return 0;
}
//end of main




//function definitions:
double PowerDmnd(double totalLoad)//function definition for conversion calculation of the total load
{
	const double conv = 1000.0;
	double convert;
	convert = totalLoad / conv;//converts from Watts to Kilowatts 
	return convert;
}

void listPrint(string InsolationVals[], int numbIV)//function definition for printing insolation values
{
	for (int i = 0; i < numbLoads; i++)
	{
		cout << "\nAverage Insolation " << i + 1 << " is " << InsolationVals[i] << Units << "\n\n";
	}
	return;
}

void newLine()//function definition for printing a new line
{
	char symbol;
	do
	{
		cin.get(symbol);
	} while (symbol != '\n');
}

void getHours(double& hours)//function definition for retrieving and validating number of hours
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

double calcEnergy(double RunTime, double LoadDmnd)//function definition for calculating energy
{
	double Energy = 0.0;
	const double conv = 1000.0;

	Energy = RunTime * LoadDmnd; //Calculates the neccessary energy that needs to be generated by the solar panels.
	return Energy;
}

double calcWatts(double insolation)//function definition for calculating watts 
{
	double Energy = 0.0;
	const double conv = 1000.0;
	double watts;

	Energy = calcEnergy(RunTime, LoadDmnd);//calls function that calculates the energy required and sets that value equal to a new variable
	watts = (Energy / insolation) * conv; //calculates needed power in KW and uses a conversion factor to get power in Watts
	return watts;
}
