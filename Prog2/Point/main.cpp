#include <iostream>
#include <vector>
#include "point.hpp"

int main()
{
    //instanciacao
    Point p1;
    Point p2;
    Point p3;

    //usando um metodo de acesso do tipo setter
    p1.SetX(10);
    p1.SetY(10);
    p2.SetX(20);
    p2.SetY(20);
    p3.SetX(20);
    p3.SetY(40);

    //chamando metodo qualquer
    //p1.ShowInfo();
    //p1.Update(15,15);

    int v1, v2;
    p1.GetXY(&v1, &v2);

    Point p4;
    p4.SetX(p2.GetX());
    p4.SetY(p3.GetY());

    //guardar em um vector
    vector< Point > Polygon;
    Polygon.push_back(p1);
    Polygon.push_back(p2);
    Polygon.push_back(p3);
    Polygon.push_back(p4);

    for(size_t i=0; i<Polygon.size(); i++)
    {
        Polygon.at(i).ShowInfo();
    }

    return 0;
};
