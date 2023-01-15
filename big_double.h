#pragma once

#include "big_int.h"

class big_double;

std::ostream &operator<<(std::ostream &o, const big_double &num);

std::istream &operator>>(std::istream &in, big_double &num);

class big_double {
public:
  big_double() = default;;

  explicit big_double(double num);

  big_double operator+(const big_double &other);

  big_double operator-(const big_double &other);

  big_double operator*(const big_double &other);

  big_double operator/(const big_double &other);

  friend std::ostream &operator<<(std::ostream &o, const big_double &num);

  friend std::istream &operator>>(std::istream &in, big_double &num);

  friend void input_in_arr(std::string &temp, big_double &num);

private:
  big_int numerator;
  big_int denominator;
};
