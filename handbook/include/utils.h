#ifndef HANDBOOK_UTILS_H_
#define HANDBOOK_UTILS_H_

#include <filesystem>

#include "core/carspec.h"
#include "core/date.h"
#include "core/fullname.h"
#include "core/passport.h"

inline bool PathIsValid(const std::string& path) {
  return std::filesystem::exists(path) && std::filesystem::is_regular_file(path);
}

bool IsValid(const CarSpec&);
bool IsValid(const Date&);
bool IsValid(const FullName&);
bool IsValid(const Passport&);

#endif // HANDBOOK_UTILS_H_
