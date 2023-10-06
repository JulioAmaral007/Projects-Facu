#include <iostream>

#include "Vehicle.hpp"

using namespace std;

// CONSTRUCTOR
Vehicle::Vehicle(string color, string licensePlate, int year)
{
	setColor(color);
	setLicensePlate(licensePlate);
	setYear(year);
}


// FUNCTIONS SET
void Vehicle::setColor(string color)
{
	this->color = color;
}

void Vehicle::setLicensePlate(string licensePlate)
{
	this->licensePlate = licensePlate;
}

void Vehicle::setYear(int year)
{
	this->year = year;
}

//FUNCTIONS GET
string Vehicle::getColor()
{
	return color;
}

string Vehicle::getLicensePlate()
{
	return licensePlate;
}

int Vehicle::getYear()
{
	return year;
}

void Vehicle::print()
{
	cout<<"Color: "<<getColor()<<endl;
	cout<<"License Plate: "<<getLicensePlate()<<endl;
	cout<<"Year: "<<getYear()<<endl;
}

Vehicle::~Vehicle()
{
	
}