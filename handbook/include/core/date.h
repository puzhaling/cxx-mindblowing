#ifndef HANDBOOK_CORE_DATE_H_
#define HANDBOOK_CORE_DATE_H_

#include <iostream>
#include <string>

struct Date {
  std::string day;
  std::string month;
  std::string year;
  
  inline bool operator==(const Date& other) const {
    return day == other.day && month == other.month && year == other.year;
  }

  inline bool operator<(const Date& other) const {
    if (year != other.year)
      return year < other.year;
    if (month != other.month)
      return month < other.month;
    return day < other.day;
  }
};

inline std::ostream& operator<<(std::ostream& out, const Date& date) {
  return out << date.day << ' ' << date.month << ' ' << date.year;
}

#endif // HANDBOOK_CORE_DATE_H_
