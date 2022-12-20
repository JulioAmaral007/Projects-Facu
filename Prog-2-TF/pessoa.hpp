#ifndef PESSOA_HPP
#define PESSOA_HPP

#include <iostream>

using namespace std;


class Pessoa
{
	private:
		string name;
		string cpf;
		string RG;

	public:
		//constructor
		
		Pessoa(string,string,string);

		// Functions set
		void setName(string);
		void setCpf(string);
		void setRG(string);

		// Functions get
		string getName();
		string getCpf();
		string getRG();

		//others functions

		virtual void print() = 0;	

		//destructor
		~Pessoa();
	
};

#endif