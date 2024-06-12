#ifndef HANDBOOK_AUTODOCS_H_ 
#define HANDBOOK_AUTODOCS_H_

#include <iostream>
#include <string_view>
#include <cstdint> 

class FullName {
 public:
  FullName() = default;
  FullName(const FullName&);
  FullName(const std::string&, const std::string&); // class invariant : nor name_ and surname_ must be empty and contain numbers

  static bool CheckCorrectness(std::string_view);
  const std::string& name() const;
  const std::string& surname() const; 
  void set_name(const std::string&); 
  void set_surname(const std::string&); 

  friend std::ostream& operator<<(std::ostream&, const FullName&);

 private:
	std::string name_;
	std::string surname_;
};

class StateNumber {
 public:
	StateNumber() = default;
	StateNumber(const StateNumber&);
	StateNumber(const std::string&); // class invariant : string length == 6 && matches the number template

	static bool CheckCorrectness(std::string_view); 
	std::uint16_t numbers() const; 
	const std::string& letters() const; 
	void set_numbers (std::uint16_t numbers); 
	void set_letters(const std::string& letters);

	friend std::ostream& operator<<(std::ostream&, const StateNumber&); 

 private:
	std::string letters_;
	std::uint16_t numbers_;
};

class CarSpecs {
 public:
	CarSpecs() = default;
	CarSpecs(const CarSpecs&);
	CarSpecs(const std::string&);

	static bool CheckCorrectness(std::string_view);
	const std::string& model() const; 
	const std::string& brand() const; 
	void set_model(const std::string&); 
	void set_brand(const std::string&);
  
	friend std::ostream& operator<<(std::ostream&, const CarSpecs&); 

 private:
	std::string model_;
	std::string brand_;
};

class AutoDocs {
 public:
	AutoDocs() = default;
	AutoDocs(const AutoDocs&);
	AutoDocs(const FullName&, const StateNumber&, const CarSpecs&, std::size_t);

	static std::uint32_t GenerateId(); 
  bool Contains(std::size_t) const; 

	const FullName& fullname() const; 
	const StateNumber& state_number() const; 
	const CarSpecs& car_specs() const; 
	std::size_t request() const; 
	std::uint32_t id() const; 
	void set_request(std::size_t);

	friend std::ostream& operator<<(std::ostream&, const AutoDocs&);
    
 private:
	static std::uint32_t iota_;
	FullName fullname_;
	StateNumber state_number_;
	CarSpecs car_specs_;
	std::uint32_t id_;
	std::size_t request_;
};

bool operator==(const FullName&, const FullName&);
bool operator!=(const FullName&, const FullName&);
bool operator<(const FullName&, const FullName&);
bool operator>(const FullName&, const FullName&);

bool operator==(const StateNumber&, const StateNumber&);
bool operator!=(const StateNumber&, const StateNumber&);
bool operator<(const StateNumber&, const StateNumber&);
bool operator>(const StateNumber&, const StateNumber&);

bool operator==(const CarSpecs&, const CarSpecs&);
bool operator!=(const CarSpecs&, const CarSpecs&);
bool operator<(const CarSpecs&, const CarSpecs&);
bool operator>(const CarSpecs&, const CarSpecs&);

bool operator==(const AutoDocs&, const AutoDocs&);
bool operator!=(const AutoDocs&, const AutoDocs&);
bool operator<(const AutoDocs&, const AutoDocs&);
bool operator>(const AutoDocs&, const AutoDocs&);

#endif // HANDBOOK_AUTODOCS_H_ 
       
