#include <iostream>
#include <vector>
#include <map>

using namespace std;

//#define TEST

auto anagram(const vector<string> &word_pairs)
{
    vector<string> res;

    for (auto words : word_pairs)
    {
        auto space_pos = words.find_first_of(' ');
        auto first_word = words.substr(0, space_pos);
        auto second_word = words.substr(space_pos + 1);
        // cout << "[" << first_word << "] vs [" << second_word << "]" << endl;
        if (first_word.length() != second_word.length())
        {
            res.push_back("NO");
        }
        else
        {
            map<char, int> first_word_chars;
            map<char, int> second_word_chars;
            for (auto i = 0; i < first_word.length(); i++)
            {
                first_word_chars[first_word[i]]++;
                second_word_chars[second_word[i]]++;
            }
            res.push_back(first_word_chars == second_word_chars ? "YES" : "NO");
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
        cout << "Sizes are different" << endl;
        return false;
    }
    for (int i = 0; i < v1.size(); i++)
    {
        if (v1[i] != v2[i])
        {
            cout << v1[i] << " <> " << v2[i] << endl;
            return false;
        }
    }
    return true;
}

bool test_1()
{

    vector<string>
        commands{
            "ADD 5 Salary",
            "ADD 31 Walk",
            "ADD 30 WalkPreparations",
            "NEXT",
            "DUMP 5 ",
            "DUMP 28 ",
            "NEXT",
            "DUMP 31",
            "DUMP 30 ",
            "DUMP 28 ",
            "ADD 28 Payment",
            "DUMP 28",
        };
    auto res = todo(commands);
    vector<string> expected{
        "1 Salary ",
        "2 Walk WalkPreparations ",
        "0 ",
        "0 ",
        "2 Walk WalkPreparations ",
        "3 Walk WalkPreparations Payment "};
    return vectors_equal(res, expected);
}

bool test_2()
{

    vector<string>
        commands{
            "ADD 31 Jan",
            "NEXT",
            "ADD 28 Feb",
            "NEXT",
            "ADD 31 Mar",
            "NEXT",
            "ADD 30 Apr",
            "NEXT",
            "ADD 31 May",
            "NEXT",
            "ADD 30 Jun",
            "NEXT",
            "ADD 31 Jul",
            "NEXT",
            "ADD 31 Aug",
            "NEXT",
            "ADD 30 Sep",
            "NEXT",
            "ADD 31 Oct",
            "NEXT",
            "ADD 30 Nov",
            "NEXT",
            "ADD 31 Dec",
            "NEXT",
            "ADD 31 Jan",
            "DUMP 28",
            "DUMP 30",
            "DUMP 31",
        };
    auto res = todo(commands);
    vector<string> expected{
        "2 Jan Feb ",
        "9 Mar Apr May Jun Jul Aug Sep Oct Nov ",
        "2 Dec Jan ",
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
    auto result = anagram(commands);
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
        cout << "FAIL!" << endl;
        return -1;
    }
    else
    {
        cout << "Test 1 OK!" << endl;
    }
    if (!test_2())
    {
        cout << "FAIL!" << endl;
        return -1;
    }
    else
    {
        cout << "Test 2 OK!" << endl;
    }
    cout << "OK!" << endl;
    return 0;
#else
    return run();
#endif
}