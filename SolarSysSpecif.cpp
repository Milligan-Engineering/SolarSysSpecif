
//File Name: SolarSysSpecif.cpp
//Author: Erin Forgety
//Email Address: efforgety@my.milligan.edu
//Term Project
//Description: This program uses calculations to determine the number of solar panels needed to run a system based on user inputs.
// Added functions to read and write from a file 
//Last Changed: 03/06/2020


#include <iostream>
#include <string>
#include <numeric>
#include <cmath>
#include <fstream>
using namespace std;
ifstream inStream;
ofstream outStream; 

const int MINLOADS = 1, MAXLOADS = 5, MAXVALS = 10;
const double conv = 1000.0;
double AvgInsonolation, Energy = 0.0, Current, totalLoad, numbPanels, RunTime, WattsNeeded, panelWatts, LoadDmnd, load, defVoltage = 12.0;
int NumberOfLoads, numbIV;

double LoadPower[MAXLOADS], LoadCurrent[MAXLOADS];

double PowerDmnd(double totalLoad);

string Device, Units = "Kwh/day/m^2";
string LoadNames[MAXLOADS], InsolationVals[MAXVALS];

double PowerDmnd(double totalLoad); //precondition: user inputs total load
//postcondition: Function returns a value of variable type double after converting the power demand from watts to kilowatts

void listPrint(string LoadNames[], double LoadPower[], int NumberOfLoads);
void listPrint(string LoadNames[], double LoadCurrent[], double load, double defVoltage, int NumberOfLoads);
void listPrint(string InsolationVals[], int numbIV);

int main()
{
	
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
		cin >> choice;

		double totalLoad = 0.0;
		switch (choice)
		{
		case 1:
			cout << "You will be entering Insolation values\n";
			cout << "Enter number of Insolation values you want to add to file. Maximum of 10 at a time.";
			cin >> numbIV;
			for (int m = 0; m < numbIV; m++)
			{
				cout << "\nEnter Insolation value " << m + 1 << " : ";
				cin >> InsolationVals[m];
			}
			for (int k = 0; k < numbIV; k++)
			{
				outStream << "Insolation :" << InsolationVals[k] << endl; //Outputs array to txtFile
			}
			listPrint(InsolationVals, numbIV);//echoes insolation
			break;

		case 2:
			cout << "You will be running a system analysis\n";
// The problem is that the program is looking for a file called "infile.dat"
// The one you saved is "outfile.dat"
//			inStream.open("infile.dat");

// change this to the name of the file you created "outfile.dat"
			inStream.open("outfile.dat");
			if (inStream.fail())
			{
				cout << "Input file opening failed.\n";
				exit(1);
			}
// Now it is going to just reading from the file the word "Insonolation"
			string aString;
			inStream >> aString;
// Then a ":" followed by the insonolation value. This is where you need to be specific about how you read and write values
			inStream >> AvgInsonolation;
			cout << "***The Average Insonolation is " << AvgInsonolation << " " << Units << "\n";//echoes insonolation



			// Retrieve and validate number of loads using a while
			cout << "How many loads will you be powering?\n";
			cin >> NumberOfLoads;

			while ((NumberOfLoads < MINLOADS) || (NumberOfLoads > MAXLOADS))//verifies that the number of loads is within the given range
			{
				cout << "Number of loads must be between " << MINLOADS << " and " << MAXLOADS << " loads. Please enter number again.\n";
				cin >> NumberOfLoads;
			}
			cout << "You will be powering " << NumberOfLoads << " loads.\n\n";// Echoes number of loads

			for (int i = 0; i < NumberOfLoads; i++)
			{
				cout << "\nEnter name of Load " << i + 1 << " : ";
				cin >> LoadNames[i];
			}
			int choice;
			do
			{
				cout << "\nWill you be entering Load demands in Watts or Amps?\nEnter 1 for Watts\nEnter 2 for Amps\n";
				cin >> choice;

				double totalLoad = 0.0;
				switch (choice)
				{
				case 1:
					cout << "You will be entering Loads in Watts\n";

					for (int j = 0; j < NumberOfLoads; j++)
					{
						cout << "\nEnter power demand of Load " << j + 1 << " : ";
						cin >> LoadPower[j];
						totalLoad += LoadPower[j];
					}

					listPrint(LoadNames, LoadPower, NumberOfLoads);
					cout << "\nThe total load is " << totalLoad << " watts";
					LoadDmnd = PowerDmnd(totalLoad);
					cout << "\nThe total power demand of your loads is " << LoadDmnd << " Kw\n";
					outStream << LoadDmnd;
					break;


				case 2:
					cout << "You will be entering Loads in Amps\n";

					for (int k = 0; k < NumberOfLoads; k++)
					{
						cout << "\nEnter current demand of Load " << k + 1 << " : ";
						cin >> LoadCurrent[k];
						totalLoad += LoadCurrent[k];
					}

					listPrint(LoadNames, LoadCurrent, load, defVoltage, NumberOfLoads);
					totalLoad = totalLoad * defVoltage;
					cout << "\nThe total load is " << totalLoad << " watts";
					LoadDmnd = PowerDmnd(totalLoad);
					cout << "\nThe total power demand of your loads is " << LoadDmnd << " Kw\n";
					outStream << LoadDmnd;
					break;

				}
			} while (choice < 1);


			cout << "\nEnter number of hours the device will run per day\n";
			cin >> RunTime;
			Energy = RunTime * LoadDmnd; //Calculates the neccessary energy that needs to be generated by the solar panels.
			cout << "\nThe Energy required to run the system for " << RunTime << " hours is " << Energy << " Kwh/day\n";
			WattsNeeded = (Energy / AvgInsonolation) * conv; //Determines total Watts needed to generate enough energy for the system.
			cout << "\nThe required panel wattage to power your loads is " << WattsNeeded << " W\n";
			cout << "\nWhat wattage solar panels will you be using?\n";
			cin >> panelWatts;

			numbPanels = WattsNeeded / panelWatts;
			cout << "\nYou will need " << ceil(numbPanels) << " solar panels to power your loads";
			break;
			
		}
	} while (choice < 1);

		inStream.close();
		outStream.close();

	return 0;
}


