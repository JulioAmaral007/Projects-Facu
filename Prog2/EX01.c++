#include <iostream>
#include <vector>

using namespace std;

//prototypes
void InsertWord(vector<string> &localList);
void PrintWords(const vector<string> &localList);
bool SearchWord(const vector<string> &localList);
bool RemoveWordByIndex(vector<string> &localList);
vector<size_t> SearchSubstring(const vector<string> &localList);
bool RemoveSubstrings(vector<string> &localList);


int main()
{
    vector<string> ListOfWords;

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
            PrintWords(ListOfWords);
            continue;
        }

        if(ch == '3')
        {
            SearchWord(ListOfWords);
            continue;
        }
        if(ch == '4')
        {
            vector<size_t> indexes = SearchSubstring(ListOfWords);
            if(indexes.size() == 0)
                cout << "Substring not found" << endl;

            continue;
        }
        if(ch == '5')
        {
            RemoveWordByIndex(ListOfWords);
            continue;
        }
        if(ch == '6')
        {
            RemoveSubstrings(ListOfWords);
            continue;
        }
        if(ch == '0')
        {
            break;
        }
    }
    return 0;
}

//passagem por referencia para atualizaçao / remoçao
void InsertWord(vector<string> &localList)
{
    cout << "Insert a word: ";
    string str;
    cin >> str;
    localList.push_back(str);
}

//passagem por referencia para consulta (sem copia)
void PrintWords(const vector<string> &localList)
{
    cout << "Print list of words" << endl;
    cout << "List of words has " << localList.size() << endl;

    //for(int i=0; i<list.size(); i++)
    for(size_t i=0; i<localList.size(); i++)
    {
        cout << "  Index " << i << " -> " << localList.at(i) << endl;
    }
}

bool SearchWord(const vector<string> &localList)
{
    cout << "Enter with a word to search: ";
    string query;
    cin >> query;

    for(size_t i=0; i<localList.size(); i++)
    {
        if(localList.at(i) == query)
        {
            cout << "-> Word " << query << " has found at position " << i << endl;
            return true;
        }
    }
    return false;
}

bool RemoveWordByIndex(vector<string> &localList)
{
    cout << "Enter with an index to remove: ";
    int index;
    cin >> index;

    if(index >= 0 && index < localList.size())
    {
        localList.erase(localList.begin()+index);
        return true;
    }
    else
    {
        cout << "Idiot !!!!, Invalid Index !" << endl;
        return false;
    }
}

vector<size_t> SearchSubstring(const vector<string> &localList)
{
    cout << "Enter with a substring to search: ";
    string str;
    cin >> str;

    cout << "Searching for substring: " << str << endl;
    vector<size_t> indexes;
    for(size_t i=0; i< localList.size(); i++)
    {
        size_t position = localList.at(i).find(str);

        if(position < localList.at(i).size())
        {
            indexes.push_back(i);
            cout << " Substring has found : " << localList.at(i) << endl;
        }
    }
    return indexes;
}

bool RemoveSubstrings(vector<string> &localList)
{
    cout << "Enter with a substring to search: ";
    string str;
    cin >> str;

    cout << "Searching for substring to removal: " << str << endl;

    bool firstremoval = false;
    size_t i=0;
    while(i<localList.size())
    {
        size_t position = localList.at(i).find(str);

        if(position < localList.at(i).size())
        {
            cout << " Substring has found, removing it: " << localList.at(i) << endl;
            localList.erase(localList.begin()+i);
            firstremoval = true;
        }
        else
        {
            i++;
        }
    }
    return firstremoval;
}




