#ifndef INGRESSO_HPP
#define INGRESSO_HPP

#include <iostream>

using namespace std;

class Ingresso
{
protected:
    string m_descricao;
    float m_valor;

public:
    Ingresso() : m_valor(0), m_descricao("") {};
    Ingresso(string desc, float v=10) : m_valor(v), m_descricao(desc) {};
    ~Ingresso() {};

    //getters and setters
    string GetDescricao() { return m_descricao; };
    float GetValor() { return m_valor; };

    string GetInformacao();

};

class IngressoVip : public Ingresso
{
protected:
    string m_descricaoPlus;
    float m_valorPlus;

public:
    //constructors and destructor
    IngressoVip() : Ingresso(), m_descricaoPlus(""), m_valorPlus(0) {};

    IngressoVip(string desc, string descPlus="", float valor=10, float adicional=5)
        : Ingresso(desc, valor),
        m_descricaoPlus(descPlus),
        m_valorPlus(adicional) {};

    ~IngressoVip() {};

    //Getters and setters
    float GetValor() { return m_valor+m_valorPlus; };

    string GetInformacao();

};



#endif

