#include <iostream>
#include <print>
#include <string>

int main() {

  std::print("Hello, World! from std::print\n");
  std::cout << "Hello, World! from std::cout" << std::endl;

  std::cin.get();
  return 0;
}
