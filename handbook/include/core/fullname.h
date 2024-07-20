#ifndef HANDBOOK_CORE_FULLNAME_H_
#define HANDBOOK_CORE_FULLNAME_H_

#include <iostream>
#include <string>

struct FullName {
  std::string surname;
  std::string name;
  std::string patronymic;
  
  inline bool operator==(const FullName& other) const {
    return surname == other.surname && name == other.name && 
      patronymic == other.patronymic;
  }

  inline bool operator!=(const FullName& other) const {
    return !operator==(other); 
  }

  inline bool operator<(const FullName& other) const {
    if (name != other.name)
      return name < other.name;
    else if (surname != other.surname)
      return surname < other.surname;
    return patronymic < other.patronymic;
  }
};

inline std::ostream& operator<<(std::ostream& out, const FullName& fullname) {
  return out << fullname.surname << ' ' << fullname.name << ' ' << fullname.patronymic;
}

#endif // HANDBOOK_CORE_FULLNAME_H
