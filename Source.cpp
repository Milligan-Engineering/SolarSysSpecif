
#include <iostream>
#include <string>
using namespace std;

double AvgInsonolation, PowerDmnd, Energy, Current, Voltage;
int RunTime, WattsNeeded;
string Device, Units = "Kwh/day/m^2";

int main()
{
	cout << "Welcome to the Solar System Specifier Program \n\n";
	cout << "Enter name of the deivce you will be powering \n";
	cin >> Device;
	cout << "\nEnter the Average Insonolation value for desired panel location in " << Units << "\n";
	cin >> AvgInsonolation;
	cout << "The Average Insonolation is " << AvgInsonolation << " " << Units << "\n\n";
	cout << "Enter the Current and Voltage needed to run the " << Device << " in units A and V\n";
	cin >> Current >> Voltage;
	PowerDmnd = (Current * Voltage) / 1000;
	cout << "The Power needed to run a " << Current << " A and " << Voltage << " V " << Device << " is " << PowerDmnd << " Kw\n";
	cout << "\nEnter number of hours the device will run per day\n";
	cin >> RunTime;
	Energy = PowerDmnd * RunTime;
	cout << "\nThe Energy required to run the system for " << RunTime << " hours is " << Energy << " Kwh/day\n";
	WattsNeeded = (Energy / AvgInsonolation) * 1000;
	cout << "\nThe required panel wattage to run " << Device << " is " << WattsNeeded << " W\n";

	return 0;
}
