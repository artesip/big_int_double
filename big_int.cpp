#include "big_int.h"

big_int::big_int(int num) {
    while (num > 0) {
        this->digit_arr.push_back(num % 10);
        num /= 10;
    }
}

size_t min(size_t first, size_t second) {
    return first < second ? first : second;
}

size_t max(size_t first, size_t second) {
    return first < second ? second : first;
}

void remove_start_zeroes(big_int &num) {
    if (num.digit_arr.size() > 1) {
        while (num.digit_arr[num.digit_arr.size() - 1] == 0 && num.digit_arr.size() > 1) {
            num.digit_arr.pop_back();
        }
    }
}

std::ostream &operator<<(std::ostream &o, const big_int &num) {
    if (num.is_negative) {
        o << "-";
        if (num.digit_arr.size() == 1 && num.digit_arr[0] == 0) {
            o << 0;
            return o;
        }

    }
    for (int i = num.digit_arr.size() - 1; i >= 0; --i) {
        o << num.digit_arr[i];
    }
    return o;
}

std::istream &operator>>(std::istream &in, big_int &num) {
    std::string temp;
    in >> temp;
    int i = 0;
    if (temp[0] == '-') {
        num.is_negative = true;
        i += 1;
    }
    for (; i < temp.size(); ++i) num.digit_arr.push_back(atoi(temp.substr(i, 1).c_str()));
    for (int j = 0; j < num.digit_arr.size() / 2; ++j) {
        std::swap(num.digit_arr[j], num.digit_arr[num.digit_arr.size() - 1 - j]);
    }
    return in;
}

big_int &big_int::operator=(const big_int &other) {
    if (digit_arr.size() != other.digit_arr.size()) {
        digit_arr.resize(other.digit_arr.size());
    }
    for (int i = 0; i < digit_arr.size(); ++i) {
        digit_arr[i] = other.digit_arr[i];
    }
    this->is_negative = other.is_negative;
    return *this;
}

big_int big_int::operator-() const {
    big_int temp = *this;
    temp.is_negative = !temp.is_negative;
    return temp;
}

bool big_int::operator==(const big_int &other) const {
    return !(*this < other || *this > other);
}

bool big_int::operator<(const big_int &other) const {
    if (this->is_negative) {
        if (other.is_negative) {
            return (-*this) < (-other);
        }
        return true;
    } else if (other.is_negative) {
        return false;
    } else if (digit_arr.size() != other.digit_arr.size()) {
        return digit_arr.size() < other.digit_arr.size();
    } else {
        for (int i = this->digit_arr.size() - 1; i >= 0; --i) {
            if (digit_arr[i] != other.digit_arr[i])
                return digit_arr[i] < other.digit_arr[i];
        }
    }
    return false;
}

bool big_int::operator>(const big_int &other) const {
    return other < *this;
}

void big_int::spec_copy_arr(big_int &temp, const big_int &from, int min_sizeof_big, const int &sign) const {
    int temp_start_size = temp.digit_arr.size();
    for (int i = min_sizeof_big; i < temp_start_size; ++i) {
        temp.digit_arr[i] += from.digit_arr[i];
        if (temp.digit_arr[i] >= 10 || temp.digit_arr[i] < 0) {
            if (i + 1 < temp.digit_arr.size()) {
                temp.digit_arr[i] -= 10 * sign;
                temp.digit_arr[i + 1] += 1 * sign;
            } else {
                temp.digit_arr.push_back(0);
                temp.digit_arr[i] -= 10 * sign;
                temp.digit_arr[i + 1] += 1 * sign;
            }
        }
    }
}

big_int big_int::operator+(const big_int &other) const {
    if (other.is_negative) {
        if (this->is_negative) {
            return -((-*this) + (-other));
        } else {
            return (*this - (-other));
        }
    } else if (this->is_negative) {
        return (other - (-*this));
    }

    int min_sizeof_big = min(digit_arr.size(), other.digit_arr.size());
    int max_sizeof_big = max(digit_arr.size(), other.digit_arr.size());
    big_int temp;
    temp.digit_arr.resize(max_sizeof_big);

    for (int i = 0; i < min_sizeof_big; ++i) {
        temp.digit_arr[i] += digit_arr[i] + other.digit_arr[i];
        if (temp.digit_arr[i] >= 10) {
            temp.digit_arr[i] -= 10;
            if (i + 1 == temp.digit_arr.size()) {
                temp.digit_arr.push_back(1);
            } else {
                temp.digit_arr[i + 1] += 1;
            }
        }
    }
    if (temp.digit_arr.size() <= max_sizeof_big) {
        spec_copy_arr(temp, *this, min_sizeof_big, plus_sign);
    } else if (temp.digit_arr.size() <= min_sizeof_big) {
        spec_copy_arr(temp, other, min_sizeof_big, plus_sign);
    }
    remove_start_zeroes(temp);

    return temp;
}

