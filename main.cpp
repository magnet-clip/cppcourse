#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
#include <set>

using namespace std;

//#define TEST
bool starts_with(const string &who, const string &what)
{
    if (who.length() <= what.length())
        return false;
    return who.find(what) == 0;
}

auto get_two_words(string str)
{
    auto pos1 = str.find_first_of(' ');
    auto pos2 = str.find_first_of(' ', pos1 + 1);

    auto word1 = str.substr(pos1 + 1, pos2 - pos1 - 1);
    auto word2 = str.substr(pos2 + 1);

    return make_tuple(word1, word2);
}

string get_second_string(const string &str)
{
    auto pos = str.find_first_of(' ');
    return str.substr(pos + 1);
}

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

auto synonims(const vector<string> &commands)
{
    vector<string> res;
    map<string, set<string>> dictionary;

    for (auto command : commands)
    {
        if (starts_with(command, "COUNT"))
        {
            // COUNT word
            auto word = get_second_string(command);
            // cout << "COUNT [" << word << "]" << endl;
            auto count = 0;
            if (dictionary.count(word))
            {
                count = dictionary[word].size();
            }
            res.push_back(to_string(count));
        }
        else if (starts_with(command, "ADD"))
        {
            // ADD word1 word2
            auto [word1, word2] = get_two_words(command);
            // cout << "ADD [" << word1 << "] [" << word2 << "]" << endl;
            if (dictionary.count(word1))
            {
                dictionary[word1].insert(word2);
            }
            else
            {
                dictionary[word1] = set<string>{word2};
            }

            if (dictionary.count(word2))
            {
                dictionary[word2].insert(word1);
            }
            else
            {
                dictionary[word2] = set<string>{word1};
            }
        }
        else if (starts_with(command, "CHECK"))
        {
            // CHECK word1 word2
            auto [word1, word2] = get_two_words(command);
            // cout << "CHECK [" << word1 << "] [" << word2 << "]" << endl;
            if (dictionary.count(word1))
            {
                if (dictionary[word1].count(word2))
                {
                    res.push_back("YES");
                }
                else
                {
                    res.push_back("NO");
                }
            }
            else
            {
                // cout << "NO" << endl;
                res.push_back("NO");
            }
        }
    }
    return res;
}

#ifdef TEST
template <typename T>
bool vectors_equal(const vector<T> &v1, const vector<T> &v2)
{
    if (v1.size() != v2.size())
    {
        // cout << "Sizes are different" << endl;
        return false;
    }
    for (int i = 0; i < v1.size(); i++)
    {
        if (v1[i] != v2[i])
        {
            // cout << "At index " << i << " " << v1[i] << " <> " << v2[i] << endl;
            return false;
        }
        else
        {
            // cout << "At index " << i << " " << v1[i] << " == " << v2[i] << endl;
        }
    }
    return true;
}

bool test_1()
{

    vector<string>
        commands{
            "ADD program code",
            "COUNT cipher",
            "ADD code cipher",
            "COUNT code",
            "COUNT program",
            "CHECK code program",
            "CHECK program cipher",
            "CHECK cpp java",
        };
    auto res = synonims(commands);
    vector<string> expected{
        "0",
        "2",
        "1",
        "YES",
        "NO",
        "NO",
    };
    return vectors_equal(res, expected);
}

#else
int run()
{

    int num;
    cin >> num;
    cin >> ws;
    vector<string> commands(num);
    for (auto &command : commands)
    {
        getline(cin, command);
    }
    auto result = synonims(commands);
    for (auto item : result)
    {
        cout << item << endl;
    }
    return 0;
}
#endif

int main()
{
#ifdef TEST
    if (!test_1())
    {
        cout << "TEST 1 FAIL!" << endl;
        return -1;
    }
    else
    {
        cout << "Test 1 OK!" << endl;
    }

    cout << "OK!" << endl;
    return 0;
#else
    return run();
#endif
}