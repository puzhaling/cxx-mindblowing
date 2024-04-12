
#ifndef AUTO_DOCS_H
#define AUTO_DOCS_H

#include <iostream>
#include <string_view>
#include <algorithm>
#include <cctype> // for std::tolower()
#include <cstdint> // for fixed-width integers

constexpr int MAX_THREE_DIGIT_NUMBER{ 999 };

std::uint32_t countWords(std::string_view s);

class FullName 
{
public:
	FullName() = delete;

	// class invariant : nor m_name and m_surname must be empty and contain numbers
	FullName(std::string_view name, std::string_view surname);

	friend std::ostream& operator<<(std::ostream& out, const FullName& fullName) { return out << fullName.m_name << ' ' << fullName.m_surname; }

	static bool isvalid(std::string_view str);

	const std::string&  getName()    const { return m_name;    }
	const std::string&  getSurname() const { return m_surname; };

	void setName   (std::string_view name)    { if (isvalid(name))    m_name = name;       }
	void setSurname(std::string_view surname) { if (isvalid(surname)) m_surname = surname; }

private:
	std::string m_name;
	std::string m_surname;
};

bool operator==(const FullName& a, const FullName& b);
bool operator!=(const FullName& a, const FullName& b);
bool operator< (const FullName& a, const FullName& b);
bool operator> (const FullName& a, const FullName& b);



class StateNumber 
{
public:
	StateNumber() = delete;

	// class invariant : string length == 6 && matches the number template
	StateNumber(std::string_view stateNumber);

	friend std::ostream& operator<<(std::ostream& out, const StateNumber& stateNumber) { return out << stateNumber.m_letters << ' ' << stateNumber.m_numbers; }

	static bool isvalid(std::string_view s) { return s.length() == 6 && isalpha(s[0]) && isdigit(s[1]) && isdigit(s[2]) && isdigit(s[3]) && isalpha(s[4]) && isalpha(s[5]); }

	char             getFront()    const { return m_letters.front(); }
	std::uint16_t    getNumbers()  const { return m_numbers;         }
	std::string_view getLetters()  const { return m_letters;         }

	void setNumbers (std::uint16_t numbers) { if (numbers <= MAX_THREE_DIGIT_NUMBER) m_numbers = numbers; }
	void setLetters(std::string_view letters);

private:
	std::string   m_letters;
	std::uint16_t m_numbers;
};

bool operator==(const StateNumber& a, const StateNumber& b);
bool operator!=(const StateNumber& a, const StateNumber& b);
bool operator< (const StateNumber& a, const StateNumber& b);
bool operator> (const StateNumber& a, const StateNumber& b);



class CarSpecs 
{
public:
	CarSpecs() = delete;

	// input file consist the following input: BrandModel
	//                                           /   \
	//					 Brand  Model
	//					    |      |
	//					m_brand m_model
	CarSpecs(std::string_view s);

	friend std::ostream& operator<<(std::ostream& out, const CarSpecs& carSpecs) { return out << carSpecs.m_brand << carSpecs.m_model; }

	static bool isvalid(std::string_view s) { return std::count_if(std::begin(s), std::end(s), [](char ch) -> bool { return std::isupper(ch); }) == 2; };

	const std::string&  getModel() const { return m_model; }
	const std::string&  getBrand() const { return m_brand; }

	void setModel(std::string& model) { m_model = model; }
	void setBrand(std::string& brand) { m_brand = brand; }
	
private:
	std::string m_model;
	std::string m_brand;
};



class AutoDocs 
{
private:
	static inline std::uint32_t s_id{ 1 };
	
public:
	static std::uint32_t generateID() { return s_id++; }

	AutoDocs() = delete;

	AutoDocs(const FullName& fullName, const StateNumber& stateNumber, const CarSpecs& carSpecs);

	friend std::ostream& operator<<(std::ostream& out, const AutoDocs& autoDocs);

	const FullName&      getFullName()    const  { return m_fullName; }
	const StateNumber&   getStateNumber() const  { return m_stateNumber; }
	const CarSpecs&      getCarSpecs()    const  { return m_carSpecs; }
	std::uint32_t  		 getID() 		  const  { return m_id; }

private:
	std::uint32_t m_id;
	FullName      m_fullName;
	StateNumber   m_stateNumber;
	CarSpecs      m_carSpecs;
};

std::ostream& operator<<(std::ostream& out, const AutoDocs& autoDocs);

bool operator==(const AutoDocs& a, const AutoDocs& b);
bool operator!=(const AutoDocs& a, const AutoDocs& b);
bool operator< (const AutoDocs& a, const AutoDocs& b);
bool operator> (const AutoDocs& a, const AutoDocs& b);

#endif // AUTO_DOCS_H
