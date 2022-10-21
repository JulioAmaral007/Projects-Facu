#include "Cypher.hpp"

int main()
{
    Cypher *cypher=new Cypher();
    while(true)
    {
        cout<<"CYPHER"<<endl;
        cout<<"Select an option:"<<endl;
        cout<<"1. Geração da Tabela e digitação do Texto"<<endl;
        cout<<"2. Encrypt"<<endl;
        cout<<"3. Decrypt"<<endl;
        cout<<"4. Finalizar"<<endl;
        cout<<"Option:"<<endl;

        int c;
        cin>>c;

        if(c==1)
        {
            cypher->CodigoTexts();
        }
        if(c==2)
        {
            cypher->Encrypt();
        }
        if(c==3)
        {
            cypher->Decrypt();
        }
        if(c==4)
        {
            delete(cypher);
            break; 
        }
    }
    return 0;
    
}