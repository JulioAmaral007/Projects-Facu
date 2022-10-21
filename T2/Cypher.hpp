#ifndef CYPHER_HPP
#define CYPHER_HPP
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class ConversionTable
{
    private:
    vector<pai  qr<char, char>> tableConversion;

    public:


    ConversionTable();

    void EncryptTableConversion(string *text);
    void GerTable(string *codAluno);

    void DecryptTableConversion(string *text);
};


class Cypher
{
    private:
    string *codigoAlun;
    string *m_text;
    ConversionTable table;

    public:
    Cypher();
    void CodigoTexts();
    void Encrypt();
    void Decrypt();
    ~Cypher();


};



#endif