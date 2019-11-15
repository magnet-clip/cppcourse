#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;

struct Specialization {
  string specialization;
  explicit Specialization(string specialization)
      : specialization(specialization) {}
};

struct Course {
  string course;
  explicit Course(string course) : course(course) {}
};

struct Week {
  string week;
  explicit Week(string week) : week(week) {}
};

struct LectureTitle {
  string specialization;
  string course;
  string week;
  LectureTitle(Specialization specialization, Course course, Week week) {
    this->specialization = specialization.specialization;
    this->course = course.course;
    this->week = week.week;
  };
};

#define TEST

#ifdef TEST

template <typename T>
bool vectors_equal(const vector<T> &v1, const vector<T> &v2) {
  if (v1.size() != v2.size()) {
    // cout << "Sizes are different" << endl;
    return false;
  }
  for (int i = 0; i < v1.size(); i++) {
    if (v1[i] != v2[i]) {
      // cout << "At index " << i << " " << v1[i] << " <> " << v2[i] << endl;
      return false;
    } else {
      // cout << "At index " << i << " " << v1[i] << " == " << v2[i] << endl;
    }
  }
  return true;
}

bool test_1() {}

#else
int run() {

  int num;
  cin >> num;
  cin >> ws;
  vector<string> commands(num);
  for (auto &command : commands) {
    getline(cin, command);
  }
  auto result = synonims(commands);
  for (auto item : result) {
    cout << item << endl;
  }
  return 0;
}
#endif

int main() {
#ifdef TEST
  if (!test_1()) {
    cout << "TEST 1 FAIL!" << endl;
    return -1;
  } else {
    cout << "Test 1 OK!" << endl;
  }

  cout << "OK!" << endl;
  return 0;
#else
  return run();
#endif
}