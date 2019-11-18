#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;

//#define TEST

#ifdef TEST

bool test_1() { return true; }

bool test_2() { return true; }

#else

int run() {
  ifstream input("input.txt");
  ofstream output("output.txt");
  string line;
  while (getline(input, line)) {
    output << line << endl;
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