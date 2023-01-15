#include "big_double.h"

int main() {
  try {
    big_int a, b;
    std::cin >> a >> b;
    std::cout << a + b << std::endl;
    std::cout << a - b << std::endl;
    std::cout << a * b << std::endl;
    std::cout << a / b << std::endl;

    big_double aa, bb;
    std::cin >> aa >> bb;
    std::cout << aa + bb << std::endl;
    std::cout << aa - bb << std::endl;
    std::cout << aa * bb << std::endl;
    std::cout << aa / bb << std::endl;
    std::cout << aa + big_double(6.5) << std::endl;
  }
  catch (int e) {
    std::cout << e << std::endl;
  }
  return 0;
}
