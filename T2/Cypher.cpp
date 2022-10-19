#include "Cypher.hpp"

Cypher::Cypher()
{
    this->m_codigo_aluno=NULL;
    this->m_text=NULL;
}

void Cypher::CodigoAluno()
{
    this->m_codigo_aluno=NULL;
    string codigo;
    cout<<"Insert student number: ";
    cin>>codigo;
    this->m_codigo_aluno=new string(codigo);
    this->m_Tabela.GeraTabela(this->m_codigo_aluno);

}

void Cypher::Text()
{
    this->m_text=NULL;
    string text;
    char c;
    cout<<"Type string or text you want encrypted/decrypted: ";
    cin.get(c);
    while(cin.get(c) && c!='\n')
    {
        text+=c;
    }
    this->m_text=new string(text);
    cout<<"This is my string: "<<*m_text<<endl;
    cout<<"String size: "<<m_text->size()<<endl;

}

void Cypher::Encrypt()
{
    if(this->m_text==NULL || this->m_codigo_aluno==NULL)
    {
        cout<<"Please insert a text/student number first."<<endl;
        return;
    }
    this->m_Tabela.EncryptTable(this->m_text);
}

void Cypher::Decrypt()
{
    if(this->m_text==NULL || this->m_codigo_aluno==NULL)
    {
        cout<<"Please insert a text/student number first."<<endl;
        return;
    }
    this->m_Tabela.DecryptTable(this->m_text);
}

Cypher::~Cypher()
{
    cout<<"Worked."<<endl;
    delete(this->m_codigo_aluno);
    delete(this->m_text);
}


ConversionTable::ConversionTable()
{

}

void ConversionTable::GeraTabela(string *codigo_aluno)
{
    if(this->m_TabelaConversao.empty()==false)
    {
        this->m_TabelaConversao.clear();
    }
    int soma=0;
    for(size_t i=0;i<codigo_aluno->size();i++)
    {
        soma=soma+int(codigo_aluno->at(i)-'0');
    }
    for(size_t i=0; i<256; i++)
    {
        pair<char,char> p;
        p.first = i;
        p.second = p.first + soma;
        this->m_TabelaConversao.push_back(p);
    }

}

void ConversionTable::EncryptTable(string *text)
{
    cout<<"Foi"<<endl;
    string *result=new string("");

    for(size_t i=0;i<text->size();i++)
    {
        char chi=text->at(i);
        char cho=this->m_TabelaConversao.at(chi).second;
        *result+=cho;
    }
    *text=*result;
    cout<<"Encrypted text: "<<*text<<endl;
    delete(result);
}

void ConversionTable::DecryptTable(string *text)
{
    string *result=new string("");

    for(size_t i=0;i<text->size();i++)
    {
        char chi=text->at(i);
        for(size_t j=0;j<this->m_TabelaConversao.size();j++)
        {
            if(chi==this->m_TabelaConversao.at(j).second)
            {
                *result+=this->m_TabelaConversao.at(j).first;
                break;
            }
        }
    }
    *text=*result;
    cout<<"Decrypted text: "<<*text<<endl;
    delete(result);
}


