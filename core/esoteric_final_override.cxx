#include <iostream>

class Base {
public:
  virtual void foo() final {
    std::cout << "non overridable" << std::endl;
  }
};

class Derived : public Base {
public:
  // override and final are c++ contextual keywords, 
  // so they can be used directly out of context
  // (override considers as keyword only in the end of
  // member function)
  void override() {
    std::cout << "override func" << std::endl;
  }

/* ERROR : trying to override final function
  void foo() override 
    {
    }
*/
};

int main()
{
  Derived *d = new Derived{};
  static_cast<Base*>(d)->foo();
  d->override();

}
