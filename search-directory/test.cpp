#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;
using std::filesystem::directory_iterator;
using std::filesystem::is_directory;

// void fileSearch(string, &ofstream);

vector<string> allPath;
string fileName = "class_field_methods.txt";


void fileSearch(string path, ofstream &wfile) {
    vector<string> currentPath;

    for (const auto& file : directory_iterator(path)) {
        string tmp = file.path();
        cout << tmp << endl;
        currentPath.push_back(tmp);
    }
    sort(currentPath.begin(), currentPath.end());
    for (int i = 0; i < currentPath.size(); i++) {
        string tmp = currentPath[i];
        allPath.push_back(tmp);
        if (tmp.substr(tmp.length()-4, tmp.length()) == ".cpp") {
            cout << "cpp file: "+tmp << endl;
            wfile << "cpp file: "+tmp <<endl;
            fstream mf;
            mf.open(tmp, ios::in);
            if (mf.is_open()) {
                string line;
                while (getline(mf, line)) {
                    if (!(line == "" || line.at(0) == ' ' || line.at(0) == '{' || line.at(0) == '}'))
                        wfile << line << endl;
                }
                wfile << endl;
                mf.close();
            }
        }
        if (is_directory(tmp)) fileSearch(tmp, wfile);
    }
}


int main() {
    ofstream wfile;
    wfile.open(fileName, ios::out);

    string input = "";
    cin >> input;
    allPath.push_back(input);
    fileSearch(input, wfile);
    for (int i = 0; i < allPath.size(); i++)
        cout << allPath[i] << endl;
    wfile.close();
    return 0;
}


