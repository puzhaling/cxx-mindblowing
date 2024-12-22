#include <string>

class Foo {
public:
  
  explicit Foo(const std::string text)
  : value(std::move(text)) // copies, not moves
  {
  }

private:
  std::string value;
};


// move makes unconditional cast to rvalue,
// but the code above does not move value of text
// to private member variable 'value', because
// constructor parameter is declared as 'const' and
// we can not pass rvalue to const string to string 
// move constructor, because it violate rule of constness,
// but it is allowed to tie lvalue ref to const with const rvalue,
// so copy constructor of std::string is called -_-

/*****************************

class string {
public:

  string(const string& rhs);
  string(string&& rhs);

};

*****************************/

/*
 * behaviour like this is important for 'const' support.
 * in general case, move constructor modifies passed object, so
 * language must restrict passing const objects to functions
 * (like move constructors), which can modify their parametres
 */
 
/* 
 * moral: if you want to use move semantics on objects,
 * not declare them as const. Also, all move actions on const
 * objects transforms into copy operations silently, so be
 * carefull
 */
