#include "person.hpp"

int main(int argc, const char *argv[])
{
    Person p1;
    Person p2("Antonio");
    Person p3("Ricardo", "Rua XXXX");

    Person *p4 = new Person();
    Person *p5 = new Person("jOAO");

    p1.ShowInfo();
    p2.ShowInfo();
    p3.ShowInfo();
    p4->ShowInfo();
    p5->ShowInfo();

    delete p4;
    delete p5;

    return 0;
}
