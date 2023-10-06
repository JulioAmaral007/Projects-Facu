#include <iostream>
#include "Car.hpp"

using namespace std;

Car::Car(string car, string color, string licensePlate, int year) : Vehicle(color, licensePlate, year)
{
	setCar(car);
	rentedCar = NULL;
}

void Car::setCar(string car)
{
	this->car = car;
}

void Car::setRentedCar(Client* rentedCar)
{
	this->rentedCar = rentedCar;
}

string Car::getCar()
{
	return car;
}

Client* Car::getRentedCar()
{
	return rentedCar;
}


void Car::rentCar(Client* client)
{
	setRentedCar(client);
}

void Car::releaseCar()
{
	rentedCar = NULL;
}

void Car::printAll()
{
	cout<<"-----------------"<<endl;
	cout<<"Car: "<<getCar()<<endl;
	print();
	if(rentedCar != NULL)
	{
		cout<<endl<<"Rented by: "<<endl;
		rentedCar->print();
	}
	cout<<"-----------------"<<endl;
}

int Car::availability()
{
	if(rentedCar == NULL )
		return 1;
	else
		return 0;
}

Car::~Car()
{
	
}