#ifndef PERSON_HPP
#define PERSON_HPP

#include <iostream>

using namespace std;

class Person
{
private:
    string *m_name;
    string *m_address;
    unsigned int *m_age;
    float *m_height;
    float *m_weight;

public:
    Person();
    Person(string name);
    Person(string name, string address);
    Person(string name, string address, unsigned int age, float height, float weight);

    ~Person();

    void ShowInfo();

};

#endif
