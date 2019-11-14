#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;

#define TEST

class Person {
public:
  void ChangeFirstName(int year, const string &first_name) {
    name[year] = first_name;
  }
  void ChangeLastName(int year, const string &last_name) {
    surname[year] = last_name;
  }
  string GetFullName(int year) {
    auto xname = get_item_by_year(name, year);
    auto xsurname = get_item_by_year(surname, year);

    if (xname != "" && xsurname != "") {
      return get_item_by_year(name, year) + " " +
             get_item_by_year(surname, year);
    } else if (xname != "") {
      return get_item_by_year(name, year) + " with unknown last name";
    } else if (xsurname != "") {
      return get_item_by_year(surname, year) + " with unknown first name";
    } else {
      return "Incognito";
    }
  }

private:
  map<int, string> name;
  map<int, string> surname;

  string get_item_by_year(const map<int, string> &coll, const int &year) {
    if (coll.size() == 0)
      return "";

    for (auto it = coll.rbegin(); it != coll.rend(); it++) {
      if (year >= it->first)
        return it->second;
    }

    return "";
  }
};

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

bool test_1() {

  Person person;
  vector<string> res;

  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  string x;
  for (int year : {1900, 1965, 1990}) {
    x = person.GetFullName(year);
    cout << x << endl;
    res.push_back(x);
  }

  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    x = person.GetFullName(year);
    cout << x << endl;
    res.push_back(x);
  }

  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    x = person.GetFullName(year);
    cout << x << endl;
    res.push_back(x);
  }

  vector<string> expected{
      "Incognito",           "Polina with unknown last name", "Polina Sergeeva",
      "Polina Sergeeva",     "Appolinaria Sergeeva",          "Polina Volkova",
      "Appolinaria Volkova",
  };
  return vectors_equal(res, expected);
}

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