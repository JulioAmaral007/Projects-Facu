#ifndef SACCOUNT_HPP
#define SACCOUNT_HPP

#include "account.hpp"

class Saccount : public Account
{
protected:
    float m_limit;
public:
    Saccount() : m_limit(0) {};

    Saccount(Client *client, float balance=0, float limit=1000) : Account(client, balance), m_limit(limit) {};

    //Saccount(Client *client, float balance=0, float limit=1000) : m_client(client), m_balance(balance), m_limit(limit) {};

    //Acessors methods - gettern and setters
    string GetInformation();

    bool Withdraw(float value) ;
    bool Transfer(float value, Account &acc);

};

#endif
