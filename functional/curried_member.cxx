#include <iostream>
#include <string>

template <typename MemberFunc>
auto carried_member(MemberFunc f) {
  return [f](auto* class_inst) {
    // imposible, since i cannot get implicit this pointer
    // that always passed as a first argument in member
    // funcs. or, maybe, there is a way?
    return f(class_inst);
  };
}

int main() {
  auto carried = carried_member(&std::string::length);
  std::string str = "Hello\n"; 
  std::cout << carried(&str) << std::endl;
}
