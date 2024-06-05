#include <iostream>
#include <string>
#include <fstream>
#include "Header1.h"

using namespace std;

void writeToFile(const string& filename, const string& text) {
    ofstream file(filename);
    if (file.is_open()) {
        file << text;
        file.close();
    }
    else {
        throw logic_error("Невозможно записать данные в файл: " + filename);
    }
}

string readFromFile(const string& filename) {
    ifstream file(filename);
    string content;
    if (file.is_open()) {
        string line;
        while (getline(file, line))
        {
            content += line + "\n";
        }
        file.close();
        return content;
    }
    else {
        throw logic_error("Невозможно прочитать файл: " + filename);
    }
}