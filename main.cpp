#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

int main() {
  ifstream input("input.txt");

  int value;
  int rows, cols;

  input >> rows >> cols;

  for (auto r = 0; r < rows; r++) {
    for (auto c = 0; c < cols - 1; c++) {
      input >> value;
      input.ignore(1);
      cout << setw(10) << right << value << " ";
    }
    input >> value;
    input.ignore(1);
    cout << setw(10) << right << value;
    if (r < rows - 1) {
      cout << endl;
    }
  }
}