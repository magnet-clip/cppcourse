#include <iostream>
#include <vector>
using namespace std;

int main()
{
    unsigned int num;
    cin >> num;

    vector<int> converted;
    unsigned int div, mod;
    do {
        div = num / 2;
        mod = num % 2;
        //cout << "Div: " << div << "; mod: " << mod << "\r\n";
        converted.push_back(mod);

        num = div;
    } while (div != 0); 

    for (auto it = converted.rbegin(); it != converted.rend(); it++) {
        cout << *it;
    }

    return 0;
}