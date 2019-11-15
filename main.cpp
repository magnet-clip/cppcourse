#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;


struct Image {
  double quality;
  double freshness;
  double rating;
};

struct Params {
  double a;
  double b;
  double c;
};

class FunctionPart {
public:
  FunctionPart(char op, double val) : op(op), val(val) {}

  double Apply(double x) const {
    if (op == '+') {
      return x + val;
    } else if (op == '*') {
      return x * val;
    } else if (op == '/') {
      return x / val;
    } else {
      return x - val;
    }
  }

  void Invert() {
    if (op == '+') {
      op = '-';
    } else if (op == '*') {
      op = '/';
    } else if (op == '/') {
      op = '*';
    } else if (op == '-') {
      op = '+';
    }
  }

private:
  char op;
  double val;
};

class Function {
public:
  void AddPart(char op, double val) { parts.push_back({op, val}); }

  void Invert() {
    for (auto &part : parts) {
      part.Invert();
    }
    reverse(begin(parts), end(parts));
  }

  double Apply(double x) const {
    for (const auto &part : parts) {
      x = part.Apply(x);
    }
    return x;
  }

private:
  vector<FunctionPart> parts;
};

Function MakeWeightFunction1(const Params &params, const Image &image) {
  Function function;
  function.AddPart('-', image.freshness * params.a + params.b);
  function.AddPart('+', image.rating * params.c);
  return function;
}

double ComputeImageWeight1(const Params &params, const Image &image) {
  Function function = MakeWeightFunction1(params, image);
  return function.Apply(image.quality);
}

double ComputeQualityByWeight1(const Params &params, const Image &image,
                               double weight) {
  Function function = MakeWeightFunction1(params, image);
  function.Invert();
  return function.Apply(weight);
}

Function MakeWeightFunction2(const Params &params, const Image &image) {
  Function function;
  function.AddPart('*', params.a);
  function.AddPart('-', image.freshness * params.b);
  function.AddPart('+', image.rating * params.c);
  return function;
}

double ComputeImageWeight2(const Params &params, const Image &image) {
  Function function = MakeWeightFunction2(params, image);
  return function.Apply(image.quality);
}

double ComputeQualityByWeight2(const Params &params, const Image &image,
                               double weight) {
  Function function = MakeWeightFunction2(params, image);
  function.Invert();
  return function.Apply(weight);
}
#define TEST

#ifdef TEST

bool test_1() {
  Image image = {10, 2, 6};
  Params params = {4, 2, 6};
  if (ComputeImageWeight1(params, image) != 36) {
    cout << "Fail1" << endl;
    return false;
  }
  if (ComputeQualityByWeight1(params, image, 46) != 20) {
    cout << "Fail2: " << ComputeQualityByWeight1(params, image, 46)
         << " != " << 20 << endl;
    return false;
  }
  return true;
}

bool test_2() {
  Image image = {10, 2, 6};
  Params params = {4, 2, 6};
  if (ComputeImageWeight2(params, image) != 72) {
    cout << "Fail1" << endl;
    return false;
  }
  if (ComputeQualityByWeight2(params, image, 52) != 5) {
    cout << "Fail2: " << ComputeQualityByWeight1(params, image, 52)
         << " != " << 5 << endl;
    return false;
  }
  return true;
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