#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>




#include "Pessoa.hpp"
using namespace std;

class Client : public Pessoa 
{
	private:
		string codClient;

	public:
		// constructor
		Client(string,string,string,string);

		//Functions Set
		void setCodClient(string);

		//functions Get
		string getCodClient();

		//others functions
		void print();

		~Client();
	
};

#endif