#include <iostream>
using namespace std;

string AskTimeServer() { return ""; }

class TimeServer {
public:
  string GetCurrentTime() {
    try {
      LastFetchedTime = AskTimeServer();
    } catch (system_error &e) {
    }
    return LastFetchedTime;
  }

private:
  string LastFetchedTime = "00:00:00";
};

int main() {
  cout << "OK" << endl;
  return 0;
}