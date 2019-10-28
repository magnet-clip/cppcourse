#include <iostream>
#include <vector>

using namespace std;

//#define TEST

bool starts_with(const string& who, const string& what) {
    if (who.length() <= what.length()) return false;
    return who.find(what) == 0;
}

int getFinalInt(const string& what, int start_pos) {
    string arg = what.substr(start_pos);
    return atoi(arg.c_str());
}

vector<int> worried_queue(const vector<string>& actions) {
    int worry_count = 0;
    vector<bool> worried_people;
    vector<int> res;
    for (auto command: actions) {
        // cout << command << endl;
        if (command == "WORRY_COUNT") {
            res.push_back(worry_count);
        } else if (starts_with(command, "COME")) {
            int came = getFinalInt(command, 5);
            if (came > 0) {
                worried_people.insert(worried_people.end(), came, false);
            } else if (came < 0) {
                worried_people.resize(worried_people.size() + came);
                worry_count = 0;
                for (auto person: worried_people) {
                    if (person) worry_count++;
                }
            }
        } else if (starts_with(command, "WORRY")) {
            int worried_pos = getFinalInt(command, 6);
            auto was_worried = worried_people[worried_pos];
            if (!was_worried) {
                worried_people[worried_pos] = true;
                worry_count++;
            }
        } else if (starts_with(command, "QUIET")) {
            int quiet_pos = getFinalInt(command, 6);
            auto was_worried = worried_people[quiet_pos];
            if (was_worried) {
                worried_people[quiet_pos] = false;
                worry_count--;
            }
        }
        // cout << "queue length now " << worried_people.size() << " and number of worried is " << worry_count << endl;
    }
    return res;
}


#ifdef TEST
    template<typename T> bool vectors_equal(const vector<T>& v1, const vector<T>& v2) {
        if (v1.size() != v2.size()) return false;
        for (int i = 0; i < v1.size(); i++)  {
            if (v1[i] != v2[i]) return false;
        }
        return true;
    }

    bool test_1() {
        vector<string> commands{"COME 5", "WORRY 1", "WORRY 4", "COME -2", "WORRY_COUNT", "COME 3", "WORRY 3", "WORRY_COUNT"};
        auto res = worried_queue(commands);
        vector<int> expected{1, 2};
        for (auto item: res) {
            cout << item << endl;
        }
        return vectors_equal(res, expected);
    }
#else
    int run() {
        int num;
        cin >> num;
        cin >> ws;
        vector<string> commands(num);
        for (auto& command: commands) {
            getline (cin, command);
        }
        auto result = worried_queue(commands);
        for (auto item: result) {
            cout << item << endl;
        }
        return 0;
    }
#endif

int main() {
    #ifdef TEST
        if (!test_1()) {
            cout << "FAIL!" << endl;
            return -1;
        }
        cout << "OK!" << endl;
        return 0;
    #else 
        return run();
    #endif
}