#include <iostream>
#include <vector>
using namespace std;

bool IsPalindrom(const string& str) {
    int pos_start = 0, pos_end = str.length() - 1;
    auto res = true;
    while ((pos_start < pos_end) && res) {
        res &= str[pos_start++] == str[pos_end--];
    }
    return res;
}

vector<string> PalindromFilter(const vector<string>& words, int minLength) {
    vector<string> res;
    for (auto word: words) {
        if (IsPalindrom(word) && word.length() >= minLength) {
            res.push_back(word);
        }
    }
    return res;
}

int main()
{
    string str;
    cin >> str;
    cout << IsPalindrom(str);
    return 0;
}