#ifndef HANDBOOK_CORE_CARSPEC_H_
#define HANDBOOK_CORE_CARSPEC_H_

#include <iostream>
#include <string>

struct CarSpec {
  std::string make;
  std::string model;
  
  inline bool operator==(const CarSpec& other) const {
    return make == other.make && model == other.model;
  }

  inline bool operator<(const CarSpec& other) const {
    if (make != other.make)
      return make < other.make;
    return model < other.model;
  }
};

inline std::ostream& operator<<(std::ostream& out, const CarSpec& carspec) {
  return out << carspec.make << ' ' << carspec.model;
}

#endif // HANDBOOK_CORE_CARSPEC_H_
