#include <iostream>
using namespace std;

class Rational {
public:
  Rational() {
    num = 0;
    denom = 1;
  }

  Rational(int numerator, int denominator) {

    if (denominator == 0) {
      throw invalid_argument("denominator is 0");
    }

    if (numerator == 0) {
      num = 0;
      denom = 1;
    } else {
      auto divisor = gcd(abs(numerator), abs(denominator));
      num = numerator / divisor;
      denom = denominator / divisor;
    }

    if (denom < 0) {
      num = -num;
      denom = -denom;
    }
  }

  int Numerator() const { return num; }

  int Denominator() const { return denom; }

private:
  int num, denom;

  int gcd(int n1, int n2) {
    auto smallest = min(n1, n2);
    auto largest = max(n1, n2);

    if (smallest == 0 || smallest == 1) {
      return 1;
    }

    while (smallest != 0) {
      auto m = largest % smallest;
      largest = smallest;
      smallest = m;
    }
    return largest;
  }
};

Rational operator+(const Rational &a, const Rational &b) {
  return Rational(a.Numerator() * b.Denominator() +
                      b.Numerator() * a.Denominator(),
                  a.Denominator() * b.Denominator());
}

Rational operator-(const Rational &a, const Rational &b) {
  return Rational(a.Numerator() * b.Denominator() -
                      b.Numerator() * a.Denominator(),
                  a.Denominator() * b.Denominator());
}

Rational operator*(const Rational &a, const Rational &b) {
  return Rational(a.Numerator() * b.Numerator(),
                  a.Denominator() * b.Denominator());
}

Rational operator/(const Rational &a, const Rational &b) {
  if (b.Numerator() == 0) {
    throw domain_error("Division by zero");
  }
  return Rational(a.Numerator() * b.Denominator(),
                  a.Denominator() * b.Numerator());
}

bool operator==(const Rational &a, const Rational &b) {
  return a.Numerator() == b.Numerator() && a.Denominator() == b.Denominator();
}

bool operator<(const Rational &a, const Rational &b) {
  return a.Numerator() * b.Denominator() < a.Denominator() * b.Numerator();
}

ostream &operator<<(ostream &stream, const Rational &a) {
  stream << a.Numerator() << "/" << a.Denominator();
  return stream;
}

istream &operator>>(istream &stream, Rational &a) {
  if (!stream) {
    return stream;
  }

  if (stream.tellg() == -1) {
    return stream;
  }
  int numerator, denominator;
  stream >> numerator;
  stream.ignore(1);
  stream >> denominator;
  a = Rational(numerator, denominator);
  return stream;
}

int main() {
  {
    const Rational r(3, 10);
    if (r.Numerator() != 3 || r.Denominator() != 10) {
      cout << "Rational(3, 10) != 3/10" << endl;
      return 1;
    }
  }

  {
    const Rational r(8, 12);
    if (r.Numerator() != 2 || r.Denominator() != 3) {
      cout << "Rational(8, 12) != 2/3" << endl;
      return 2;
    }
  }

  {
    const Rational r(-4, 6);
    if (r.Numerator() != -2 || r.Denominator() != 3) {
      cout << "Rational(-4, 6) != -2/3" << endl;
      return 3;
    }
  }

  {
    const Rational r(4, -6);
    if (r.Numerator() != -2 || r.Denominator() != 3) {
      cout << "Rational(4, -6) != -2/3" << endl;
      return 3;
    }
  }

  {
    const Rational r(0, 15);
    if (r.Numerator() != 0 || r.Denominator() != 1) {
      cout << "Rational(0, 15) != 0/1" << endl;
      return 4;
    }
  }

  {
    const Rational defaultConstructed;
    if (defaultConstructed.Numerator() != 0 ||
        defaultConstructed.Denominator() != 1) {
      cout << "Rational() != 0/1" << endl;
      return 5;
    }
  }

  {
    Rational r1(4, 6);
    Rational r2(2, 3);
    bool equal = r1 == r2;
    if (!equal) {
      cout << "4/6 != 2/3" << endl;
      return 1;
    }
  }

  {
    Rational a(2, 3);
    Rational b(4, 3);
    Rational c = a + b;
    bool equal = c == Rational(2, 1);
    if (!equal) {
      cout << "2/3 + 4/3 != 2" << endl;
      return 2;
    }
  }

  {
    Rational a(5, 7);
    Rational b(2, 9);
    Rational c = a - b;
    bool equal = c == Rational(31, 63);
    if (!equal) {
      cout << "5/7 - 2/9 != 31/63" << endl;
      return 3;
    }
  }

  {
    const Rational r = Rational(1, 2) * Rational(1, 3) / Rational(1, 4);
    bool equal = (r == Rational(2, 3));
    if (!equal) {
      cout << "1/2*1/3 / 1/4 != 2/3" << endl;
      return 1;
    }
  }

  {
    try {
      Rational r(1, 0);
      cout << "Doesn't throw in case of zero denominator" << endl;
      return 1;
    } catch (invalid_argument &) {
    }

    try {
      auto x = Rational(1, 2) / Rational(0, 1);
      cout << "Doesn't throw in case of division by zero" << endl;
      return 2;
    } catch (domain_error &) {
    }
  }

  cout << "OK" << endl;
  return 0;
}