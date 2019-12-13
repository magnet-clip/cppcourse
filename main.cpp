#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;

#define TEST
bool starts_with(const string &who, const string &what) {
  if (who.length() <= what.length())
    return false;
  return who.find(what) == 0;
}

string get_second_string(const string &str) {
  auto pos = str.find_first_of(' ');
  return str.substr(pos + 1);
}

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

auto parse_bus_info(string command) {
  string bus_name;
  int stops_count;
  vector<string> stops;

  int state = 0;
  // state
  // 0 - reading bus number
  // 1 - reading stops count
  // 2 - reading stops
  // 3 - finished

  auto pos = command.find_first_of(' '); // end of command itself

  // NEW_BUS bus stop_count stop1 stop2 ...
  // NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo
  while (state < 3) {
    auto last_pos = pos + 1;
    pos = command.find_first_of(' ', last_pos);
    switch (state) {
    case 0:
      bus_name = command.substr(last_pos, pos - last_pos);
      // cout << "Bus name: [" << bus_name << "]" << endl;
      state++;
      break;
    case 1:
      state++;
      stops_count = stoi(command.substr(last_pos, pos - last_pos));
      // cout << "Stops count: [" << stops_count << "]" << endl;
      break;
    case 2:
      if (pos == string::npos) {
        auto stop_name = command.substr(last_pos);
        // cout << "Stop name: [" << stop_name << "]" << endl;
        stops.push_back(stop_name);

        state++;
      } else {
        auto stop_name = command.substr(last_pos, pos - last_pos);
        // cout << "Stop name: [" << stop_name << "]" << endl;
        stops.push_back(stop_name);
      }
      break;
    case 3:
      cout << "End" << endl;
      break;
    }
  }

  return make_tuple(bus_name, stops_count, stops);
}

auto route(const vector<string> &commands) {
  vector<string> res;
  map<string, vector<string>> stops_for_bus;
  map<string, vector<string>> buses_for_stop;

  for (auto command : commands) {
    stringstream buffer;
    if (command == "ALL_BUSES") {
      // print out all routes and stops
      if (stops_for_bus.size()) {
        for (auto [bus, stops] : stops_for_bus) {
          buffer << "Bus " << bus << ": " << join_vector(stops, " ");
          res.push_back(buffer.str());
          buffer.str("");
        }
      } else {
        buffer << "No buses";
        res.push_back(buffer.str());
      }
    } else if (starts_with(command, "NEW_BUS")) {
      // NEW_BUS bus stop_count stop1 stop2 ...
      // add bus route
      const auto &[bus_name, stops_count, stops] = parse_bus_info(command);
      for (auto stop : stops) {
        stops_for_bus[bus_name].push_back(stop);
        buses_for_stop[stop].push_back(bus_name);
      }
    } else if (starts_with(command, "BUSES_FOR_STOP")) {
      // BUSES_FOR_STOP stop
      // print which buses visit this stop
      auto stop = get_second_string(command);
      if (!buses_for_stop.count(stop)) {
        buffer << "No stop";
      } else {
        buffer << join_vector(buses_for_stop[stop], " ");
      }
      res.push_back(buffer.str());
    } else if (starts_with(command, "STOPS_FOR_BUS")) {
      // STOPS_FOR_BUS bus
      // print which stops does the bus visit
      auto bus = get_second_string(command);
      if (!stops_for_bus.count(bus)) {
        buffer << "No bus";
        res.push_back(buffer.str());
      } else {
        for (auto stop : stops_for_bus[bus]) {
          auto buses_for_this_stop = buses_for_stop[stop];
          auto search_iterator =
              find(buses_for_this_stop.begin(), buses_for_this_stop.end(), bus);
          buses_for_this_stop.erase(search_iterator);
          if (buses_for_this_stop.size()) {
            buffer << "Stop " << stop << ": "
                   << join_vector(buses_for_this_stop, " ");
          } else {
            buffer << "Stop " << stop << ": no interchange";
          }
          res.push_back(buffer.str());
          buffer.str("");
        }
      }
    }
  }
  return res;
}

#ifdef TEST
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

bool test_0() {
  const auto &[bus_name, stops_count, stops] =
      parse_bus_info("NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo");

  if (bus_name != "32")
    return false;

  if (stops_count != 3)
    return false;

  if (stops != vector<string>{"Tolstopaltsevo", "Marushkino", "Vnukovo"})
    return false;

  return true;
}

bool test_1() {

  vector<string> commands{
      "10",
      "ALL_BUSES",
      "BUSES_FOR_STOP Marushkino",
      "STOPS_FOR_BUS 32K",
      "NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo",
      "NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo "
      "Skolkovo",
      "BUSES_FOR_STOP Vnukovo",
      "NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo "
      "Troparyovo",
      "NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo",
      "STOPS_FOR_BUS 272",
      "ALL_BUSES",
  };
  auto res = route(commands);
  vector<string> expected{
      "No buses",
      "No stop",
      "No bus",
      "32 32K",
      "Stop Vnukovo: 32 32K 950",
      "Stop Moskovsky: no interchange",
      "Stop Rumyantsevo: no interchange",
      "Stop Troparyovo: 950",
      "Bus 272: Vnukovo Moskovsky Rumyantsevo Troparyovo",
      "Bus 32: Tolstopaltsevo Marushkino Vnukovo",
      "Bus 32K: Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo "
      "Skolkovo",
      "Bus 950: Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo",
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
  auto result = route(commands);
  for (auto item : result) {
    cout << item << endl;
  }
  return 0;
}
#endif

int main() {
#ifdef TEST
  if (!test_0()) {
    cout << "TEST 0 FAIL!" << endl;
    return -1;
  } else {
    cout << "Test 0 OK!" << endl;
  }
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