
#include "Cypher.hpp"

int main()
{
    Cypher *cy1=new Cypher();
    while(true)
    {
        cout<<"-------------------------------------------------"<<endl;
        cout<<"CYPHER"<<endl;
        cout<<"Select an option:"<<endl;
        cout<<"1. Insert Text"<<endl;
        cout<<"2. Generate ConversionTable"<<endl;
        cout<<"3. Encrypt Text"<<endl;
        cout<<"4. Decrypt Text"<<endl;
        cout<<"5. Exit"<<endl;
        cout<<"-------------------------------------------------"<<endl;
        cout<<"Option:"<<endl;

        int ch;
        cin>>ch;

        if(ch==1)
        {
            cy1->Text();
        }
        if(ch==2)
        {
            cy1->CodigoAluno();
        }
        if(ch==3)
        {
            cy1->Encrypt();
        }
        if(ch==4)
        {
            cy1->Decrypt();
        }
        if(ch==5)
        {
            delete(cy1);
            break; 
        }
    }
    return 0;
    
}