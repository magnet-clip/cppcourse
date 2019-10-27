#include <iostream>
#include <vector>
using namespace std;

void MoveStrings(vector<string>& source, vector<string>& destination) {
    for (auto s: source) {
        destination.push_back(s);
    }
    source.clear();
}

bool test_1() {
    vector<string> source = {"a", "b", "c"};
    vector<string> destination = {"z"};
    MoveStrings(source, destination);
    return source.size() == 0 && destination[0] == "z" && destination[1] == "a" && destination[2] == "b" && destination[3] == "c";
}

int main()
{
    if (!test_1()) {
        cout << "FAIL!";
        return -1;
    }

    cout << "OK!";
    return 0;
}