
#include <cassert>
#include "autodocs.hpp"

constexpr int INDENT_WIDTH{ 30 };
constexpr int CAR_NUMBER_MAXIMUM_DIGITS_COUNT{ 3 };


std::uint32_t countWords(std::string_view s) 
{
	if (s.empty()) {
		return 0;
	}

	bool inSpaces{ true };
	std::size_t wordsCount{};

	std::size_t length{ s.length() };
	for (char ch : s) 
	{
		if (std::isspace(ch)) 
		{
			inSpaces = true;
		}
		else if (inSpaces) 
		{
			++wordsCount;
			inSpaces = false;
		}
	}

	return wordsCount;
}

static std::uint32_t countDigits(int number) 
{
	number = std::abs(number);
	std::size_t count{ 0 };

	while (number != 0) 
	{ 
		number /= 10; 
		count++; 
	}

	return count;
}





// FULL NAME CLASS 

FullName::FullName(std::string_view name, std::string_view surname)
	: m_name   { ( assert( isvalid(name)    && "INVALID NAME" ),    name)    }
	, m_surname{ ( assert( isvalid(surname) && "INVALID SURNAME" ), surname) } 
{}

bool FullName::isvalid(std::string_view str) 
{
	if (std::all_of(std::begin(str), std::end(str), [=](char ch) -> bool { return isalpha(ch); })) 
	{
		return true;
	}

	return !str.empty();
}

bool operator==(const FullName& a, const FullName& b) 
{ 
	return a.getName() == b.getName() && a.getSurname() == b.getSurname(); 
}

bool operator!=(const FullName& a, const FullName& b) 
{ 
	return !(a == b); 
}

bool operator<(const FullName& a, const FullName& b) 
{
    if (a.getSurname() == b.getSurname()) 
    {
        return a.getName() < b.getName();
    }
    return a.getSurname() < b.getSurname();
}

bool operator>(const FullName& a, const FullName& b) 
{
    if (a.getSurname() == b.getSurname()) 
    {
        return a.getName() > b.getName();
    }
    return a.getSurname() > b.getSurname();
}






// STATE NUMBER CLASS:

StateNumber::StateNumber(std::string_view stateNumber)
	: m_letters{ ( assert( isvalid(stateNumber) && "INVALID STATE_NUMBER" ), (std::string(1, stateNumber[0]) + stateNumber[4] + stateNumber[5]) ) }
	, m_numbers{ static_cast<std::uint16_t>(std::stoi(std::string(1, stateNumber[1]) + stateNumber[2] + stateNumber[3])) }
{}

void StateNumber::setLetters(std::string_view letters) 
{
	if (letters.length() != 3) 
	{ 
		return;
	}

	if (std::any_of(std::begin(letters), std::end(letters), [=](char ch) -> bool { return isdigit(ch); })) 
	{
		return;
	}

	std::string letters_copy{ letters };
	std::transform(std::begin(letters_copy), std::end(letters_copy), std::begin(letters_copy), [&](char ch) { return std::tolower(ch); } );
	m_letters = letters_copy;
}

bool operator==(const StateNumber& a, const StateNumber& b) 
{ 
	return a.getLetters() == b.getLetters() && a.getNumbers() == b.getNumbers(); 
}

bool operator!=(const StateNumber& a, const StateNumber& b) 
{ 
	return !(a == b); 
}

bool operator<(const StateNumber& a, const StateNumber& b) 
{
    if (a.getLetters() == b.getLetters()) 
    {
        return a.getNumbers() < b.getNumbers();
    }
    return a.getLetters() < b.getLetters();
}

bool operator>(const StateNumber& a, const StateNumber& b) 
{
    if (a.getLetters() == b.getLetters()) 
    {
        return a.getNumbers() > b.getNumbers();
    }
    return a.getLetters() > b.getLetters();
}





// CAR SPECS CLASS:

CarSpecs::CarSpecs(std::string_view s) 
{
	std::string brand_model{ s };
	std::string model{};
	std::string brand{};

	auto const pos{ std::distance(std::begin(s), std::find_if(std::begin(s)+1, std::end(s), [](char ch)-> bool { return std::isupper(ch); })) };

	brand = brand_model.substr(0, pos);
	model = brand_model.substr(pos);

	m_brand = brand;
	m_model = model;
}




// AUTO DOCS CLASS:

AutoDocs::AutoDocs(const FullName& fullName, const StateNumber& stateNumber, const CarSpecs& carSpecs) :	
	m_fullName{ fullName }, m_stateNumber{ stateNumber }, m_carSpecs{ carSpecs }, m_id{ AutoDocs::generateID() }
{}

/*
	calculate cout indent by checking first operand length and substracting it from INDENT_WIDTH

	ALLIGNMENT_WIDTH:
	------------------------------------ 36 chars

	first/second operand's width:
	------------- 13 characters

	=> there are 36 - 13 = 23 characters left to print to achive desired indent width

	same logic is applied for second indent, that is placed between state number and id. 
	first we found how many digits there are in a state number. cause it's maximum size - 3,
	we print additional spaces, as if there is always 3 digit 'm_numbers' 
*/
std::ostream& operator<<(std::ostream& out, const AutoDocs& autoDocs) 
{
	std::size_t fullNameLength{ autoDocs.m_fullName.getName().length() + autoDocs.m_fullName.getSurname().length() }; 
	std::size_t spacesCount{ static_cast<std::size_t>(::INDENT_WIDTH - fullNameLength) };

	out << "FullName: {";
	out << autoDocs.m_fullName << '}';

	while (spacesCount--) 
	{
		out << ' ';
	}

	out << "StateNumber: {" << autoDocs.m_stateNumber << '}';

	std::size_t stateNumberDigitsCount{ countDigits(autoDocs.m_stateNumber.getNumbers()) };

	while (stateNumberDigitsCount++ != ::CAR_NUMBER_MAXIMUM_DIGITS_COUNT) 
	{ 
		out << ' ';
	}

	spacesCount = ::INDENT_WIDTH;
	while (spacesCount--) 
	{
		out << ' ';
	}

	out << "CarSpecs: {" << autoDocs.m_carSpecs << '}';

	spacesCount = static_cast<std::size_t>(::INDENT_WIDTH - autoDocs.m_carSpecs.getBrand().length() - autoDocs.m_carSpecs.getModel().length());
	while (spacesCount--) 
	{
		out << ' ';
	}

	return out << "id: " << autoDocs.getID(); 
}

bool operator==(const AutoDocs& a, const AutoDocs& b) 
{ 
	return a.getFullName() == b.getFullName() && a.getStateNumber() == b.getStateNumber(); 
}

bool operator!=(const AutoDocs& a, const AutoDocs& b) 
{ 
	return !(a == b); 
}

bool operator<(const AutoDocs& a, const AutoDocs& b) 
{
    if (a.getFullName() == b.getFullName()) 
    {
        return a.getStateNumber() < b.getStateNumber();
    }
    return a.getFullName() < b.getFullName();
}

bool operator>(const AutoDocs& a, const AutoDocs& b) 
{
    if (a.getFullName() == b.getFullName()) 
    {
        return a.getStateNumber() > b.getStateNumber();
    }
    return a.getFullName() > b.getFullName();
}
