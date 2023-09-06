#include <iostream>
#include "types.hpp"

using namespace std;

enum DataType{tnone, tint, tfloat, tdouble, tpoint2d};

class Element
{
private:
    void* m_data;

    //0-NONE 1-int 2-float 3-double
    DataType m_type;

public:
    //Element() : m_data(NULL), m_type(0) {};
    Element();
    Element(int v);
    Element(float v);
    Element(double v);
    Element(Point2d v);
    ~Element();

    void ShowInfo();

};
