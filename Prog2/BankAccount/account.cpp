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

bool Account::Withdraw(float value)
{
    if(m_balance >= value)
    {
        m_balance -= value;
        return true;
    }
    else
        return false;
}

bool Account::operator -=(float value)
{
    return Withdraw(value);
}

void Account::Deposit(float value)
{
    m_balance+=value;
}

void Account::operator +=(float value)
{
    m_balance+=value;
}

bool Account::Transfer(float value, Account &acc)
{
    if(this->Withdraw(value))
    {
        acc.Deposit(value);
        return true;
    }
    else
        return false;
}

void Account::operator >> (Account &acc)
{
    if(m_balance > 0)
    {
        Withdraw(m_balance);
        acc.Deposit(m_balance);
    }
}
