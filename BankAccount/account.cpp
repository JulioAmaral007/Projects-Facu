#include "account.hpp"
#include <sstream>

string Account::GetInformation()
{
    stringstream sst;

    if(m_client == NULL)
    {
        sst << "Client not informed";
    }
    else
    {
        sst << "Client Name: " << m_client->GetName() << " - " << "Profession: " << m_client->GetProfession() << " - " << "Income : " << m_client->GetIncome() << " - " << "Balance: " << m_balance;
    }

    return sst.str();
};

