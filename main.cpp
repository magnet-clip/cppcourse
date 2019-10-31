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
        // cout << command << endl;
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
            // cout << "NEXT " << last_month << " / " << current_month << endl;

            auto current_days = count_days[current_month];
            auto last_days = count_days[last_month];
            if (current_days < last_days)
            {
                // cout << "Current month days count "  << current_days << " < " << last_days << " - prev month" << endl;
                auto &new_last_day_of_month = tasks[current_days - 1];

                for (auto i = last_days - 1; i >= current_days; i--)
                {
                    auto last_day_tasks = tasks.back();
                    // cout << "Adding " << last_day_tasks.size() << " tasks  from task row " << tasks.size()-1 << " to exisiting " << new_last_day_of_month.size() << " tasks (row " << (current_days - 1) << ")" << endl;
                    new_last_day_of_month.insert(new_last_day_of_month.end(), last_day_tasks.begin(), last_day_tasks.end());
                    tasks.pop_back();
                }
            }
            else if (current_days > last_days)
            {
                tasks.insert(tasks.end(), current_days - last_days, vector<string>());
            }
        }
        else if (starts_with(command, "ADD"))
        {
            auto date = get_middle_integer(command) - 1;
            auto name = get_ending_string(command);

            //cout << "ADD " << date << " " << name << endl;

            tasks[date].push_back(name);
            // cout << "Now at date [" << date << "] there's [" << tasks[date].size() << "] tasks" << endl;
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
    } else {
        cout << "Test 1 OK!" << endl;
    }
     if (!test_2())
    {
        cout << "FAIL!" << endl;
        return -1;
    }else {
        cout << "Test 2 OK!" << endl;
    }
    cout << "OK!" << endl;
    return 0;
#else
    return run();
#endif
}