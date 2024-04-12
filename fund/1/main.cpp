// 2.1
// добавленное поле: {марка и модель транспортного средства}
// поиск по: фио, {марка и модель}
// алгоритм поиска: рабин-карп, бойер-мур

#include <string_view>
#include <string>
#include <cstdint> // for fixed-width integers
#include <cassert> 
#include <cctype> // for isalpha() and isspace()
#include <iostream>
#include <sstream>
#include <fstream>
#include <limits>
#include <vector>
#include <stdexcept>

#include "autodocs.hpp"
#include "search.hpp"
#include "args_parser.hpp"

constexpr auto FULLNAME_MAX_LENGTH{ 30 };
constexpr auto CAR_NUMBER_MAXIMUM_DIGITS_COUNT{ 3 };
constexpr auto INDENT_WIDTH{ 10 };

// default patterns count
std::uint16_t ge_patternCount1{ 1 };
std::uint16_t ge_patternCount2{ 1 };

 
static void readFromTo
(std::ifstream& inputStream, std::vector<AutoDocs>& docsContainer, std::size_t N) 
{
	std::string line{};
	while (N-- && !inputStream.eof()) 
	{
		std::getline(inputStream, line, '\n');
		std::istringstream lineBuffer{ line };

		if (line.empty() || countWords(line) != 4) 
		{
			continue;
		}

		std::string name{};
		std::string surname{};
		std::string stateNumber{};
		std::string brandModel{};

		std::uint16_t counter{ 1 };

		std::string word{};
		while (lineBuffer >> word) 
		{
			switch (counter++) 
			{
			case 1:
				if (FullName::isvalid(word)) 
				{
					name = word;
				}
				break;
			case 2: 
				if (FullName::isvalid(word))
				{
					surname = word;
				}
				break;
			case 3:
				if (StateNumber::isvalid(word)) 
				{
					stateNumber = word;
				}
				break;
			case 4:
				if (CarSpecs::isvalid(word)) 
				{
					brandModel = word;
				}
				break;
			}
		}

		// if all the line words were succesfully initialized, new AutoDocs instance make sense
		if (!name.empty() && !surname.empty() && !stateNumber.empty() && !brandModel.empty()) 
		{
			if (name.length() + surname.length() <= ::FULLNAME_MAX_LENGTH) 
			{
				docsContainer.emplace_back(AutoDocs{ FullName{ name, surname }, StateNumber{ stateNumber }, CarSpecs{ brandModel }});
			}
		}
	}
}

// command style : N, fullname_pattern1, pattern_count1, brandmodel_pattern2, pattern_count2 ...
int main(int argc, char* argv[]) 
{	
	ArgsParser args_parser(argc, argv);
	std::cout << args_parser << '\n';
	
	assert(args_parser.getN() >= 10 && args_parser.getN() <= 1000000 && "INVALID N'S RANGE");
	
	std::vector<AutoDocs> docsContainer{};
	try
	{
		docsContainer.reserve(args_parser.getN());
	}
	catch (std::length_error const& error)
	{
		std::cerr << "MEMORY RESERVATION FAILED: "<< error.what() << '\n';
		return EXIT_FAILURE;
	}

	std::ifstream inputStream{ "ifiles/data.txt" };
	assert(inputStream.is_open() && "INPUTSTREAM ASSOCIATED FILE IS NOT FOUND OR CANNOT BE OPENED");

	// read "N" lines from filestream and fill docsContainer with their content
	readFromTo(inputStream, docsContainer, args_parser.getN());
	
	rabinKarp(args_parser,  docsContainer);
	boyerMoore(args_parser, docsContainer);

	inputStream.close();
	ge_ofstreamBM.close();
	ge_ofstreamRK.close();

	return EXIT_SUCCESS;
}	


// искать первое найденое вхождение
// 1 - линейный с барьером
// 2 - бинарный (рекрсивная реализация)