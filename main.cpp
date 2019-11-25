#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class date_format_exception : exception {
public:
  date_format_exception() : exception() {}
  date_format_exception(string msg) : exception(), message(msg) {}
  string getMessage() { return message; }

private:
  string message;
};

class Date {
public:
  Date() : year(0), month(0), day(0) {}
  Date(int year, int month, int day) : year(year), month(month), day(day) {}
  Date(string str) {
    string raw_year, raw_month, raw_day;

    stringstream date_stream(str);

    getline(date_stream, raw_year, '-');
    try {
      year = stoi(raw_year);
    } catch (invalid_argument) {
      stringstream msg_stream;
      msg_stream << "Wrong date format: " << str;
      throw date_format_exception(msg_stream.str());
    }

    getline(date_stream, raw_month, '-');
    try {
      month = stoi(raw_month);
    } catch (invalid_argument) {
      stringstream msg_stream;
      msg_stream << "Wrong date format: " << str;
      throw date_format_exception(msg_stream.str());
    }

    if (month < 1 || month > 12) {
      stringstream msg_stream;
      msg_stream << "Month value is invalid: " << month;
      throw date_format_exception(msg_stream.str());
    }

    getline(date_stream, raw_day, '-');
    try {
      day = stoi(raw_day);
    } catch (invalid_argument) {
      stringstream msg_stream;
      msg_stream << "Wrong date format: " << str << " [" << raw_day << "]";
      throw date_format_exception(msg_stream.str());
    }

    if (day < 1 || day > 31) {
      stringstream msg_stream;
      msg_stream << "Day value is invalid: " << day;
      throw date_format_exception(msg_stream.str());
    }
  }
  int GetYear() const { return year; }
  int GetMonth() const { return month; }
  int GetDay() const { return day; }

private:
  int year, month, day;
};

bool operator<(const Date &lhs, const Date &rhs) {
  if (lhs.GetYear() == rhs.GetYear()) {
    if (lhs.GetMonth() == rhs.GetMonth()) {
      return lhs.GetDay() < rhs.GetDay();
    } else {
      return lhs.GetMonth() < rhs.GetMonth();
    }
  } else {
    return lhs.GetYear() < rhs.GetYear();
  }
}

ostream &operator<<(ostream &stream, const Date &date) {
  stream << setw(4) << setfill('0') << date.GetYear();
  stream << "-";
  stream << setw(2) << setfill('0') << date.GetMonth();
  stream << "-";
  stream << setw(2) << setfill('0') << date.GetDay();
  return stream;
}

class Database {
public:
  void AddEvent(const Date &date, const string &event);
  bool DeleteEvent(const Date &date, const string &event);
  int DeleteDate(const Date &date);

  vector<string> Find(const Date &date) const;

  void Print() const;
};

vector<string> database(const vector<string> &lines) {
  Database db;
  vector<string> res;

  for (const auto &line : lines) {
    stringstream command_stream(line);
    string command;
    command_stream >> command;
    if (command == "Add") {
      string event;
      string date;
      command_stream >> date >> event;

      try {
        Date the_date(date);
      } catch (date_format_exception &e) {
        stringstream response;
        response << e.getMessage();
        res.push_back(response.str());
        continue;
      }
    } else if (command == "Del") {
    } else if (command == "Find") {
    } else if (command == "Print") {
      // db.Print();
    } else {
      stringstream response;
      response << "Unknown command: " << command << endl;
      res.push_back(response.str());
    }
  }

  return res;
}

#define TEST

#ifdef TEST

bool starts_with(const string &who, const string &what) {
  if (who.length() <= what.length())
    return false;
  return who.find(what) == 0;
}

template <typename T>
bool vectors_equal(const vector<T> &v1, const vector<T> &v2) {
  if (v1.size() != v2.size()) {
    cout << "Sizes are different" << endl;
    return false;
  }
  for (int i = 0; i < v1.size(); i++) {
    if (v1[i] != v2[i]) {
      cout << "At index " << i << " " << v1[i] << " <> " << v2[i] << endl;
      return false;
    } else {
      cout << "At index " << i << " " << v1[i] << " == " << v2[i] << endl;
    }
  }
  return true;
}

bool test1() {
  auto res = database({
      "Add 0-1-2 event1",
      "Add 1-2-3 event2",
      "Find 0-1-2",
      "",
      "Del 0-1-2",
      "Print",
      "Del 1-2-3 event2",
      "Del 1-2-3 event2",
  });

  vector<string> output{
      "event1",
      "Deleted 1 events",
      "0001-02-03 event2",
      "Deleted successfully",
      "Event not found",
  };

  return vectors_equal(res, output);
}

bool test2() {
  auto res = database({
      "Add 0-13-32 event1",
  });

  vector<string> output{
      "Month value is invalid: 13",
  };

  return vectors_equal(res, output);
}

bool test3() {
  auto res = database({
      "Add 1---1-1 event1",
  });

  vector<string> output{
      "Wrong date format: 1---1-1",
  };

  return vectors_equal(res, output);
}

bool test4() {
  auto res = database({
      "Add 0-11-32 event1",
  });

  vector<string> output{
      "Day value is invalid: 32",
  };

  return vectors_equal(res, output);
}
#else

#endif

int main() {
#ifdef TEST
  if (!test1()) {
    cout << "TEST 1 FAILED" << endl;
  } else {
    cout << "TEST 1 OK" << endl;
  }
  if (!test2()) {
    cout << "TEST 2 FAILED" << endl;
  } else {
    cout << "TEST 2 OK" << endl;
  }
  if (!test3()) {
    cout << "TEST 3 FAILED" << endl;
  } else {
    cout << "TEST 3 OK" << endl;
  }
  if (!test4()) {
    cout << "TEST 4 FAILED" << endl;
  } else {
    cout << "TEST 4 OK" << endl;
  }
  return 0;

#else
  vector<string> commands;
  while (getline(cin, command)) {
    commands.push_back(command);
  }

  auto res = database(commands);
  for (const auto &str : res) {
    cout << str << endl;
  }

  return 0;
#endif
}