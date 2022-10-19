#ifndef CYPHER_HPP
#define CYPHER_HPP
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class ConversionTable
{
    private:
    vector<pair<char, char>> m_TabelaConversao;

    public:

    //constructors
    ConversionTable();

    //setter
    void GeraTabela(string *codigo_aluno);
    void EncryptTable(string *text);
    void DecryptTable(string *text);
};


class Cypher
{
    private:
    string *m_codigo_aluno;
    string *m_text;
    ConversionTable m_Tabela;

    public:
    Cypher();
    void CodigoAluno();
    void Text();
    void Encrypt();
    void Decrypt();
    ~Cypher();


};



#endif