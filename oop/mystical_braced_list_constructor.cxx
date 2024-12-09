#include <iostream>
#include <vector>
#include <initializer_list>

class Widget {
public:
  Widget(int i, bool b) {
    std::cout << "first" << std::endl;
  }
  
  Widget(int i, double d) {
    std::cout << "second" << std::endl;
  }

  Widget(std::initializer_list<double> il) {
    std::cout << "third" << std::endl;
  }
};


int main()
{
  /*
   * if one of the constructors is declared as constructor
   * that accepts std::initializer_list<T>, compiler 
   * prefers strictly overloading with std::initializer_list<T> another
   * constructors. this means that even though other constructors may 
   * have a better match, the compiler will take every opportunity 
   * to interpret the initializer as std::initilizer_list<T>
  */
  Widget w1 = {1, true}; // third
  Widget w2(10, true); // first
}
