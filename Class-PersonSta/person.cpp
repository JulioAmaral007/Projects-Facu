#include "person.hpp"

Person::Person()
{
    cout << "initializing person" << endl;
}

Person::Person(string name) : Person()
{
    this->m_name = name;
}

Person::Person(string name, string address) : Person()
{
    this->m_name = name;
    this->m_address = address;
}

Person::Person(string name, string address, unsigned int age, float height, float weight) : Person()
{
    this->m_name = name;
    this->m_address = address;
    this->m_age = age;
    this->m_height = height;
    this->m_weight = weight;
}

Person::~Person()
{
    cout << "destructor called" << endl;
}

void Person::ShowInfo()
{
    cout << "Name: " << this->m_name << endl;
}

