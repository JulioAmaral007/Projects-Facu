#include "client.hpp"
#include "account.hpp"
#include "saccount.hpp"

int main()
{
    Client c1("Jose da Silva");
    Client c2("Ricardo Pereira", "Vendedor", 3000);
    Client* c3 = new Client("Jonas Oliveira", "Motorista", 4000);

    Account Acc1;
    Account Acc2(&c1, 1000);
    Account Acc3(&c1, 2000);
    Account Acc4(&c2, 5000);
    Account Acc5(c3, 10000);

    Saccount Acc6(c3, 0, 10000);
    //SAccount Acc7(new Client("Pedro","Baterista",6000), 10000);
    Saccount Acc7(&c1);


    cout << Acc1.GetInformation() << endl;
    cout << Acc2.GetInformation() << endl;
    cout << Acc3.GetInformation() << endl;
    cout << Acc4.GetInformation() << endl;
    cout << Acc5.GetInformation() << endl;
    cout << Acc6.GetInformation() << endl;
    cout << Acc7.GetInformation() << endl;

    Acc6.Transfer(5000, Acc3);
    Acc6.Transfer(5000, Acc7);



    /*
    Acc1 -= 500; *

    Acc1.Transfer(500, Acc3);
    Acc1.Deposit(600);
    Acc1 += 500; *

    Acc5.ChangeClient(&c1);
    Acc5 >> &c1; *
    */

    delete c3;

    return 0;
}
