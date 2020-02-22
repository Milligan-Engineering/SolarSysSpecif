
//File Name: SolarSysSpecif.cpp
//Author: Erin Forgety
//Email Address: efforgety@my.milligan.edu
//Term Project
//Description: This program uses calculations to determine the number of solar panels needed to run a system based on user inputs.
// Edited to correct menu and variable declaration errors
//Last Changed: 02/17/2020


#include <iostream>
#include <string>
#include <numeric>
#include <cmath>
using namespace std;

const int MINLOADS = 1, MAXLOADS = 5, defVoltage = 12, conv = 1000;
double AvgInsonolation, Energy = 0.0, Current, PowerDmnd, totalLoad, numbPanels, RunTime, WattsNeeded, panelWatts;																																																																																																		
double LoadPower[MAXLOADS], LoadCurrent[MAXLOADS];
double loadDmnd(double totalLoad, const int conv)
int NumberOfLoads;
string Device, Units = "Kwh/day/m^2";
string LoadNames[MAXLOADS];


int main()
{
	cout << "Welcome to the Solar System Specifier Program \n\n";

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
			cout << "Will you be entering Load demands in Watts or Amps?\nEnter 1 for Watts\nEnter 2 for Amps\n";
			cin >> choice;

			int totalLoad = 0;
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
				PowerDmnd = totalLoad / conv;
				cout << "The total power demand of your loads is " << PowerDmnd << " Kw\n";
				cout << "\nEnter the Average Insonolation value for desired panel location in " << Units << "\n";
				cin >> AvgInsonolation;
				cout << "The Average Insonolation is " << AvgInsonolation << " " << Units << "\n\n";//echoes insonolation
				cout << "\nEnter number of hours the device will run per day\n";
				cin >> RunTime;
				Energy = RunTime * PowerDmnd; //Calculates the neccessary energy that needs to be generated by the solar panels.
				cout << "\nThe Energy required to run the system for " << RunTime << " hours is " << Energy << " Kwh/day\n";
				WattsNeeded = (Energy / AvgInsonolation) * conv; //Determines total Watts needed to generate enough energy for the system.
				cout << "\nThe required panel wattage to power your loads is " << WattsNeeded << " W\n";
				cout << "\nWhat wattage solar panels will you be using?\n";
				cin >> panelWatts;
				numbPanels = WattsNeeded / panelWatts;
				cout << "\nYou will need " << ceil(numbPanels) << " solar panels to power your loads";
				break;

			case 2:
				cout << "You will be entering Loads in Amps\n";

				for (int k = 0; k < NumberOfLoads; k++)
				{
					cout << "\nEnter current demand of Load " << k + 1 << " : ";
					cin >> LoadCurrent[k];
					totalLoad += LoadCurrent[k];
				}
				PowerDmnd = (totalLoad * defVoltage) / 1000; //Calculates the power demand of the load. Divides by 1000 to convert to Kw
				cout << "The total power demand of your loads is " << PowerDmnd << " Kw\n";
				cout << "\nEnter the Average Insonolation value for desired panel location in " << Units << "\n";
				cin >> AvgInsonolation;
				cout << "The Average Insonolation is " << AvgInsonolation << " " << Units << "\n\n";//echoes insonolation
				cout << "\nEnter number of hours the device will run per day\n";
				cin >> RunTime;
				Energy = RunTime * PowerDmnd; //Calculates the neccessary energy that needs to be generated by the solar panels.
				cout << "\nThe Energy required to run the system for " << RunTime << " hours is " << Energy << " Kwh/day\n";
				WattsNeeded = (Energy / AvgInsonolation) * 1000; //Determines total Watts needed to generate enough energy for the system.
				cout << "\nThe required panel wattage to run " << Device << " is " << WattsNeeded << " W\n";
				cout << "\nWhat wattage solar panels will you be using?\n";
				cin >> panelWatts;
				numbPanels = WattsNeeded / panelWatts;
				cout << "\nYou will need " << ceil(numbPanels) << " solar panels to power your loads";
				break;
			}
		} while (choice != 1);
	
	return 0;
}


/*if (NumberOfLoads == 1) //runs orgininal prgm for powering one load if number of loads entered is equal to one
	{
		cout << "Enter name of the deivce you will be powering \n";
		cin >> Device;
		cout << "\nEnter the operating voltage needed to power " << Device << " in V\n";
		cin >> Voltage;
		cout << "The required voltage is " << Voltage << " V.\n";//echoes voltage
		cout << "\nEnter the Average Insonolation value for desired panel location in " << Units << "\n";
		cin >> AvgInsonolation;
		cout << "The Average Insonolation is " << AvgInsonolation << " " << Units << "\n\n";//echoes insonolation
		cout << "Enter the Current needed to run the " << Device << " in units A\n";
		cin >> Current;
		PowerDmnd = (Current * Voltage) / 1000; //Calculates the power demand of the load. Divides by 1000 to convert to Kw
		cout << "The Power needed to run a " << Current << " A and " << Voltage << " V " << Device << " is " << PowerDmnd << " Kw\n";
		cout << "\nEnter number of hours the device will run per day\n";
		cin >> RunTime;
		Energy = RunTime * PowerDmnd; //Calculates the neccessary energy that needs to be generated by the solar panels.
		cout << "\nThe Energy required to run the system for " << RunTime << " hours is " << Energy << " Kwh/day\n";
		WattsNeeded = (Energy / AvgInsonolation) * 1000; //Determines total Watts needed to generate enough energy for the system.
		cout << "\nThe required panel wattage to run " << Device << " is " << WattsNeeded << " W\n";
	}
	else if (NumberOfLoads == 2,3,4,5)//runs modified version of og prgm for panel powering multiple loads
	{
		for (int i = 0; i < NumberOfLoads; i++)
		{
			cout << "\nEnter name of Load " << i + 1 << " : ";
			cin >> LoadNames[i];
		}
	}*/
