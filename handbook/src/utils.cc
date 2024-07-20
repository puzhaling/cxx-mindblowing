#include <iostream>    // for std::cerr;
#include <algorithm>   // for std::all_of()
#include <cctype>      // for std::isupper() && std::islower() && std::isdigit()

#include "utils.h"

bool IsValid(const CarSpec& carspec) {
  bool first = !carspec.make.empty() && std::isalpha(carspec.make.front()) && std::isupper(carspec.make.front()) && 
    (carspec.make.length() > 1) && std::all_of(carspec.make.begin() + 1, carspec.make.end(), [](char ch) {
        return std::isalpha(ch) || std::isdigit(ch); }); 

  bool second = !carspec.model.empty() && std::isalpha(carspec.make.front()) && std::isupper(carspec.model.front()) && 
    (carspec.model.length() > 1) && std::all_of(carspec.model.begin() + 1, carspec.model.end(), [](char ch) {
        return std::isalpha(ch) || std::isdigit(ch); }); 

  if (first && second)
    return true;

  std::cerr << "Error: invalid carspec." << std::endl;
  return false;
}

bool IsValid(const Date& date) {
  bool first = !date.day.empty() && (std::stoi(date.day) <= 31) && 
    std::all_of(date.day.begin(), date.day.end(), 
      [](char ch) { return std::isdigit(ch); });
  bool second = !date.month.empty() && (std::stoi(date.month) <= 12) && 
    std::all_of(date.month.begin(), date.month.end(), 
      [](char ch) { return std::isdigit(ch); });
  bool third = !date.year.empty() && std::all_of(date.year.begin(), date.year.end(), 
      [](char ch) { return std::isdigit(ch); });

  if (first && second && third)
    return true;

  std::cerr << "Error: invalid date." << std::endl;
  return false;
}

bool IsValid(const FullName& fullname) {
  bool first = (fullname.name.length() > 1) && std::isupper(fullname.name.front()) &&
    std::all_of(fullname.name.begin() + 1, fullname.name.end(), 
        [](char ch) { return std::isalpha(ch) && std::islower(ch); });

  bool second = (fullname.surname.length() > 1) && std::isupper(fullname.surname.front()) && 
    std::all_of(fullname.surname.begin() + 1, fullname.surname.end(), 
      [](char ch) { return std::isalpha(ch) && std::islower(ch); });

  bool third = (fullname.patronymic.length() > 1) && std::isupper(fullname.patronymic.front()) && 
    std::all_of(fullname.patronymic.begin() + 1, fullname.patronymic.end(), 
      [](char ch) { return std::isalpha(ch) && std::islower(ch); });

  if (first && second && third)
    return true;

  std::cerr << "Error: invalid fullname." << std::endl;
  return false;
}

bool IsValid(const Passport& passport) {
  bool first = (passport.series.length() == 4) && std::all_of(
      passport.series.begin(), passport.series.end(), [](char ch) { return std::isdigit(ch); }) &&
    (std::stoi(passport.series.substr(0, 2)) <= 12);
  bool second = (passport.number.length() == 6) && std::all_of(
      passport.series.begin(), passport.series.end(), [](char ch) { return std::isdigit(ch); });
  
  if (first && second)
    return true;

  std::cerr << "Error: invalid passport" << std::endl;
  return false;
}
