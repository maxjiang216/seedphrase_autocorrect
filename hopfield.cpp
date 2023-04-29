#include "hopfield.h"
#include <cstring>
#include <iostream>

using std::string;
using std::vector;
using namespace std;

Hopfield::Hopfield(const vector<string> &patterns) {
    int n = 0;
    for (int i = 0; i < patterns.size(); i++) {
        if (patterns[i].length() * 5 > n) n = patterns[i].length() * 5;
    }
    bool bit_patterns[patterns.size()][n];
    for (int i = 0; i < patterns.size(); ++i) {
        for (int j = 0; j < patterns[i].length(); ++j) {
            decode(patterns[i][j], bit_patterns[i] + j * 5);
        }
        for (int j = patterns[i].length() * 5; j < n; ++j) {
            bit_patterns[i][j] = false;
        }
    }
    weights = vector<vector<double>>(n, vector<double>(n, 0.0));
    for (int i = 0; i < patterns.size(); ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                weights[j][k] += (bit_patterns[i][j] == bit_patterns[i][k]) ? 1.0 : -1.0;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            weights[i][j] /= patterns.size();
            weights[j][i] = weights[i][j];
        }
    }
}

void Hopfield::decode(char c, bool *bits) {

    // Convert the character to lowercase
    c = std::tolower(c);
    // Convert the lowercase character to an integer from 1 to 26
    int index = c - 'a' + 1;
    if (index < 0 || index > 25) {
        // If the character is not a letter, set all bits to 0
        for (int i = 0; i < 5; ++i) {
            bits[i] = false;
        }
        return;
    }
    // Convert the integer to a 5-bit pattern
    for (int i = 0; i < 5; ++i) {
        bits[i] = (index & (1 << i)) != 0;
    }
}

string Hopfield::recall(const string &pattern) const {
    int n = pattern.length() * 5;
    bool bits[n];
    for (int i = 0; i < pattern.length(); ++i) {
        decode(pattern[i], bits + i * 5);
    }
    bool old_bits[n];
    do {
        for (int i = 0; i < n; ++i) {
            old_bits[i] = bits[i];
        }
        for (int i = 0; i < n; ++i) {
            double sum = 0.0;
            for (int j = 0; j < n; ++j) {
                sum += weights[i][j] * (bits[j] ? 1.0 : -1.0);
            }
            bits[i] = sum >= 0.0;
        }
        string result;
        for (int i = 0; i < n; i += 5) {
            int index = 0;
            for (int j = 0; j < 5; ++j) {
                index |= bits[i + j] ? (1 << j) : 0;
            }
            result += 'a' + index - 1;
        }
    } while (memcmp(bits, old_bits, n * sizeof(bool)) != 0);
    string result;
    for (int i = 0; i < n; i += 5) {
        int index = 0;
        for (int j = 0; j < 5; ++j) {
            index |= bits[i + j] ? (1 << j) : 0;
        }
        result += 'a' + index - 1;
    }
    return result;
}