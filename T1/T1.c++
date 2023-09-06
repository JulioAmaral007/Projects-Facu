#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void AddFile(string filename, vector<pair<string, vector<string>>> &ListaDeArquivos);
void RecordFile(string filename,vector<pair<string, vector<string>>> &ListaDeArquivos);
vector<pair<string, vector<string>>> SearchSubstring(string busca, const vector<pair<string, vector<string>>> &ListaDeArquivos);
void RemoveSubstrings(vector<pair<string, vector<string>>> &ListaDeArquivos, string busca);
void RemoveRepetedWords(vector<pair<string, vector<string>>> &ListaDeArquivos);
void ShowStatistics(const vector<pair<string, vector<string>>> &ListaDeArquivos);
bool SaveDatabase(string filename, const vector<pair<string, vector<string>>> &ListaDeArquivos);

int main() {

  vector<pair<string, vector<string>>> ListOfFiles;

  while (true) {
    cout << "-------------------------------------------------" << endl;
    cout << "FILE MANIPULATOR HACK" << endl;
    cout << "Select an option:" << endl;
    cout << "1. Open a File..." << endl;
    cout << "2. Search for Substrings..." << endl;
    cout << "3. Remove Words Containing a Substring" << endl;
    cout << "4. Remove all Repeated Words" << endl;
    cout << "5. Show Statistics" << endl;
    cout << "6. Exit" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "Option:" << endl;
    int ch;
    cin >> ch;

    if (ch == 1) {
      cout << "Enter with a file to open: ";
      string user_filename;
      cin >> user_filename;
      AddFile(user_filename, ListOfFiles);
    }
    if (ch == 2) {
      cout << "Enter a substring to search: ";
      string busca;
      cin >> busca;
      vector<pair<string, vector<string>>> Substrings =
          SearchSubstring(busca, ListOfFiles);
      for (int i = 0; i < Substrings.size(); i++) {
        for (int j = 0; j < Substrings.at(i).second.size(); j++) {
          cout << Substrings.at(i).first << " has substring "
               << "\"" << busca << "\": " << Substrings.at(i).second.at(j)
               << endl;
        }
      }
    }
    if (ch == 3) {
      cout << "Enter a substring to remove all occurrences: ";
      string busca;
      cin >> busca;
      RemoveSubstrings(ListOfFiles, busca);
    }
    if (ch == 4) {
      RemoveRepetedWords(ListOfFiles);
    }
    if (ch == 5) {
      ShowStatistics(ListOfFiles);
    }
    if (ch == 6) {
      SaveDatabase("concatenation.txt", ListOfFiles);
      break;
    }
  }
}

void RecordFile(string filename,
                vector<pair<string, vector<string>>> &ListaDeArquivos) {
  ifstream filereader(filename);
  if (filereader.is_open()) {
    string tmp;
    while (getline(filereader, tmp)) {
      ListaDeArquivos.at(ListaDeArquivos.size() - 1).second.push_back(tmp);
    }
    filereader.close();
  } else {
    cout << "File could not be found. Creating a new one." << endl;
    ofstream out(filename);
    out.open(filename);
    out.close();
  }
}

void AddFile(string filename,
             vector<pair<string, vector<string>>> &ListaDeArquivos) {
  for (size_t i = 0; i < ListaDeArquivos.size(); i++) {
    if (ListaDeArquivos.at(i).first == filename) {
      cout << "File already opened." << endl;
      return;
    }
  }
  vector<string> file_vector;
  pair<string, vector<string>> file_pair;
  file_pair.first = filename;
  file_pair.second = file_vector;
  ListaDeArquivos.push_back(file_pair);
  RecordFile(filename, ListaDeArquivos);
}

vector<pair<string, vector<string>>>
SearchSubstring(string busca,
                const vector<pair<string, vector<string>>> &ListaDeArquivos) {
  vector<pair<string, vector<string>>> cadeiasSubstring;
  for (int i = 0; i < ListaDeArquivos.size();
       i++) // Read al the pairs in the vector
  {
    pair<string, vector<string>> sub_pair;
    vector<string> sub_vector;
    sub_pair.second = sub_vector;
    sub_pair.first = ListaDeArquivos.at(i).first;
    for (int j = 0; j < ListaDeArquivos.at(i).second.size();
         j++) // Read all the string vectors in the primary vector
    {
      string cadeia = ListaDeArquivos.at(i).second.at(j);
      int pos = cadeia.find(busca);
      if (pos < cadeia.size()) {
        sub_pair.second.push_back(cadeia);
      }
    }
    if (sub_pair.second.empty() == false) {
      cadeiasSubstring.push_back(sub_pair);
    }
  }
  return cadeiasSubstring;
}

void RemoveSubstrings(vector<pair<string, vector<string>>> &ListaDeArquivos,
                      string busca) {
  for (size_t i = 0; i < ListaDeArquivos.size(); i++) {
    for (size_t j = 0; j < ListaDeArquivos.at(i).second.size(); j++) {
      string cadeia = ListaDeArquivos.at(i).second.at(j);
      size_t pos = cadeia.find(busca);
      if (pos < cadeia.size()) {
        ListaDeArquivos.at(i).second.erase(
            ListaDeArquivos.at(i).second.begin() + j);
      }
    }
  }
}

void RemoveRepetedWords(vector<pair<string, vector<string>>> &ListaDeArquivos) {
  for (int i = 0; i < ListaDeArquivos.size(); i++) // read all the pairs i
  {
    bool condition = false;
    int cont = 0;
    for (int j = 0; j < ListaDeArquivos.at(i).second.size();
         j++) // read all the words inside pair i
    {
      string cadeia = ListaDeArquivos.at(i).second.at(j);
      vector<string>::iterator indice;
      vector<string>::iterator it;
      if (condition == true) {
        do {
          vector<string>::iterator it =
              find(indice, ListaDeArquivos.at(i).second.end(), cadeia);
          vector<string>::iterator indice = it;
          ListaDeArquivos.at(i).second.erase(it);
          j--;
        } while (it < ListaDeArquivos.at(i).second.end());
      }
      if (condition == false) {
        vector<string>::iterator indice =
            find(ListaDeArquivos.at(i).second.begin(),
                 ListaDeArquivos.at(i).second.end(), cadeia);
        condition = true;
      }
    }
  }
}

void ShowStatistics(
    const vector<pair<string, vector<string>>> &ListaDeArquivos) {

  int soma = 0;
  cout << "File Manipulator Hack Statistics:"
       << "\n";
  for (int i = 0; i < ListaDeArquivos.size();
       i++) // Read al the pairs in the vector
  {
    cout << ListaDeArquivos.at(i).first << " has ";
    int soma = 0;
    for (int j = 0; j < ListaDeArquivos.at(i).second.size();
         j++) // Read all the string vectors in the primary vector
    {
      soma++;
    }
    cout << soma << " Words"
         << "\n";
  }
}

bool SaveDatabase(string filename,
                  const vector<pair<string, vector<string>>> &ListaDeArquivos) {
  ofstream filewritter(filename);
  if (filewritter.is_open()) {
    for (int i = 0; i < ListaDeArquivos.size();
         i++) // Read al the pairs in the vector
    {

      filewritter << ListaDeArquivos.at(i).first << "\n";

      for (int j = 0; j < ListaDeArquivos.at(i).second.size();
           j++) // Read all the string vectors in the primary vector
      {
        filewritter << ListaDeArquivos.at(i).second.at(j) << endl;
        cout << "\n";
      }
    }
    return true;
    filewritter.close();
  } else {
    cout << "Error, unable to create a file" << endl;
    return false;
  }
}