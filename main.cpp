#include <iostream>
using namespace std;


int main() {
    int s;
    cin >> s;

    auto single_f = false;
    auto double_f = false;

    auto res = -2;

    for (auto i = 0; i < s.length(); i++) {
        if (s[i] == 'f') {
            if (double_f) { // f occurred twice
                // do nothing, everything's done
            } else if (single_f) { // one f already found 
                double_f = true;
                res = i;
            } else { // it's the first f we found here
                single_f = true;
                res = -1;
            }
        }
    }

    cout << res;
    return 0; 
}