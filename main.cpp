#include <iostream>
#include <vector>
using namespace std;

vector<int> Reversed(const vector<int>& numbers) {
    vector<int> res;
    for (auto it = numbers.rbegin(); it != numbers.rend(); it++) {
        res.push_back(*it);
    }
    return res;
}

bool vectors_equal(const vector<int>& a, const vector<int>& b) {
    if (a.size() != b.size()) return false;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

bool test_1() {
    vector<int> numbers = {1, 5, 3, 4, 2};
    vector<int> rev_numbers = {2, 4, 3, 5, 1};
    return vectors_equal(Reversed(numbers), rev_numbers);
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