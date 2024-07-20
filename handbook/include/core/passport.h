#ifndef HANDBOOK_CORE_PASSPORT_H_
#define HANDBOOK_CORE_PASSPORT_H_

#include <iostream>
#include <string>
#include <functional>

struct Passport {
  std::string series;
  std::string number;
  
  inline bool operator==(const Passport& other) const {
    return series == other.series && number == other.number;
  }

  inline bool operator<(const Passport& other) const {
    if (series != other.series)
      return series < other.series;
    return number < other.number;
  }
};

namespace std {
  template<>
  struct hash<Passport> {
    std::size_t operator()(const Passport& passport) const {
      return std::hash<std::string>()(passport.series) ^ std::hash<std::string>()(passport.number);
    }
  };
}

inline std::ostream& operator<<(std::ostream& out, const Passport& passport) {
  return out << passport.series << ' ' << passport.number;
}

#endif // HANDBOOK_CORE_PASSPORT_H_
