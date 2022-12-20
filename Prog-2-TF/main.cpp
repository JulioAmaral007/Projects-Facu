
#include "CarDB.hpp"
#include "ClientDB.hpp"

#include <iostream>
#include <string>
using namespace std;

int main()
{ // Principal menu

  int option;
  ClientDB c;
  CarDB car;

  string name, cpf, RG, code;
  string nameOfCar, color, licensePlate;
  int year, aux;
  Client *client;

  do
  {
    /*cout << "                                       ______________             "
            "          "
         << endl;
    cout << "                                  _.-''         || \ `-.          "
            "          "
         << endl;
    cout << "                             _.-''              ||   \  `-._      "
            " -=====/  "
         << endl;
    cout << "                   _____..-''.<(]_______________||_____\    "
            "`-------/--/.   "
         << endl;
    cout << "         _..---''''__      /  ``     "
            "____________|__________.....________\  "
         << endl;
    cout << "   _.-'''__.-.='_`_`-.\---|---'''''''       ` `  |   __  "
            "/.-'_`_`-.\      \."
         << endl;
    cout << " .' --''' .'/ /  |  \ \`. |                     /   '='.'/ /  |  "
            "\ \`.  __.|"
         << endl;
    cout << " |--------|| |``-O-''| ||----------------------/-------|| "
            "|``-O-''| ||''  / "
         << endl;
    cout << " '''----..| \\\\/_ _\/ / |______________________________|\\\\/_ "
            "_\/ / `--'  "
         << endl;
    cout << "             `-.....-'                                    "
            "`-.....-'         "
         << endl;*/

    cout << endl
         << "Car Rental Application" << endl;

    cout << "========== Clients ==========" << endl;
    cout << "1 - New client account" << endl;
    cout << "3 - List of client accounts" << endl;

    cout << "========== Cars ==========" << endl;

    cout << "4 - New car rent" << endl;
    cout << "5 - New car devolution" << endl;
    cout << "6 - List of car leased" << endl;
    cout << "7 - List of available cars" << endl;
    cout << "8 - To register new car" << endl;
    cout << "9 - To delete a car" << endl;

    cout << "0 - Quit" << endl;

    cin >> option;

    switch (option)
    {

    case 0:
      break;
    case 1:

      cout << "Client name: " << endl;
      cin.ignore();
      getline(cin, name);
      cout << "Client cpf: " << endl;
      cin >> cpf;
      cout << "Client RG: " << endl;
      cin >> RG;
      cout << "Client code: " << endl;
      cin >> code;

      if (c.include(name, cpf, RG, code))
        cout << "Successfully added customer" << endl;
      else
        cout << "space for customers full" << endl;

      cout << "\nPress ENTER to continue..." << endl;
      cin.ignore();
      cin.get();
      break;

    case 3:

      c.list();
      cout << "\nPress ENTER to continue..." << endl;
      cin.ignore();
      cin.get();
      break;

    case 4:

      cout << "Car license plate: " << endl;
      cin >> licensePlate;
      cout << "Client cpf: " << endl;
      cin >> cpf;
      client = c.find(cpf);

      if (client != NULL)
      {
        aux = car.rent(licensePlate, client);

        if (aux == 2)
          cout << "Unavailable car " << endl;
        else if (aux == 0)
          cout << "License plate not found" << endl;
        else if (aux)
          cout << "Rent successfully" << endl;
      }
      else
        cout << "Customer not found" << endl;

      cout << "\nPress ENTER to continue..." << endl;
      cin.ignore();
      cin.get();
      break;

    case 5:

      cout << "Car license plate: " << endl;
      cin >> licensePlate;
      aux = car.release(licensePlate);
      if (aux == 1)
        cout << "Successfully relsease car" << endl;
      else if (aux == 0)
        cout << "Car not found" << endl;

      cout << "\nPress ENTER to continue..." << endl;
      cin.ignore();
      cin.get();
      break;

    case 6:

      car.listLeased();
      cout << "\nPress ENTER to continue..." << endl;
      cin.ignore();
      cin.get();
      break;

    case 7:

      car.listAvailable();
      cout << "\nPress ENTER to continue..." << endl;
      cin.ignore();
      cin.get();
      break;

    case 8:

      cout << "Car name: " << endl;
      cin.ignore();
      getline(cin, nameOfCar);
      cout << "Car color: " << endl;
      cin >> color;
      cout << "Car license plate: " << endl;
      cin >> licensePlate;
      cout << "Car year: " << endl;
      cin >> year;

      if (car.newCar(nameOfCar, color, licensePlate, year))
        cout << "Successfully added car " << endl;
      else
        cout << "Bank full of cars" << endl;

      cout << "\nPress ENTER to continue..." << endl;
      cin.ignore();
      cin.get();
      break;

    case 9:

      cout << "Car license plate: " << endl;
      cin >> licensePlate;

      if (car.deleteCar(licensePlate))
        cout << "Successfully deleted car" << endl;
      else
        cout << "License plate not found" << endl;

      cout << "\nPress ENTER to continue..." << endl;
      cin.ignore();
      cin.get();
      break;

    default:

      cout << "Please enter with a valid option" << endl;
      cout << "\nPress ENTER to continue..." << endl;
      cin.ignore();
      cin.get();
      break;
    }

  } while (option);
}
