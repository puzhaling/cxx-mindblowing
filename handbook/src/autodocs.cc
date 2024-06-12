#include <cassert>
#include <string>
#include <cstdint>
#include <algorithm>
#include <cctype>
#include <string_view>
#include <cmath>
#include "autodocs.h"

std::uint32_t CountWords(std::string_view s) {
	if (s.empty()) 
		return 0;

	bool in_spaces = true;
	std::size_t words_count = 0;

	std::size_t length = s.length();
	for (char ch : s) {
		if (std::isspace(ch)) {
			in_spaces = true;
    } else if (in_spaces) {
			++words_count;
			in_spaces = false;
		}
	}
	return words_count;
}

static inline std::uint32_t CountDigits(int number) {
	number = std::abs(number);
	std::size_t count = 0;
	while (number != 0) { 
		number /= 10; 
		count++; 
	}
	return count;
}

// FullName class:
FullName::FullName(const std::string& name, const std::string& surname) 
    : name_((assert(CheckCorrectness(name) && "INVALID NAME" ), name)), 
      surname_((assert(CheckCorrectness(surname) && "INVALID SURNAME"), surname)) 
{}

FullName::FullName(const FullName& copy) 
    : name_(copy.name_), 
      surname_(copy.surname_) 
{}

bool FullName::CheckCorrectness(std::string_view str) {
  static constexpr auto kAlphaChecker = [](char c) { return isalpha(c); };
	if (std::all_of(std::begin(str), std::end(str), kAlphaChecker)) 
		return true;
	return !str.empty();
}

const std::string& FullName::name() const {
  return name_;
}

const std::string& FullName::surname() const {
  return surname_;
}

void FullName::set_name(const std::string& name) {
  if (FullName::CheckCorrectness(name))
    name_ = name;
}

void FullName::set_surname(const std::string& surname) {
  if (FullName::CheckCorrectness(surname))
    surname_ = surname;
}

std::ostream& operator<<(std::ostream& out, const FullName& fullname) { 
  return out << fullname.name_ << ' ' << fullname.surname_; 
}

bool operator==(const FullName& a, const FullName& b) { 
	return a.name() == b.name() && a.surname() == b.surname(); 
}
bool operator!=(const FullName& a, const FullName& b) { 
	return !(a == b); 
}
bool operator<(const FullName& a, const FullName& b) {
  if (a.surname() == b.surname()) 
    return a.name() < b.name();
  return a.surname() < b.surname();
}
bool operator>(const FullName& a, const FullName& b) {
  if (a.surname() == b.surname()) 
    return a.name() > b.name();
  return a.surname() > b.surname();
}

// StateNumber class:
StateNumber::StateNumber(const std::string& s)
    : letters_((assert(CheckCorrectness(s) && "INVALID STATE_NUMBER"), std::string(1, s[0]) + s[4] + s[5])), 
      numbers_(static_cast<std::uint16_t>(std::stoi(std::string(1, s[1]) + s[2] + s[3]))) 
{}

StateNumber::StateNumber(const StateNumber& copy) 
    : letters_(copy.letters_), 
      numbers_(copy.numbers_) 
{}

bool StateNumber::CheckCorrectness(std::string_view s) { 
  return s.length() == 6 && isalpha(s[0]) && isdigit(s[1]) && isdigit(s[2]) && isdigit(s[3]) && isalpha(s[4]) && isalpha(s[5]); 
}

std::uint16_t StateNumber::numbers() const { 
  return numbers_;         
}

const std::string& StateNumber::letters() const { 
  return letters_;         
}

void StateNumber::set_numbers(std::uint16_t numbers) { 
  static constexpr short kMaxStateNumberValue = 999;
  if (numbers <= kMaxStateNumberValue) 
    numbers_ = numbers; 
}

void StateNumber::set_letters(const std::string& letters) {
	if (letters.length() != 3) 
		return;
	if (std::any_of(std::begin(letters), std::end(letters), [=](char ch) -> bool { return isdigit(ch); })) 
		return;

	std::string letters_copy(letters);
	std::transform(std::begin(letters_copy), std::end(letters_copy), std::begin(letters_copy), [&](char ch) { return std::tolower(ch); } );
	letters_ = letters_copy;
}

std::ostream& operator<<(std::ostream& out, const StateNumber& state_number) {
  return out << state_number.letters_ << ' ' << state_number.numbers_; 
}

bool operator==(const StateNumber& a, const StateNumber& b) { 
	return a.letters() == b.letters() && a.numbers() == b.numbers(); 
}
bool operator!=(const StateNumber& a, const StateNumber& b) { 
	return !(a == b); 
}
bool operator<(const StateNumber& a, const StateNumber& b) {
  if (a.letters() == b.letters()) 
    return a.numbers() < b.numbers();
  return a.letters() < b.letters();
}
bool operator>(const StateNumber& a, const StateNumber& b) {
  return !(a == b) && !(a < b);
}

// CarSpecs class:
CarSpecs::CarSpecs(const std::string& s) {
  static const auto upper_finder = [](char c){ return std::isupper(c); };
  int num_uppers = std::count_if(std::begin(s), std::end(s), upper_finder);
  if (s.empty() || !std::isupper(s.front()))
    throw std::runtime_error("invalid input string");
  else if (num_uppers != 2) 
    throw std::runtime_error("invalid input string");

  const auto pos = std::distance(std::begin(s), std::find_if(std::begin(s) + 1, std::end(s), [](char ch) -> bool { return std::isupper(ch); }));

  std::string brand = s.substr(0, pos);
  std::string model = s.substr(pos);

  std::cout << "brand: " << brand << ' ' << "model: " << model << '\n';
	brand_ = brand;
	model_ = model;
}

