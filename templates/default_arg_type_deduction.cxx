template <typename T>
void f(T = ""); // not working for, for example, f();
// impossible to deduce T

// for such behaviour support, you need to declare default value for
// template type parameter:
template <typename T = std::string>
void f(T = "");
// f() - OK

