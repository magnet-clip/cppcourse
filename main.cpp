#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
using namespace std;

#define TEST

#ifdef TEST
stringstream ss;
#define ECHO(str) (ss << (str) << endl)
#else
#define ECHO(str) (cout << (str) << endl)
#endif

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
    getline(date_stream, raw_month, '-');
    getline(date_stream, raw_day);

    try {
      year = stoi(raw_year);
    } catch (invalid_argument) {
      stringstream msg_stream;
      msg_stream << "Wrong date format: " << str;
      throw date_format_exception(msg_stream.str());
    }

    try {
      month = stoi(raw_month);
    } catch (invalid_argument) {
      stringstream msg_stream;
      msg_stream << "Wrong date format: " << str;
      throw date_format_exception(msg_stream.str());
    }

    try {
      day = stoi(raw_day);
    } catch (invalid_argument) {
      stringstream msg_stream;
      msg_stream << "Wrong date format: " << str << " [" << raw_day << "]";
      throw date_format_exception(msg_stream.str());
    }

    if (month < 1 || month > 12) {
      stringstream msg_stream;
      msg_stream << "Month value is invalid: " << month;
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
  void AddEvent(const Date &date, const string &event) {
    data[date].insert(event);
  }

  bool DeleteEvent(const Date &date, const string &event) {
    if (data.count(date)) {
      ECHO("Deleted successfully");
      data[date].erase(event);
      if (data[date].size() == 0) {
        data.erase(date);
      }
      return true;
    } else {
      ECHO("Event not found");
      return false;
    }
  }

  int DeleteDate(const Date &date) {
    int count = 0;
    if (data.count(date)) {
      count = data[date].size();
      data.erase(date);
    }
    stringstream msg;
    msg << "Deleted " << count << " events";
    ECHO(msg.str());
    return count;
  }

  void Find(const Date &date) {
    if (data.count(date)) {
      for (const auto &item : data[date]) {
        ECHO(item);
      }
    }
  }

  void Print() const {
    for (const auto &[date, items] : data) {
      for (const auto &item : items) {
        stringstream msg;
        msg << date << " " << item;
        ECHO(msg.str());
      }
    }
  }

private:
  map<Date, set<string>> data;
};

void database(const vector<string> &lines) {
  Database db;

  for (const auto &line : lines) {
    stringstream command_stream(line);
    string command;
    command_stream >> command;
    if (command == "Add") {
      string event;
      string date;

      // reading event and date as plain strings
      command_stream >> date >> event;

      try {
        // converting string to date
        Date the_date(date);

        db.AddEvent(date, event);
      } catch (date_format_exception &e) {
        // in case of error, show message
        stringstream response;
        response << e.getMessage();
        ECHO(response.str());
      }

    } else if (command == "Del") {
      string date;
      string event;

      // reading event and date as plain strings
      command_stream >> date;
      try {
        // converting string to date
        Date the_date(date);

        if (command_stream.eof()) {
          db.DeleteDate(date);
        } else {
          command_stream >> event;
          db.DeleteEvent(date, event);
        }
      } catch (date_format_exception &e) {
        // in case of error, show message
        stringstream response;
        response << e.getMessage();
        ECHO(response.str());
      }
    } else if (command == "Find") {
      string date;
      string event;

      // reading event and date as plain strings
      command_stream >> date;
      try {
        // converting string to date
        Date the_date(date);

        db.Find(date);
      } catch (date_format_exception &e) {
        // in case of error, show message
        stringstream response;
        response << e.getMessage();
        ECHO(response.str());
      }
    } else if (command == "Print") {
      db.Print();
    } else if (command == "") {
    } else {
      stringstream response;
      response << "Unknown command: " << command << endl;
      ECHO(response.str());
    }
  }
}

#ifdef TEST

bool compare(vector<string> output) {
  for (const auto &item : output) {
    string str;
    if (ss.eof()) {
      cout << "ss ended";
      return false;
    }
    getline(ss, str);
    if (str != item) {
      cout << str << " != " << item << endl;
      return false;
    } else {
      cout << "[" << str << "] == [" << item << "]" << endl;
    }
  }
  return true;
}

bool test1() {
  database({
      "Add 0-1-2 event1",
      "Add 1-2-3 event2",
      "Find 0-1-2",
      "",
      "Del 0-1-2",
      "Print",
      "Del 1-2-3 event2",
      "Del 1-2-3 event2",
  });

  return compare({
      "event1",
      "Deleted 1 events",
      "0001-02-03 event2",
      "Deleted successfully",
      "Event not found",
  });
}

bool test2() {
  database({
      "Add 0-13-32 event1",
  });

  return compare({
      "Month value is invalid: 13",
  });

  // return vectors_equal(res, output);
}

bool test3() {
  database({
      "Add 1---1-1 event1",
  });

  return compare({
      "Wrong date format: 1---1-1",
  });
}

bool test4() {
  database({
      "Add 0-11-32 event1",
  });

  return compare({
      "Day value is invalid: 32",
  });
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
  string command;
  while (getline(cin, command)) {
    commands.push_back(command);
  }

  database(commands);

  return 0;
#endif
}