#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "blocks.h"

using json = nlohmann::json;
using namespace std;

void replaceChar(string &s) {
    for (char &c : s) {
        if (c == ' ') {
            c = '0';
        } else {
          c = '1';
        }
    }
}


int main(int argc, char* argv[]) {
    if (argc < 2 || (argc == 3) || argc > 4 || (argc == 4 && string(argv[2]) != "-o")) {
        cout << "Usage:\t" << argv[0] << " <file in>\n\t" << argv[0] << " <file in> -o <file out>" << endl;
        return 1;
    }

    string fin = argv[1];
    string fout = "tmp_bin";
    if (argc == 4) {
        fout = argv[3];
    }

    map<string, string> dataMap;

    try {
        json data = json::parse(blocks);
        for (auto& el : data.items()) {
            dataMap[el.value()] = el.key();
        }
    } catch (const json::parse_error& e) { 
        cerr << "JSON Parsing failed: " << e.what() << endl;
        return 2;
    }

    ifstream in(fin);
    if (!in.is_open()) {
        cerr << "Could not open input file." << endl;
        return 3;
    }
    
    ofstream out(fout + ".c");

    string line;
    string arr[5];
    size_t lineCount = 0;

    while (getline(in, line)) {
        arr[lineCount % 5] = line;
        // works with 5 lines at a time
        if (lineCount % 5 == 4) {
            size_t numChars = arr[0].length() / 5;
            
            // for each collumn
            for (size_t j = 0; j < numChars; j++) {
                string code = "";
                for (int row = 0; row < 5; row++) {
                    code.append(arr[row].substr(j * 5, 5));
                }
                replaceChar(code);
                if (dataMap.count(code)) {
                    out << dataMap[code];
                } else {
                    out << " "; 
                }
            }
            out << endl;
        }
        lineCount++;
    }

    out.close();
    in.close();

    string compileCmd = "gcc " + fout + ".c -o " + fout;
    if (system(compileCmd.c_str()) == 0) {
        system(("rm " + fout + ".c").c_str());
        
        if (argc == 2) {
            system(("./" + fout).c_str());
            system(("rm " + fout).c_str());
        }
    } else {
        cerr << "Compilation failed." << endl;
    }

    return 0;
}
