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
      return xname + " " + xsurname;
    } else if (xname != "") {
      return xname + " with unknown last name";
    } else if (xsurname != "") {
      return xsurname + " with unknown first name";
    } else {
      return "Incognito";
    }
  }

  string GetFullNameWithHistory(int year) {
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

  string get_full_item_by_year(const map<int, string> &coll, const int &year) {
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

bool test_2() {
  Person person;
  vector<string> res;

  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  string x;
  for (int year : {1900, 1965, 1990}) {
    x = person.GetFullNameWithHistory(year);
    cout << x << endl;
    res.push_back(x);
  }

  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    x = person.GetFullNameWithHistory(year);
    cout << x << endl;
    res.push_back(x);
  }

  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    x = person.GetFullNameWithHistory(year);
    cout << x << endl;
    res.push_back(x);
  }

  person.ChangeFirstName(1990, "Polina");
  person.ChangeLastName(1990, "Volkova-Sergeeva");
  x = person.GetFullNameWithHistory(1990);
  cout << x << endl;
  res.push_back(x);

  person.ChangeFirstName(1966, "Pauline");
  x = person.GetFullNameWithHistory(1966);
  cout << x << endl;
  res.push_back(x);

  person.ChangeLastName(1960, "Sergeeva");
  for (int year : {1960, 1967}) {
    x = person.GetFullNameWithHistory(year);
    cout << x << endl;
    res.push_back(x);
  }

  person.ChangeLastName(1961, "Ivanova");
  x = person.GetFullNameWithHistory(1967);
  cout << x << endl;
  res.push_back(x);

  vector<string> expected{
      "Incognito",
      "Polina with unknown last name",
      "Polina Sergeeva",
      "Polina Sergeeva",
      "Appolinaria (Polina) Sergeeva",
      "Polina Volkova (Sergeeva)",
      "Appolinaria (Polina) Volkova (Sergeeva)",
      "Polina (Appolinaria, Polina) Volkova-Sergeeva (Volkova, Sergeeva)",
      "Pauline (Polina) with unknown last name",
      "Sergeeva with unknown first name",
      "Pauline (Polina) Sergeeva",
      "Pauline (Polina) Sergeeva (Ivanova, Sergeeva)",
  };
  return vectors_equal(res, expected);
}

bool test_3() {
  Person person;
  vector<string> res;

  person.ChangeFirstName(1900, "Eugene");
  person.ChangeLastName(1900, "Sokolov");
  person.ChangeLastName(1910, "Sokolov");
  person.ChangeFirstName(1920, "Evgeny");
  person.ChangeLastName(1930, "Sokolov");
  string x = person.GetFullNameWithHistory(1940);
  cout << x << endl;
  res.push_back(x);

  vector<string> expected{
      "Evgeny (Eugene) Sokolov",

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
  if (!test_3()) {
    cout << "TEST 3 FAIL!" << endl;
    return -1;
  } else {
    cout << "Test 3 OK!" << endl;
  }
  if (!test_2()) {
    cout << "TEST 2 FAIL!" << endl;
    return -1;
  } else {
    cout << "Test 2 OK!" << endl;
  }

  cout << "OK!" << endl;
  return 0;
#else
  return run();
#endif
}