#include <iostream>

auto print_person_cd(const person_t &person) 
{
  return [&](std::ostream &out) {
    return [&](person_t::output_format_t format) {
      print_person(person, out, format);
    };
  };  
}

using std::cout;

// still unary, but allow passing more than once
// argument at a time
auto print_person_cs = make_carried(print_person);

print_person_cs(martha, cout, person_t::full_name);
print_person_cs(martha)(cout, person_t::full_name);
print_person_cs(martha, cout)(person_t::full_name);
print_person_cs(martha)(cout)(person_t::full_name);

auto print_martha = print_person_cd(martha);
print_martha(cout, person_t::name_only);

auto print_martha_to_cout =
        print_person_cd(martha, cout);
print_martha_to_cout(person_t::name_only);
