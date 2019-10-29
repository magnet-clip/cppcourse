#include <iostream>
#include <vector>

using namespace std;

//#define TEST

bool starts_with(const string &who, const string &what)
{
    if (who.length() <= what.length())
        return false;
    return who.find(what) == 0;
}

int get_ending_integer(const string &what)
{
    int start_space_pos = what.find_first_of(' ');
    string arg = what.substr(start_space_pos + 1);
    return atoi(arg.c_str());
}

int get_middle_integer(const string &what)
{
    int start_space_pos = what.find_first_of(' ');
    int end_space_pos = what.find_last_of(' ');
    string arg = what.substr(start_space_pos + 1, end_space_pos - start_space_pos);
    return atoi(arg.c_str());
}

string get_ending_string(const string &what)
{
    int end_space_pos = what.find_last_of(' ');
    string arg = what.substr(end_space_pos + 1);
    return arg;
}

auto todo(const vector<string> &actions)
{
    vector<string> res;
    const vector<int> count_days{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int current_month = 0;
    vector<vector<string>> tasks;
    tasks.assign(count_days[current_month], vector<string>());

    for (auto command : actions)
    {
        if (starts_with(command, "DUMP"))
        {
            auto date = get_ending_integer(command) - 1;
            // cout << "DUMP " << date << endl;
            string str;
            str.append(to_string(tasks[date].size()) + " ");
            for (auto record : tasks[date])
            {
                str.append(record + " ");
            }
            res.push_back(str);
        }
        else if (command == "NEXT")
        {
            auto last_month = current_month;
            current_month = (current_month + 1) % 12;
            // cout << "NEXT " << current_month << endl;

            if (count_days[current_month] < count_days[last_month])
            {
                auto &new_last_day_of_month = tasks[count_days[current_month] - 1];

                for (auto i = count_days[last_month] - 1; i > count_days[current_month]; i--)
                {
                    auto last_day_tasks = tasks.back();
                    new_last_day_of_month.insert(new_last_day_of_month.end(), last_day_tasks.begin(), last_day_tasks.end());
                    tasks.pop_back();
                }
            }
            else if (count_days[current_month] > count_days[last_month])
            {
                tasks.insert(tasks.end(), vector<string>());
            }
        }
        else if (starts_with(command, "ADD"))
        {
            auto date = get_middle_integer(command) - 1;
            auto name = get_ending_string(command);

            // cout << "ADD " << date << " " << name << endl;

            tasks[date].push_back(name);
        }
    }
    return res;
}

#ifdef TEST
template <typename T>
bool vectors_equal(const vector<T> &v1, const vector<T> &v2)
{
    if (v1.size() != v2.size())
        return false;
    for (int i = 0; i < v1.size(); i++)
    {
        if (v1[i] != v2[i])
            return false;
    }
    return true;
}

bool test_1()
{
    vector<string> commands{"COME 5", "WORRY 1", "WORRY 4", "COME -2", "WORRY_COUNT", "COME 3", "WORRY 3", "WORRY_COUNT"};
    auto res = worried_queue(commands);
    vector<int> expected{1, 2};
    for (auto item : res)
    {
        cout << item << endl;
    }
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
    auto result = todo(commands);
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
    cout << "OK!" << endl;
    return 0;
#else
    return run();
#endif
}