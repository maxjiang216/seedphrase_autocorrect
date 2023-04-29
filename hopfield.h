// Hopfield Network for remembering a list of strings

#ifndef HOPFIELD_H
#define HOPFIELD_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Hopfield {

private:
    vector<vector<double>> weights;

    static void decode(char c, bool *bits);

  public:
    Hopfield(const vector<string> &patterns);
    ~Hopfield() = default;

    string recall(const string &pattern) const;
};

#endif