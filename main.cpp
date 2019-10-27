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

int main()
{
    string str;
    cin >> str;
    cout << IsPalindrom(str);
    return 0;
}