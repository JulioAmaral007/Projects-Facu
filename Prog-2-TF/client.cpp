#include <iostream>

#include "Client.hpp"

using namespace std;

//constructor
Client::Client(string nome, string cpf, string RG, string codClient):Pessoa(nome, cpf, RG)
{
	setCodClient(codClient);
}

//functions set
void Client::setCodClient(string codClient)
{
	this->codClient = codClient;
}

//functions get

string Client::getCodClient()
{
	return codClient;
}

//others functions

void Client::print()
{
	cout<<"Name: "<<getName()<<endl;
	cout<<"Cpf: "<<getCpf()<<endl;
	cout<<"RG: "<<getRG()<<endl;
	cout<<"Codigo do cliente: "<<getCodClient()<<endl;
}


Client::~Client()
{
	
}
