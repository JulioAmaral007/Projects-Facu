#include "Element.hpp"

Element::Element()
{
    m_data = NULL;
    m_type = tnone;
}

Element::Element(int v)
{
    m_data = new int(v);
    m_type = tint;
}

Element::Element(float v)
{
    m_data = new float(v);
    m_type = tfloat;
}

Element::Element(double v)
{
    m_data = new double(v);
    m_type = tdouble;
}

Element::Element(Point2d v)
{
    m_data = new Point2d(v);
    m_type = tpoint2d;
}

Element::~Element()
{
    if(m_data) delete m_data;
}

void Element::ShowInfo()
{
    if(m_type == tnone)
        cout << "Element: empty" << endl;
    if(m_type == tint)
        cout << "Element: integer -> "      << *(int*)m_data << endl;
    if(m_type == tfloat)
        cout << "Element: float point -> "   << *(float*)m_data << endl;
    if(m_type == tdouble)
        cout << "Element: double -> "        << *(double*)m_data << endl;
    if(m_type == tpoint2d)
        cout << "Element: point2d -> ("        << ((Point2d*) m_data)->m_x << "," << ((Point2d*)m_data)->m_y << ")" << endl;

}


