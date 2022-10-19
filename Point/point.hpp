#include <iostream>

using namespace std;

class Point
{
//atributos / estados
private:
    int x, y;

//metodos / comportamentes
public:
    //constructor - sem retorno, mesmo nome da class
    Point();

    //metodos de acesso -- Getters and Setters
    //Setters
    void SetX(int value);
    void SetY(int value);
    void Update(int x, int y);

    //Getters
    void ShowInfo();
    int GetX();
    int GetY();
    //void GetXY(int &x, int &y);
    void GetXY(int *x, int *y);

};