double PowerDmnd(double totalLoad) // function definition for load conversion calculation
{
	const double conv = 1000.0;
	double convert;
	convert = totalLoad / conv;
	return convert;
}

void listPrint(string LoadNames[], double LoadPower[], int NumberOfLoads)
{
	for (int i = 0; i < NumberOfLoads; i++)
	{
		cout << LoadNames[i] << " requires " << LoadPower[i] << " Watts\n";
	}
return;
}

void listPrint(string LoadNames[], double LoadCurrent[], double load, double defVoltage, int NumberOfLoads)
{
	for (int i = 0; i < NumberOfLoads; i++)
	{
		load = LoadCurrent[i] * defVoltage;
		cout << LoadNames[i] << " requires " << load << " Watts\n";
	}
	return;
}

void listPrint(string InsolationVals[], int numbIV)
{
	for (int i = 0; i < NumberOfLoads; i++)
	{
		cout << "Average Insolation " << i + 1 << " is " << InsolationVals[i] << Units << "\n";
	}
	return;
}





/*// Retrieve and validate number of loads using a while
	cout << "How many loads will you be powering?\n";
	cin >> NumberOfLoads;

	while ((NumberOfLoads < MINLOADS) || (NumberOfLoads > MAXLOADS))//verifies that the number of loads is within the given range
	{
		cout << "Number of loads must be between " << MINLOADS << " and " << MAXLOADS << " loads. Please enter number again.\n";
		cin >> NumberOfLoads;
	}
	cout << "You will be powering " << NumberOfLoads << " loads.\n\n";// Echoes number of loads

	for (int i = 0; i < NumberOfLoads; i++)
	{
		cout << "\nEnter name of Load " << i + 1 << " : ";
		cin >> LoadNames[i];
	}
		int choice;
		do
		{
			cout << "\nWill you be entering Load demands in Watts or Amps?\nEnter 1 for Watts\nEnter 2 for Amps\n";
			cin >> choice;

			double totalLoad = 0.0;
			switch (choice)
			{
			case 1:
				cout << "You will be entering Loads in Watts\n";

				for (int j = 0; j < NumberOfLoads; j++)
				{
					cout << "\nEnter power demand of Load " << j + 1 << " : ";
					cin >> LoadPower[j];
					totalLoad += LoadPower[j];
				}

				listPrint(LoadNames, LoadPower, NumberOfLoads);
				cout << "\nThe total load is " << totalLoad << " watts";
				LoadDmnd = PowerDmnd(totalLoad);
				cout << "\nThe total power demand of your loads is " << LoadDmnd << " Kw\n";
				outStream << LoadDmnd;
				break;


			case 2:
				cout << "You will be entering Loads in Amps\n";

				for (int k = 0; k < NumberOfLoads; k++)
				{
					cout << "\nEnter current demand of Load " << k + 1 << " : ";
					cin >> LoadCurrent[k];
					totalLoad += LoadCurrent[k];
				}

				listPrint(LoadNames, LoadCurrent, load, defVoltage, NumberOfLoads);
				totalLoad = totalLoad * defVoltage;
				cout << "\nThe total load is " << totalLoad << " watts";
				LoadDmnd = PowerDmnd(totalLoad);
				cout << "\nThe total power demand of your loads is " << LoadDmnd << " Kw\n";
				outStream << LoadDmnd;
				break;

			}
		} while (choice < 1);

		/*cout << "\nEnter the Average Insonolation value for desired panel location in " << Units << "\n";
		cin >> AvgInsonolation;
		cout << "The Average Insonolation is " << AvgInsonolation << " " << Units << "\n";//echoes insonolation

		inStream >> AvgInsonolation;
		cout << "The Average Insonolation is " << AvgInsonolation << " " << Units << "\n";//echoes insonolation

		cout << "\nEnter number of hours the device will run per day\n";
		cin >> RunTime;
		Energy = RunTime * LoadDmnd; //Calculates the neccessary energy that needs to be generated by the solar panels.
		cout << "\nThe Energy required to run the system for " << RunTime << " hours is " << Energy << " Kwh/day\n";
		WattsNeeded = (Energy / AvgInsonolation) * conv; //Determines total Watts needed to generate enough energy for the system.
		cout << "\nThe required panel wattage to power your loads is " << WattsNeeded << " W\n";
		cout << "\nWhat wattage solar panels will you be using?\n";
		cin >> panelWatts;

		numbPanels = WattsNeeded / panelWatts;
		cout << "\nYou will need " << ceil(numbPanels) << " solar panels to power your loads";*/