#include "ClientDB.hpp"


#include <iostream>


using namespace std;

ClientDB::ClientDB() {
  int i;
  for (int i = 0; i < 1000; i++) {
    customers[i] = NULL;
  }
}

int ClientDB::include(string name, string cpf, string RG, string code) {


    int i;
  for (i = 0; i < 1000; i++) {
    if (customers[i] == NULL) {
      customers[i] = new Client(name, cpf, RG, code);
      return 1;
    }

  }


  return 0;
}

void ClientDB::list()

{
  int i;
  for (int i = 0; i < 1000; i++) {
    if (customers[i] != NULL) {
      cout << "-----------------------" << endl;
      customers[i]->print();
      cout << "-----------------------" << endl;
    }
  }
}

Client *ClientDB::find(string cpf) {
  int i;
  for (i = 0; i < 1000; i++) {
    if (customers[i] != NULL) {
      if (customers[i]->getCpf() == cpf) {
        return customers[i];
      }
    }
  }

  return NULL;
}
