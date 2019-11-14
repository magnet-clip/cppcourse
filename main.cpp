#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;

#define TEST
string join_vector(const vector<string> &items, string delimiter) {
  string res;
  if (items.size() == 0) {
    return "";
  }

  if (items.size() == 1) {
    return items[0];
  }

  for (auto i = 0; i < items.size() - 1; i++) {
    res += items[i] + delimiter;
  }

  res += items[items.size() - 1];
  return res;
}

class Person {
public:
  Person(string xname, string xsurname, int year) {
    birth_year = year;
    name[year] = xname;
    surname[year] = xsurname;
  }

  void ChangeFirstName(int year, const string &first_name) {
    if (year >= birth_year)
      name[year] = first_name;
  }

  void ChangeLastName(int year, const string &last_name) {
    if (year >= birth_year)
      surname[year] = last_name;
  }

  string GetFullName(int year) const {
    if (year < birth_year)
      return "No person";

    auto xname = get_item_by_year(name, year);
    auto xsurname = get_item_by_year(surname, year);

    if (xname != "" && xsurname != "") {
      return xname + " " + xsurname;
    } else if (xname != "") {
      return xname + " with unknown last name";
    } else if (xsurname != "") {
      return xsurname + " with unknown first name";
    } else {
      return "Incognito";
    }
  }

  string GetFullNameWithHistory(int year) const {
    if (year < birth_year)
      return "No person";

    auto xname = get_full_item_by_year(name, year);
    auto xsurname = get_full_item_by_year(surname, year);

    if (xname != "" && xsurname != "") {
      return xname + " " + xsurname;
    } else if (xname != "") {
      return xname + " with unknown last name";
    } else if (xsurname != "") {
      return xsurname + " with unknown first name";
    } else {
      return "Incognito";
    }
  }

private:
  int birth_year;
  map<int, string> name;
  map<int, string> surname;

  string get_item_by_year(const map<int, string> &coll, const int &year) const {
    if (coll.size() == 0)
      return "";

    for (auto it = coll.rbegin(); it != coll.rend(); it++) {
      if (year >= it->first)
        return it->second;
    }

    return "";
  }

  string get_full_item_by_year(const map<int, string> &coll,
                               const int &year) const {
    if (coll.size() == 0)
      return "";

    string last = "";
    vector<string> names;
    string res = "";

    for (auto it = coll.rbegin(); it != coll.rend(); it++) {
      if (year >= it->first) {
        if ((last == "") || (it->second != last)) {
          names.push_back(it->second);
          last = it->second;
        }
      }
    }

    // cout << names.size() << ": [" << join_vector(names, ",") << "]" << endl;

    if (names.size() == 0) {
      return "";
    } else if (names.size() == 1) {
      return names[0];
    } else {
      res = names[0] + " (";
      // cout << res << endl;
      for (auto i = 1; i < names.size(); i++) {
        res += names[i] + ", ";
      }
      // cout << res << endl;
      res = res.substr(0, res.length() - 2) + ")";
      // cout << res << endl;
      return res;
    }
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

  vector<string> res;

  Person person("Polina", "Sergeeva", 1960);
  string x;
  for (int year : {1959, 1960}) {
    x = person.GetFullNameWithHistory(year);
    cout << x << endl;
    res.push_back(x);
  }

  person.ChangeFirstName(1965, "Appolinaria");
  person.ChangeLastName(1967, "Ivanova");
  for (int year : {1965, 1967}) {
    x = person.GetFullNameWithHistory(year);
    cout << x << endl;
    res.push_back(x);
  }

  vector<string> expected{
      "No person",
      "Polina Sergeeva",
      "Appolinaria (Polina) Sergeeva",
      "Appolinaria (Polina) Ivanova (Sergeeva)",

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