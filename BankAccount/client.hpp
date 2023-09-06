#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>

using namespace std;

class Client
{
private:
    string m_name;
    string m_profession;
    float m_income;

public:
    Client() : m_name(""), m_profession(""), m_income(0) {};

    Client(string nome, string profession="", float income=0) : m_name(nome), m_profession(profession), m_income(income) {};

    //getters and setters
    string GetName() { return m_name; };
    string GetProfession() { return m_profession; };
    float GetIncome() { return m_income; };

};


#endif
