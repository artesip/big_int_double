#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <cmath>

class big_double;

class big_int;

const int plus_sign = 1;

const int minus_sign = -1;

std::ostream &operator<<(std::ostream &o, const big_int &num);

std::istream &operator>>(std::istream &in, big_int &num);

class big_int {
public:
  big_int() = default;;

  explicit big_int(int num);

  bool operator<(const big_int &other) const;

  bool operator>(const big_int &other) const;

  bool operator==(const big_int &other) const;

  big_int operator+(const big_int &other) const;

  big_int operator-(const big_int &other) const;

  big_int operator*(const big_int &other) const;

  big_int operator/(const big_int &other) const;

  big_int &operator=(const big_int &other);

  big_int operator-() const;

  friend std::ostream &operator<<(std::ostream &o, const big_int &num);

  friend std::istream &operator>>(std::istream &in, big_int &num);

private:
  std::vector<int16_t> digit_arr;
  bool is_negative = false;

  void spec_copy_arr(big_int &temp, const big_int &from, int min_sizeof_big, const int &sign) const;

  friend void remove_start_zeroes(big_int &num);

  friend std::istream &operator>>(std::istream &in, big_double &num); // для big_double
  friend void input_in_arr(std::string &temp, big_double &num);
};
