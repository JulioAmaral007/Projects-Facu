#include <iostream>

#include "CarDB.hpp"
#define MAX 1000

using namespace std;

CarDB::CarDB()
{
	int i;
	for (i = 0; i < MAX; i++)
	{
		cars[i] = NULL;
	}
}

int CarDB::newCar(string car, string color, string licensePlate, int year)
{
	int i;
	for(i=0; i<MAX; i++)
	{
		if(cars[i] == NULL )
		{
			cars[i] = new Car(car, color, licensePlate, year);
			return 1;
		}
	}
	return 0;
}

int CarDB::deleteCar(string licensePlate)
{
	int i;
	for (int i = 0; i < MAX; i++)
	{
		if(cars[i] != NULL)
		{
			if(cars[i]->getLicensePlate() == licensePlate )
			{
				delete(cars[i]);
				cars[i] = NULL;
				return 1;
			}
		}
	}

	return 0;
}

int CarDB::rent(string licensePlate, Client* client)
{
	int i;
	for(i=0; i<MAX;i++)
	{
		if(cars[i] != NULL)
		{
			if(cars[i]->getLicensePlate() == licensePlate)
			{
				if(cars[i]->availability())
				{
					cars[i]->rentCar(client);
					return 1;
				}
				else 
					return 2;
			}
		}
	}

	return 0;
}

int CarDB::release(string licensePlate)
{
	int i;
	for(i=0; i<MAX;i++)
	{
		if(cars[i] != NULL)
		{
			if(cars[i]->getLicensePlate() == licensePlate  )
			{
				if(cars[i]->availability() == 0)
				{
					cars[i]->releaseCar();
					return 1;
				}
				else
				{
					cout<<"the car is not rented "<<endl;
					return 2;
				}

			}
		}
	}

	return 0;
}

int CarDB::releaseAll(Client* client)
{
	int i;
	for (i = 0; i < MAX; i++)
	{
		if(cars[i] != NULL )
		{
			if(cars[i]->getRentedCar() == client )
			{
				if(cars[i]->availability() == 0)
				{
					cars[i]->releaseCar();
				}
			}
		}
	}
}

void CarDB::listAvailable()
{
	int i, cont = 0;
	for(i=0; i<MAX; i++)
	{
		if(cars[i] != NULL)
		{
			if(cars[i]-> availability() )
			{
				cars[i]->printAll();
			}
			else
				cont++;
		}
		else cont++;
	}

	if(cont == MAX)
		cout<<"No available cars "<<endl;
}

void CarDB::listLeased()
{
	int i,cont = 0;
	for(i=0; i<MAX; i++)
	{
		if(cars[i] != NULL)
		{
			if(cars[i]->availability() == 0)
			{
				cars[i]->printAll();
			}
			else 
				cont++;
		}
		else cont++;
	}

	if(cont == MAX)
		cout<<"Without rented cars "<<endl;	
}

CarDB::~CarDB()
{
	
}