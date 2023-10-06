#include <iostream>
#include <vector>
#include <utility>

using namespace std;

vector< pair< char, char > > CreateConvTable(int disp);
string EncryptText(string input, vector< pair<char,char>> table);
string DecryptText(string input, vector< pair<char,char>> table);

int main()
{
    string input = "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

    //create a convertion table
    vector< pair<char,char >> convTable;
    convTable = CreateConvTable(10);

    for(size_t i=0; i<convTable.size(); i++)
    {
        char orig = convTable.at(i).first;
        char dest = convTable.at(i).second;

        cout << " Orig: " << (char) orig << " - " << (int) orig << " -> " <<
        " Destino: " << (char) dest << " - " << (int) dest << endl;
    }

    string encrypted;
    encrypted = EncryptText(input, convTable);
    cout << "Original text: "  << input << endl;
    cout << "--------------------------------" << endl;
    cout << "Encrypted text: " << encrypted << endl;


    string decrypted;
    decrypted = DecryptText(encrypted, convTable);
    cout << "--------------------------------" << endl;
    cout << "Reverted text: "  << decrypted << endl;

    return 0;
}

string EncryptText(string input, vector< pair<char,char>> table)
{
    string result;

    for(size_t i=0; i<input.length(); i++)
    {
        char chi = input.at(i); //input character
        char cho = table.at(chi).second;  //output character
        result += cho;
    }
    return result;
}

string DecryptText(string input, vector< pair<char,char>> table)
{
    string result;

    for(size_t i=0; i<input.length(); i++)
    {
        char chi = input.at(i); //input character

        for(size_t j=0; j<table.size(); j++)
        {
            if(chi == table.at(j).second)
            {
                result += table.at(j).first;
                break;
            }
        }
    }
    return result;
}

vector< pair<char,char >> CreateConvTable(int disp)
{
    //vector< pair<char,char >> table(256); //preinitialize, w/o push_back
    vector< pair<char,char >> table;
    for(size_t i=0; i<256; i++)
    {
        //pair<char,char> p(i, ' ');  //avoiding first and second indexes
        pair<char,char> p;
        p.first = i;
        p.second = p.first + disp;
        table.push_back(p);
    }

    return table;
}