CarSpecs::CarSpecs(const CarSpecs& copy) 
    : model_(copy.model_), 
      brand_(copy.brand_) 
{}

bool CarSpecs::CheckCorrectness(std::string_view s) { 
  return std::count_if(std::begin(s), std::end(s), [](char ch) -> bool { return std::isupper(ch); }) == 2; 
}

const std::string& CarSpecs::model() const { 
  return model_; 
}

const std::string& CarSpecs::brand() const { 
  return brand_; 
}

void CarSpecs::set_model(const std::string& model) { 
  model_ = model; 
}

void CarSpecs::set_brand(const std::string& brand) { 
  brand_ = brand; 
}

std::ostream& operator<<(std::ostream& out, CarSpecs const& car_specs) { 
  return out << car_specs.brand_ << car_specs.model_; 
}

bool operator==(const CarSpecs& a, const CarSpecs& b) {
  return (a.brand() == b.brand()) && 
         (a.model() == b.model());
}
bool operator!=(const CarSpecs& a, const CarSpecs& b) {
  return !(a == b);
}
bool operator<(const CarSpecs& a, const CarSpecs& b) {
  if (a.model() < b.model())
    return true;
  return a.brand() < b.brand();
}
bool operator>(const CarSpecs& a, const CarSpecs& b) {
  return !(a == b) && !(a < b);
}

// AutoDocs class:
AutoDocs::AutoDocs(const AutoDocs& copy) 
    : fullname_(copy.fullname_), 
      state_number_(copy.state_number_), 
      car_specs_(copy.car_specs_), 
      id_(copy.id_), 
      request_(copy.request_) 
{}

AutoDocs::AutoDocs(const FullName& fullname, const StateNumber& state_number, const CarSpecs& car_specs, std::size_t request) 
    :	fullname_(fullname), 
      state_number_(state_number), 
      car_specs_(car_specs), 
      id_(AutoDocs::GenerateId()), 
      request_(request) 
{} 

std::uint32_t AutoDocs::iota_ = 1;

std::uint32_t AutoDocs::GenerateId() {
  return iota_++;
}

const FullName& AutoDocs::fullname() const {
  return fullname_;
}

const StateNumber& AutoDocs::state_number() const { 
  return state_number_; 
}

const CarSpecs& AutoDocs::car_specs() const { 
  return car_specs_;   
}

bool AutoDocs::Contains(std::size_t request) const {
	return request_ == request;
}

std::size_t AutoDocs::request() const { 
  return request_; 
}

std::uint32_t AutoDocs::id() const { 
  return id_; 
} 

/*
	calculate cout indent by checking first operand length and substracting it from kIndentWidth

	ALLIGNMENT_WIDTH:
	------------------------------------ 36 chars

	first/second operand's width:
	------------- 13 characters

	=> there are 36 - 13 = 23 characters left to print to achive desired indent width

	same logic is applied for second indent, that is placed between state number and id. 
	first we found how many digits there are in a state number. cause it's maximum size - 3,
	we print additional spaces, as if there is always 3 digit 'numbers_' 
*/
std::ostream& operator<<(std::ostream& out, const AutoDocs& autodocs) {
  constexpr static unsigned kIndentWidth = 30;
  constexpr static unsigned kCarNumberMaxDigitsCount = 3;

	std::size_t fullname_len(autodocs.fullname().name().length() + autodocs.fullname().surname().length()); 
	std::size_t spaces_count(static_cast<std::size_t>(kIndentWidth - fullname_len));
	out << "FullName: {";
	out << autodocs.fullname_ << '}';

	while (spaces_count--) 
		out << ' ';
	out << "StateNumber: {" << autodocs.state_number_ << '}';

	std::size_t num_digits_in_state_number(CountDigits(autodocs.state_number().numbers()));

	while (num_digits_in_state_number != kCarNumberMaxDigitsCount) 
		out << ' ';

	spaces_count = kIndentWidth;
	while (spaces_count--) 
		out << ' '; 
	out << "CarSpecs: {" << autodocs.car_specs() << '}';

	spaces_count = static_cast<std::size_t>(kIndentWidth - autodocs.car_specs().brand().length() - autodocs.car_specs().model().length());
	while (spaces_count--) 
		out << ' ';
	out << "request: " << autodocs.request();

	return out; 
}

bool operator==(const AutoDocs& a, const AutoDocs& b) { 
    return (a.fullname() == b.fullname()) &&
           (a.state_number() == b.state_number()) &&
           (a.car_specs() == b.car_specs()) &&
           (a.request() == b.request());    
}
bool operator!=(const AutoDocs& a, const AutoDocs& b) { 
	return !(a == b); 
}
bool operator<(const AutoDocs& a, const AutoDocs& b) {
	if (a.fullname() < b.fullname())
    return true;
  else if (a.state_number() < b.state_number())
    return true;
  else if (a.car_specs() < b.car_specs())
    return true;
  else if (a.request() < b.request())
    return true;
  return a.id() < b.id();
}
bool operator>(const AutoDocs& a, const AutoDocs& b) {
	return !(a == b) && !(a < b);
}

