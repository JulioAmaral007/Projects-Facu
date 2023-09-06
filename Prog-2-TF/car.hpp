#include <iostream>

#include "Client.hpp"
#include "Vehicle.hpp"

using namespace std;

#ifndef CAR_HPP
#define CAR_HPP

class Car : public Vehicle
{
	private:
		string car;
		Client* rentedCar;

	public:
		Car(string, string,  string, int);

		//Functions SET
		void setCar(string);
		void setRentedCar(Client*);

		//functions GET
		string getCar();
		Client* getRentedCar();

		//others functions
		void rentCar(Client*); // set cpf of Client
		void releaseCar(); // release car
		void printAll();
		int availability();

		~Car();
	
};

#endif