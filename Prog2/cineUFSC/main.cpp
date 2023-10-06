#include "ingresso.hpp"

int main()
{
    Ingresso i1;
    Ingresso i2("A bela e a fera");
    Ingresso i3("Scary movie", 60);

    IngressoVip i4("O Atirador");
    IngressoVip i5("American Pie", "Pipoca, Refri", 50, 10);

    cout << i1.GetInformacao() << endl;
    cout << i2.GetInformacao() << endl;
    cout << i3.GetInformacao() << endl;

    cout << i4.GetInformacao() << endl;
    cout << i5.GetInformacao() << endl;

    return 0;
};
