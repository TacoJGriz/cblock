#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using json = nlohmann::json;
using namespace std;

string toLowerCase(string str) {
  transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return tolower(c); });
  return str;
}

void replaceChar(string &s, char x, char y) {
    for (char &c : s) {
        if (c == x) {
            c = y;
        }
    }
}

int main(int argc, char* argv[]) {
  
  if (argc < 2 || argc > 4) {
    cout << "Usage: " << argv[0] << " <file in> opt:<file out> <json file>" << endl;
    return 1;
  }

  string fin = argv[1];
  string fout;

  if (argc == 2) {
    int index = fin.find('.');
    index = index == string::npos ? fin.length() : index;

    fout = fin.substr(0, index).append(".cblock"); 
  } else {
    fout = argv[2];
  }

  string jsonLoc = "blocks.json";
  if (argc == 4) {
    jsonLoc = argv[3];
  }

  ifstream jfile(jsonLoc);
  json j;
  jfile >> j;
  jfile.close();

  ofstream ofile(fout);
  ifstream ifile(fin);

  string line;

  while (getline(ifile, line)) {
    string arr[5] = {"", "", "", "", ""};
    //line = toLowerCase(line);

    for (char ch : line) {
      string charstr(1, ch);
      string jcode = j[charstr].get<string>();
      
      replaceChar(jcode, '0', ' ');
      replaceChar(jcode, '1', ch);

      for (size_t i = 0; i < 5; i++) {
        arr[i].append(jcode.substr(5*i, 5));
      }
    }
    for (const string &ln : arr) {
      ofile << ln << endl;
    }
  }

  ofile.close();
  ifile.close();

  return 0;
}
