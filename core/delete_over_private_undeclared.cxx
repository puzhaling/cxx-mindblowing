class Foo {
public:

// ...

private:
  // pre c++11 way to prevent any 
  // functions from calling them

  // they are intentionally left undefined for
  // the cases when member functions or friend classes
  // ever tried to call them, this code wont be linked (but compiled
  // with no problems) :(
  Foo(const Foo& );
  Foo& operator=(const Foo&);
};


// c++11 way to do the same but in more 'deep' way.
// any tries to call these functions lends to compilation errors
// in contrast to declaring them as private, where errors occurs
// on linking stage
class Foo {
public:
  Foo(const Foo& ) = delete;
  Foo& operator=(const Foo&) = delete;
};
// by convention, deleted functions are declared as public and
// there is a reason. when user code tries to call member function,
// c++ firstly tries to detect this function accessebility (public, private)
// before detecting it's deleted or not. (some compilers may tell you
// that you are trying to call private function but it doesn't matter
// when you try to call deleted function



// additional advantage of delete is that any functions can be 
// declared as deleted (not only member functions in the case of private)
bool isLucky(int number);
bool isLucky(char) = delete;
bool isLucky(bool) = delete; // functions that don't make sense (isLucky('a')?
// whaaaaat?)
bool isLucky(double) = delete;


// another cool trick is that delete function (but not function, 
// declared as private) can be used to is to prevent usage of 
// tempate instantiation that must be forbidden
template <class T>
void processPointer(T* ptr);

template<>
void processPointer<void>(void *) = delete; // delete specialization

template<>
void processPointer<char>(char *) = delete;



