#include <iostream>

#include "Car.hpp"
#define MAX 1000

#ifndef CARDB_HPP
#define CARDB_HPP

using namespace std;

class CarDB
{
	private:
		Car* cars[MAX];

	public:
		CarDB();

		int newCar(string, string, string, int);
		int deleteCar(string);
		int rent(string, Client*); //licensePlate and Client
		int release(string); // licensePlate
		int releaseAll(Client*);
		void listAvailable();
		void listLeased();

		~CarDB();
	
};

#endif