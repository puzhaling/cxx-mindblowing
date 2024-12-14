
// c++11 restrict constexpr functions to use a single return instruction
constexpr int pow(int base, int exp) noexcept
{
  return (exp == 0 ? 1 : base * pow(base, exp - 1));
}


// in c++14 restriction to constexpr functions implementation have
// become significantly weaker. now it can have implementation
// like this
constexpr int pow(int base, int exp) noexcept
{
  auto result = 1;
  for (int i = 1; i < exp; ++i) result *= base;
  return result;
}

// constexpr functions are restricted in to get and return 
// only literal type, that are types that can have values, 
// defined at compile time

// "The constructors with a constexpr specifier make their
// type a literal type"




// UPDATE:
// in c++11 2 restrictions does not allow to declare setters
// as constexpr functions:
// 1) in c++11 constexpr member functions are implicitly const
// 2) they have void return type and void does not considered
//    as literal type in c++11

// all the above restrictions are removed in c++14

