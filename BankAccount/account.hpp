#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include "client.hpp"

class Account
{
protected:
    Client* m_client;
    float m_balance;

public:
    Account() : m_client(NULL), m_balance(0) {};

    Account(Client* client, float balance=0) : m_client(client), m_balance(balance) {};

    ~Account() {}; //m_client sera compartilhado entre varios objetos de conta, logo, nao deve ser deletado nos destrutores

    //Acessors methods - gettern and setters
    string GetInformation();
    float GetBalance() { return m_balance;};

    bool Withdraw(float value);
    bool operator -=(float value);

    void Deposit(float value);
    void operator +=(float value);

    bool Transfer(float value, Account &acc);
    void operator >> (Account &acc);
};





#endif
