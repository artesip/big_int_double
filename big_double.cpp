#include "big_double.h"


void input_in_arr(std::string &temp, big_double &num) {
  int i = 0;
  if (temp[0] == '-') {
    num.numerator.is_negative = true;
    i += 1;
  }
  for (auto it = --temp.end(); it != temp.begin(); --it) {
    if (*it == '0') {
      temp.erase(it);
    } else {
      break;
    }
  }
  int dot_pos = temp.size();
  int j = i;
  while (j < temp.size()) {
    if (temp[j] == '.') {
      dot_pos = j;
      break;
    }
    ++j;
  }
  num.numerator.digit_arr.resize(temp.size() - 1);
  for (; i < dot_pos; ++i) {
    num.numerator.digit_arr[temp.size() - i - 1 - 1] = atoi(temp.substr(i, 1).c_str());
  }

  for (; i < temp.size(); ++i) {
    num.numerator.digit_arr[temp.size() - i - 1 - 1] = atoi(temp.substr(i+1, 1).c_str());
  }
  num.denominator.digit_arr.resize(temp.size() - dot_pos);
  num.denominator.digit_arr[temp.size() - dot_pos - 1] = 1;

}

std::istream &operator>>(std::istream &in, big_double &num) {
  std::string temp;
  in >> temp;
  input_in_arr(temp, num);
  return in;
}

std::ostream &operator<<(std::ostream &o, const big_double &num) {  // не придумал вывода числом(позже будет)
  o << num.numerator << "/" << num.denominator;
  return o;
}

big_double::big_double(double num) {
  std::string temp = std::to_string(num);
  input_in_arr(temp, *this);
}

big_double big_double::operator+(const big_double &other) {
  big_double temp;
  if (this->denominator == other.denominator) {
    temp.denominator = this->denominator;
    temp.numerator = this->numerator + other.numerator;
  } else {
    temp.denominator = this->denominator * other.denominator;
    temp.numerator = this->numerator * other.denominator + other.numerator * this->denominator;
  }
  return temp;
}

big_double big_double::operator-(const big_double &other) {
  big_double temp;
  if (this->denominator == other.denominator) {
    temp.denominator = this->denominator;
    temp.numerator = this->numerator - other.numerator;
  } else {
    temp.denominator = this->denominator * other.denominator;
    temp.numerator = this->numerator * other.denominator - other.numerator * this->denominator;
  }
  return temp;
}

big_double big_double::operator*(const big_double &other) {
  big_double temp;
  temp.numerator = this->numerator * other.numerator;
  temp.denominator = this->denominator * other.denominator;
  return temp;
}

big_double big_double::operator/(const big_double &other) {
  big_double temp;
  temp.numerator = this->numerator * other.denominator;
  temp.denominator = this->denominator * other.numerator;
  return temp;
}
