#include "hopfield.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<string> patterns = {};
    ifstream file("bip39.txt");
    string line;
    while (getline(file, line)) {
        patterns.push_back(line);
    }
    Hopfield hopfield(patterns);
    string pattern;
    while (getline(cin, pattern)) {
        cout << hopfield.recall(pattern) << endl;
    }
}