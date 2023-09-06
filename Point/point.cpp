#include "point.hpp"

Point::Point()
{
    cout << "Initializing point" << endl;
    this->x = 0;
    this->y = 0;

}

void Point::SetX(int value)
{
    this->x = value;
}

void Point::SetY(int value)
{
    this->y = value;
}

void Point::ShowInfo()
{
    cout << "x: " << this->x << " - y: " << this->y << endl;
}

void Point::Update(int x, int y)
{
    this->x  = x;
    this->y  = y;

    this->ShowInfo();
}

int Point::GetX()
{
    return this->x;
}

int Point::GetY()
{
    return this->y;
}
/*
void Point::GetXY(int &x, int &y)
{
    x = this->x;
    y = this->y;
}*/

void Point::GetXY(int *x, int *y)
{
    *x = this->x;
    *y = this->y;
}
