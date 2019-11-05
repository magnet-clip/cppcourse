#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>

using namespace std;

// #define TEST
bool starts_with(const string &who, const string &what)
{
    if (who.length() <= what.length())
        return false;
    return who.find(what) == 0;
}

auto parse_route(string command)
{
    vector<string> stops;
    int count;
    int state = 0;
    // state
    // 0 - reading stops
    // 1 - finished

    auto pos = command.find_first_of(' '); // end of command itself
    // stop_count stop1 stop2 ...
    while (state < 1)
    {
        auto last_pos = pos + 1;
        string temp;
        pos = command.find_first_of(' ', last_pos);
        switch (state)
        {
        case 0:
            if (pos == string::npos)
            {
                auto stop_name = command.substr(last_pos);
                // cout << "Stop name: [" << stop_name << "]" << endl;
                stops.push_back(stop_name);

                state++;
            }
            else
            {
                auto stop_name = command.substr(last_pos, pos - last_pos);
                // cout << "Stop name: [" << stop_name << "]" << endl;
                stops.push_back(stop_name);
            }
            break;
        case 1:
            // cout << "End" << endl;
            break;
        }
    }

    return stops;
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

auto numbers(const vector<string> &commands)
{
    vector<string> res;
    auto route_counter = 0;
    map<vector<string>, int> routes;

    for (auto command : commands)
    {
        stringstream buffer;
        auto route = parse_route(command);
        if (routes.count(route))
        {
            buffer << "Already exists for " << routes[route];
        }
        else
        {
            routes[route] = ++route_counter;
            buffer << "New bus " << route_counter;
        }
        res.push_back(buffer.str());
        buffer.str("");
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
            cout << "At index " << i << " " << v1[i] << " <> " << v2[i] << endl;
            return false;
        }
        else
        {
            cout << "At index " << i << " " << v1[i] << " == " << v2[i] << endl;
        }
    }
    return true;
}

bool test_0()
{
    const auto &stops = parse_route("3 Tolstopaltsevo Marushkino Vnukovo");

    if (stops != vector<string>{"Tolstopaltsevo", "Marushkino", "Vnukovo"})
        return false;

    return true;
}

bool test_1()
{

    vector<string>
        commands{
            "2 Marushkino Kokoshkino",
            "1 Kokoshkino",
            "2 Marushkino Kokoshkino",
            "2 Kokoshkino Marushkino",
        };
    auto res = numbers(commands);
    vector<string> expected{
        "New bus 1",
        "New bus 2",
        "Already exists for 1",
        "New bus 3",
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
    auto result = numbers(commands);
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
    if (!test_0())
    {
        cout << "TEST 0 FAIL!" << endl;
        return -1;
    }
    else
    {
        cout << "Test 0 OK!" << endl;
    }
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