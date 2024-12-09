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

  Widget(std::initializer_list<bool> il) {
    std::cout << "fourth" << std::endl;
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
  
  
  /*
   * The compiler's mapping of curly initializers to std::initializer_list 
   * constructors is so strict that it dominates even when the 
   * best-matching std::initializer_list constructor cannot be called
   */
  Widget w3{10, 5.0}; // Error! Requires narrowing conversions
  // int and float cannot be represented with 'bool' type 
  // (compiler ignores first two constructors, even though they
  // second constructor fits perfectly!

  // Important: if there is no way to cast argument to initializer_list
  // type (e.g bool to std::string), compiler returns to normal overloading
  // resolution rules

  
  /*
   * what constructor will be called in this case? 
   * empty brackets means 'no arguments', so default
   * constructor will be called
   */
  Widget w4{}; 

  // Fun: If you want to call constructor with empty
  // initializer_list, use nested brackets, like:
  Widget w5({});
  Widget w6{{}}; // the same
}
