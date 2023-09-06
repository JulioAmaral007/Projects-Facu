#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

//prototype
void InsertWord(vector<string> &Lista);
void PrintList(const vector<string> &Lista);
bool SearchWord(const vector<string> &Lista);
bool RemoveWordByIndex(vector<string> &Lista);
vector<string> SearchSubstring(const vector<string> &Lista);
size_t RemoveSubstring(vector<string> &Lista);
bool SaveDatabase(string filename, const vector<string> &Lista);
bool LoadDatabase(string filename, vector<string> &Lista);


int main()
{
    vector<string> ListOfWords;
    if(LoadDatabase("database.txt", ListOfWords) == false)
    {
        cout << "Database file not found, creating a new one" << endl;
    }

    while(true) //main loop
    {
        cout << "--------------------------------------------------" << endl;
        cout << "UFxC String Store V.0" << endl;
        cout << "1. Insert string" << endl;
        cout << "2. Print index and string" << endl;
        cout << "3. Search string (literalpos)" << endl;
        cout << "4. Search substrings" << endl;
        cout << "5. Remove (by index)" << endl;
        cout << "6. Remove by substrings (all occurrences)" << endl;
        cout << "0. Quit" << endl;
        cout << "--------------------------------------------------" << endl << endl;

        cout << "Select an option: ";

        char ch;
        cin >> ch;

        //conditions or switch case
        if(ch == '1')
        {
            InsertWord(ListOfWords);
            continue;
        }
        if(ch == '2')
        {
            PrintList(ListOfWords);
            continue;
        }

        if(ch == '3')
        {
            SearchWord(ListOfWords);
            continue;
        }
        if(ch == '4')
        {
            vector<string> cadeias = SearchSubstring(ListOfWords);
            if(cadeias.size() == 0)
                cout << " Substring not found" << endl;
            else
            {
                cout << cadeias.size() << " Substrings were found" << endl;
                for(size_t i=0; i<cadeias.size(); i++)
                    cout << " -> " << cadeias.at(i) << endl;
            }

            continue;
        }
        if(ch == '5')
        {
            RemoveWordByIndex(ListOfWords);
            continue;
        }
        if(ch == '6')
        {
            size_t qtderemoved = RemoveSubstring(ListOfWords);
            cout << "Removed words: " << qtderemoved;
            continue;
        }
        if(ch == '0')
        {
            SaveDatabase("database.txt", ListOfWords);
            break;
        }

    }

    return 0;
}

//vector<string> &Lista -> evita copia, permitindo acesso ao endereço de memoria passado
void InsertWord(vector<string> &Lista)
{
    cout << "Enter with a word: ";
    string str;
    cin >> str;
    Lista.push_back(str);
}

//void PrintList(vector<string> Lista) //passagem por copia da variavel ListOfWords -> lista
void PrintList(const vector<string> &Lista) //passagem por referecia, evitando a copia, e com proteçao a alteraçao (read only)
{
    cout << "List of words" << endl;
    cout << "List has " << Lista.size() << " words" << endl;

    for(size_t i=0; i<Lista.size(); i++)
    {
        cout << " Index " << i << " -> " << Lista.at(i) << endl;
    }
}

bool SearchWord(const vector<string> &Lista)
{
    cout << "Enter with a word to search: ";
    string str;
    cin >> str;

    for(size_t i=0; i< Lista.size(); i++) //see iterator
    {
        if(Lista.at(i) == str)
        {
            cout << " String " << str << " was found at position " << i << endl;
            return true;
        }
    }
    cout << " String not found" << endl;
    return false;
}

bool RemoveWordByIndex(vector<string> &Lista)
{
    cout << "Enter with an index to remove: ";
    int index;
    cin >> index;

    if(index >= 0 && index < Lista.size())
    {
        Lista.erase(Lista.begin() + index);
        return true;
    }
    else
    {
        cout << "Idiot ! Index is invalid !!!" << endl;
        return false;
    }
}

vector<string> SearchSubstring(const vector<string> &Lista)
{
    cout << "Enter with a substring to search: ";
    string busca;
    cin >> busca;

    vector<string> cadeiasSubstring;
    for(size_t i=0; i<Lista.size(); i++)
    {
        string cadeia = Lista.at(i);
        size_t pos = cadeia.find(busca);
        if(pos < cadeia.size())
        {
            cadeiasSubstring.push_back(cadeia);
        }
    }
    return cadeiasSubstring;
}

//elimina todas as substrings a devolve a quantidade de palavras eliminadas
size_t RemoveSubstring(vector<string> &Lista)
{
    cout << "Enter with a substring to search: ";
    string busca;
    cin >> busca;

    size_t i=0;
    size_t removed=0;
    while(i<Lista.size())
    {
        string cadeia = Lista.at(i);
        size_t pos = cadeia.find(busca);
        if(pos < cadeia.size())
        {
            Lista.erase(Lista.begin() + i);
            removed++;
        }
        else
            i++;
    }
    return removed;
}

bool SaveDatabase(string filename, const vector<string> &Lista)
{
    ofstream filewritter(filename);
    if(filewritter.is_open())
    {
        for(size_t i=0; i<Lista.size(); i++)
            filewritter << Lista.at(i) << endl;

        filewritter.close();
        return true;
    }
    else
    {
        cout << "Error, unable to create a file" << endl;
        return false;
    }
}

bool LoadDatabase(string filename, vector<string> &Lista)
{
    ifstream filereader(filename);
    if(filereader.is_open())
    {
        string tmp;
        while(getline(filereader, tmp))
        {
            Lista.push_back(tmp);
        }
        filereader.close();
        return true;

    }
    else
        return false;
}       