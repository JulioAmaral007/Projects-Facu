#include "ingresso.hpp"
#include <sstream>
#include <iomanip>

/*string Ingresso::GetInformacao()
{
    string strret;

    if(m_descricao == "")
    {
        strret += "Descricao nao disponivel";
    }
    else
    {
        strret += "Descricao do Ingresso: ";
        strret += m_descricao;
        strret += " -> Valor: R$ ";
        strret += to_string(m_valor);
    }

    return strret;
}*/

string Ingresso::GetInformacao()
{
    stringstream strret;

    if(m_descricao == "")
    {
        strret << "Descricao nao disponivel";
    }
    else
    {
        strret << "Descricao do Ingresso: ";
        strret << m_descricao;
        strret << " -> Valor: R$ ";
        strret << setprecision(2) << fixed << m_valor;
    }

    return strret.str();
}

string IngressoVip::GetInformacao()
{
    stringstream strret;

    if(m_descricao == "")
    {
        strret << "Descricao nao disponivel";
    }
    else
    {
        strret << "Descricao do Ingresso Plus: ";
        strret << m_descricao;
        strret << " -> Valor: R$ ";
        strret << setprecision(2) << fixed << m_valor;
        strret << " -> Valor Adicional " << m_valorPlus;
        strret << " -> Valor Total: " << m_valor+m_valorPlus;
        strret << endl;
    }

    return strret.str();
}
