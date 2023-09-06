#include "Element.hpp"
#include <vector>

int main()
{
    //exemplo de enumerador
    //DataType meutipodedados;
    //meutipodedados = tint;

    Element e1;
    Element e2((int) 10);
    Element e3((float) 3.1415);
    Element e4((double) 5.55);
    Element e5(Point2d(5,5));

    e1.ShowInfo();
    e2.ShowInfo();
    e3.ShowInfo();
    e4.ShowInfo();
    e5.ShowInfo();

    /*
    vector<Element> GenericList;
    GenericList.push_back(e1);
    GenericList.push_back(e2);
    GenericList.push_back(e3);
    GenericList.push_back(e4);

    for(size_t i=0; i<GenericList.size(); i++)
    {
        GenericList.at(i).ShowInfo();
    }*/

    return 0;
};
