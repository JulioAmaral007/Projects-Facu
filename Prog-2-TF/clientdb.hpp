#ifndef CLIENTDB_HPP
#define CLIENTDB_HPP

#include <iostream>

#include "Client.hpp"
#define MAX 1000

using namespace std;

class ClientDB
{
	private:
		Client * customers[MAX];

	public:
		ClientDB();
		int include(string, string, string, string); // add client, return 1 if sucess or 0 if failed 

		Client* find(string);
		void list(); // list of clients

		~ClientDB() {};
	
};

#endif
