#include <iostream>

using namespace std;

#ifndef VEHICLE_HPP
#define VEHICLE_HPP

class Vehicle
{
	private:
		string color, licensePlate;
		int year;

	public:
		Vehicle(string,string, int);

		//functions set
		void setColor(string);
		void setLicensePlate(string);
		void setYear(int);

		//functions get
		string getColor();
		string getLicensePlate();
		int getYear();

		void print();

		~Vehicle();
	
};

#endif