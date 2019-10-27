#include <iostream>
#include <vector>
using namespace std;

void Reverse(vector<int>& numbers) {
    int start_pos = 0, end_pos = numbers.size() - 1;
    while (start_pos < end_pos) {
        auto tmp = numbers[start_pos];
        numbers[start_pos] = numbers[end_pos];
        numbers[end_pos] = tmp;
        start_pos += 1;
        end_pos -= 1;
    }
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
    Reverse(numbers);
    return vectors_equal(numbers, rev_numbers);
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