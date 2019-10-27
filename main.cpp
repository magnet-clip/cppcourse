#include <iostream>
using namespace std;

inline int min(int a, int b)
{
    return a < b ? a : b;
}

inline int max(int a, int b)
{
    return a < b ? b : a;
}

int main()
{
    unsigned int n1, n2;
    cin >> n1 >> n2;

    unsigned int smallest = min(n1, n2);
    unsigned int largest = max(n1, n2);

    if (smallest == 0 || smallest == 1)
    {
        cout << 1;
        return 0;
    }

    while (smallest != 0)
    {
        unsigned int m = largest % smallest;
        // cout << "Remainder of " << largest << " and " << smallest << " is " << m << "\n";
        largest = smallest;
        smallest = m;
    }
    cout << largest;
    return 0;
}