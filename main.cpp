#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
#include <set>

using namespace std;

string join_vector(const vector<string> &items, string delimiter)
{
    string res;
    if (items.size() == 0)
    {
        return "";
    }

    if (items.size() == 1)
    {
        return items[0];
    }

    for (auto i = 0; i < items.size() - 1; i++)
    {
        res += items[i] + delimiter;
    }

    res += items[items.size() - 1];
    return res;
}

string tolower_str(const string &str)
{
    auto res = str;
    transform(res.begin(), res.end(), res.begin(), ::tolower);
    return res;
}

int run()
{

    int len;
    cin >> len;
    vector<string> strings(len, "");
    for (auto &str : strings)
    {
        cin >> str;
    }
    sort(strings.begin(), strings.end(), [](const string &a, const string &b) { return tolower_str(a) < tolower_str(b); });
    cout << join_vector(strings, " ");
    return 0;
}

int main()
{

    return run();
}