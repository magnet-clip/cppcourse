#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
#include <set>

using namespace std;

string join_vector(const vector<int> &items, string delimiter)
{
    string res;
    if (items.size() == 0)
    {
        return "";
    }

    if (items.size() == 1)
    {
        return to_string(items[0]);
    }

    for (auto i = 0; i < items.size() - 1; i++)
    {
        res += to_string(items[i]) + delimiter;
    }

    res += to_string(items[items.size() - 1]);
    return res;
}

int run()
{

    int len;
    cin >> len;
    vector<int> numbers(len, 0);
    for (auto &num : numbers)
    {
        cin >> num;
    }
    sort(numbers.begin(), numbers.end(), [](const int &a, const int &b) { return abs(a) < abs(b); });
    cout << join_vector(numbers, " ");
    return 0;
}

int main()
{

    return run();
}