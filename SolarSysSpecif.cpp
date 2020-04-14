
//File Name: SolarSysSpecif.cpp
//Author: Erin Forgety
//Email Address: efforgety@my.milligan.edu
//Term Project
//Description: This program uses calculations to determine the number of solar panels needed to run a system based on user inputs.
// Refined Search function
//Last Changed: 04/14/2020


#include <iostream>
#include <string>
#include <numeric>
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;
ifstream inStream;
ofstream outStream; 

const int MINLOADS = 1, MAXLOADS = 10, MAXVALS = 10;
const double conv = 1000.0;
double AvgInsolation, AvgInsonolation = 4.0, Energy = 0.0, Current, totalLoad, numbPanels, RunTime, WattsNeeded, panelWatts, LoadDmnd, load, hours, defVoltage = 12.0, target;
int NumberOfLoads, numbIV;

double LoadPower[MAXLOADS], LoadCurrent[MAXLOADS];

string Device, Units = "Kwh/day/m^2";
string LoadNames[MAXLOADS], InsolationVals[MAXVALS];
char aString[] = "Average Insolation", ans, answ, result;

double PowerDmnd(double totalLoad); //precondition: user inputs total load
//postcondition: Function returns a value of variable type double after converting the power demand from watts to kilowatts

char search(double LoadPower[], const int MAXLOADS, double target);
char search2(double LoadCurrent[], const int MAXLOADS, double target);

void listPrint(string LoadNames[], double LoadPower[], int NumberOfLoads);
void listPrint(string LoadNames[], double LoadCurrent[], double load, double defVoltage, int NumberOfLoads);
void listPrint(string InsolationVals[], int numbIV);
void getHours(double& hours);
void newLine();

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

			while ((numbIV < MINLOADS) || (numbIV > MAXVALS))//verifies that the number is within the given range
			{
				cout << "Number must be between " << MINLOADS << " and " << MAXVALS << " . Please enter number again.\n";
				cin >> numbIV;
			}
			cout << "You will be entering " << numbIV << " Insolation values.\n";// Echoes number

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

			break;

		case 2:
			cout << "You will be running a system analysis\n";

			inStream.open("outfile.dat");
			if (inStream.fail())
			{
				cout << "Input file opening failed.\n";
				exit(1);
			}
// Now it is going to just reading from the file the word "Insonolation"
			inStream >> aString;
// Then a ":" followed by the insonolation value. This is where you need to be specific about how you read and write values
			inStream >> InsolationVals[0];
			cout << aString << " : " << InsolationVals[0] << " " << Units << "\n";//echoes insonolation
			stringstream geek(InsolationVals[0]);
			geek >> AvgInsolation;


			// Retrieve and validate number of loads using a while
			cout << "How many loads will you be powering?\n";
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

					cout << "\nWould you like to check the array you filled for a target value?\nType 'y' for yes or 'n' for no\n";
					cin >> ans;
					do
					{
						cout << "Enter the power value you want to search for\n";
						cin >> target;
						result = search(LoadPower, MAXLOADS, target);
						if (result == -1)
						{
							cout << target << " is not stored in the array\n";
						}
						else
						{
							cout << target << " is stored in array position " << LoadNames[result] << endl << "\n";
						}
						cout << "Would you like to search again? Type y/n\n";
						cin >> answ;

					} while ((answ != 'n') && (answ != 'N')); 

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

					cout << "\nWould you like to check the array you filled for a target value?\nType 'y' for yes or 'n' for no\n";
					cin >> ans;
					do
					{
						cout << "Enter the current value you want to search for\n";
						cin >> target;
						result = search2(LoadCurrent, MAXLOADS, target);
						if (result == -1)
						{
							cout << target << " is not stored in the array\n";
						}
						else
						{
							cout << target << " is stored in array position " << LoadNames[result] << endl << "\n";
						}
						cout << "Would you like to search again? Type y/n\n";
						cin >> answ;

					} while ((answ != 'n') && (answ != 'N'));

					listPrint(LoadNames, LoadCurrent, load, defVoltage, NumberOfLoads);
			
					totalLoad = totalLoad * defVoltage;
					cout << "\nThe total load is " << totalLoad << " watts";
					LoadDmnd = PowerDmnd(totalLoad);
					cout << "\nThe total power demand of your loads is " << LoadDmnd << " Kw\n";
					outStream << LoadDmnd;
					break;

				}
			} while (choice < 1);

			getHours(RunTime);
			
			Energy = RunTime * LoadDmnd; //Calculates the neccessary energy that needs to be generated by the solar panels.
			cout << "\nThe Energy required to run the system for " << RunTime << " hours is " << Energy << " Kwh/day\n";
			WattsNeeded = (Energy / AvgInsonolation) * conv; //Determines total Watts needed to generate enough energy for the system.
			cout << "\nThe required panel wattage to power your loads is " << WattsNeeded << " W\n";
			cout << "\nWhat wattage solar panels will you be using?\n";
			cin >> panelWatts;

			numbPanels = WattsNeeded / panelWatts;
			cout << "\nYou will need " << ceil(numbPanels) << " solar panels to power your loads\n";
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

char search(double LoadPower[], const int MAXLOADS, double target)
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
		return - 1;
}

char search2(double LoadCurrent[], const int MAXLOADS, double target)
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

void listPrint(string LoadNames[], double LoadPower[], int NumberOfLoads)
{
	cout << "\n";
	for (int i = 0; i < NumberOfLoads; i++)
	{
		cout << LoadNames[i] << " requires " << LoadPower[i] << " Watts\n";
	}
return;
}

void listPrint(string LoadNames[], double LoadCurrent[], double load, double defVoltage, int NumberOfLoads)
{
	cout << "\n";
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

/*char ans;
			char ans1;
			char result;
			string target;
			cout << "Would you like to check the array you filled for a target value?\nType 'y' for yes or 'n' for no";
			cin >> ans;
			do
			{
				cout << "Enter the Insolation value you want to search for";
				cin >> target;
				result = search(string InsolationVals, int numbIV, int target);
				if (result == -1)
					cout << target << " is not stored in the array";
				else
					cout << target << " is stored in array position " << result << endl;
				cout << "Would you like to search again? Type y/n";
				cin << ans1;

			} while ((ans1 != 'n') && (ans1 != 'N'));*/