big_int big_int::operator-(const big_int &other) const {
    if (other.is_negative) {
        return (*this + (-other));
    } else if (this->is_negative) {
        return -((-*this) + other);
    } else if (*this < other) {
        return -(other - *this);
    }

    int min_sizeof_big = min(digit_arr.size(), other.digit_arr.size());
    int max_sizeof_big = max(digit_arr.size(), other.digit_arr.size());
    big_int temp;
    temp.digit_arr.resize(max_sizeof_big);

    for (int i = 0; i < min_sizeof_big; ++i) {
        temp.digit_arr[i] += digit_arr[i] - other.digit_arr[i];
        if (temp.digit_arr[i] < 0) {
            temp.digit_arr[i] += 10;
            temp.digit_arr[i + 1] -= 1;
        }
    }
    if (digit_arr.size() == max_sizeof_big) {
        spec_copy_arr(temp, *this, min_sizeof_big, minus_sign);
    } else {
        spec_copy_arr(temp, other, min_sizeof_big, minus_sign);
    }
    remove_start_zeroes(temp);

    return temp;
}

big_int big_int::operator*(const big_int &other) const {
    big_int temp;
    temp.digit_arr.resize(this->digit_arr.size() + other.digit_arr.size());
    temp.is_negative = this->is_negative != other.is_negative;
    for (int i = 0; i < other.digit_arr.size(); ++i) {
        for (int j = 0; j < this->digit_arr.size(); ++j) {
            temp.digit_arr[j + i] += other.digit_arr[i] * this->digit_arr[j];
            while (temp.digit_arr[j + i] >= 10) {
                temp.digit_arr[j + i] -= 10;
                temp.digit_arr[j + i + 1] += 1;
            }
        }
    }
    remove_start_zeroes(temp);

    return temp;
}

big_int big_int::operator/(const big_int &other) const {
    if (this->is_negative) {
        return -((-*this) / other);
    } else if (other.is_negative) {
        return -((*this) / (-other));
    }
    big_int ans;
    big_int remainder;
    remainder.digit_arr.push_back(0);
    ans.is_negative = this->is_negative != other.is_negative;
    if (other.digit_arr.size() == 1 && other.digit_arr[0] == 0) {
        throw -1;
    } else if (other.digit_arr.size() == 1 && other.digit_arr[0] == 1) {
        return *this;
    } else if (*this == other) {
        return big_int(1);
    } else if (*this < other) {
        ans.digit_arr.push_back(0);
        return ans;
    } else {
        int cursor = 0;
        while (cursor <= digit_arr.size() - 1) {
            big_int temp;
            temp.digit_arr.resize(other.digit_arr.size());
            int k = temp.digit_arr.size() - 1;
            int tempr = cursor;
            for (int &i = cursor;
                 i < tempr + other.digit_arr.size() || temp < other; ++i) {  // берем первые число для деления
                if (i < digit_arr.size())
                    temp.digit_arr[k--] += this->digit_arr[this->digit_arr.size() - 1 - i];
                else {
                    for (int j = 0; j < temp.digit_arr.size() / 2; ++j) {
                        std::swap(temp.digit_arr[j], temp.digit_arr[j + 1]);
                    }
                    temp.digit_arr.pop_back();
                    for (int j = 0; j < temp.digit_arr.size() / 2; ++j) {
                        std::swap(temp.digit_arr[j], temp.digit_arr[j + 1]);
                    }
                    break;
                }
            }
            for (int i = 0; i < remainder.digit_arr.size(); ++i) {
                temp.digit_arr.push_back(remainder.digit_arr[i]);
            }
            remove_start_zeroes(temp);
            if (temp < other && cursor < digit_arr.size()) {
                temp.digit_arr.resize(other.digit_arr.size() + 1);
                for (int i = temp.digit_arr.size() - 1; i > 0; --i) {
                    std::swap(temp.digit_arr[i], temp.digit_arr[i - 1]);
                }
                temp.digit_arr[0] += this->digit_arr[this->digit_arr.size() - cursor - 1];
                ++cursor;
            }
            int quotient = 0;
            while (temp > big_int(0)) {
                temp = temp - other;
                ++quotient;
            }
            temp = temp + other;
            --quotient;
            remove_start_zeroes(temp);
            remainder = temp;
            ans.digit_arr.push_back(quotient);
        }
        for (int j = 0; j < ans.digit_arr.size() / 2; ++j) {
            std::swap(ans.digit_arr[j], ans.digit_arr[j + 1]);
        }
        for (int i = 0; i < ans.digit_arr.size(); ++i) {
            if (ans.digit_arr[i] >= 10) {
                ans.digit_arr[i] -= 10;
                if (i + 1 == ans.digit_arr.size()) {
                    ans.digit_arr.push_back(1);
                } else {
                    ans.digit_arr[i + 1] += 1;
                }
            }
        }
    }
    remove_start_zeroes(ans);

    return ans;
}
