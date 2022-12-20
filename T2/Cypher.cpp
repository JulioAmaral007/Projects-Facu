#include "Cypher.hpp"

Cypher::Cypher()
{
    this->codigoAlun = NULL;
    this->m_text = NULL;
}

void Cypher::CodigoTexts()
{
    this->codigoAlun = NULL;
    string codA;
    cout << "Digite o Codigo do Aluno: ";
    cin >> codA;
    this->codigoAlun = new string(codA);
    this->table.GerTable(this->codigoAlun);

    this->m_text = NULL;
    string text;
    char c;
    cout << "Digite o texto a ser encrypted/decrypted: ";
    cin.get(c);
    while (cin.get(c) && c != '\n')
    {
        text += c;
    }
    this->m_text = new string(text);
}

void Cypher::Encrypt()
{
    if (this->m_text == NULL || this->codigoAlun == NULL)
    {
        cout << "Insira o texto ou o codigo do aluno primeiro." << endl;
        return;
    }
    this->table.EncryptTableConversion(this->m_text);
}

void Cypher::Decrypt()
{
    if (this->m_text == NULL || this->codigoAlun == NULL)
    {
        cout << "Insira o texto ou o codigo do aluno primeiro." << endl;
        return;
    }
    this->table.DecryptTableConversion(this->m_text);
}

Cypher::~Cypher()
{
    cout << "Finalizado." << endl;
    delete (this->codigoAlun);
    delete (this->m_text);
}

ConversionTable::ConversionTable()
{
}

void ConversionTable::GerTable(string *codAluno)
{
    if (this->tableConversion.empty() == false)
    {
        this->tableConversion.clear();
    }
    int soma = 0;
    for (size_t i = 0; i < codAluno->size(); i++)
    {
        soma = soma + int(codAluno->at(i) - '0');
    }
    for (size_t i = 0; i < 256; i++)
    {
        pair<char, char> p;
        p.first = i;
        p.second = p.first + soma + soma;
        this->tableConversion.push_back(p);
    }
}

void ConversionTable::EncryptTableConversion(string *text)
{
    string *result = new string("");

    for (size_t i = 0; i < text->size(); i++)
    {
        char chi = text->at(i);
        char cho = this->tableConversion.at(chi).second;
        *result += cho;
    }
    *text = *result;
    cout << "Encrypted text: " << *text << endl;
    delete (result);
}

void ConversionTable::DecryptTableConversion(string *text)
{
    string *result = new string("");

    for (size_t i = 0; i < text->size(); i++)
    {
        char chi = text->at(i);
        for (size_t j = 0; j < this->tableConversion.size(); j++)
        {
            if (chi == this->tableConversion.at(j).second)
            {
                *result += this->tableConversion.at(j).first;
                break;
            }
        }
    }
    *text = *result;
    cout << "Decrypted text: " << *text << endl;
    delete (result);
}
