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
#include <filesystem>
#include <cstdlib>

#include "autodocs.hpp"
#include "searches.hpp"

namespace fs = std::filesystem;

constexpr auto FULLNAME_MAX_LENGTH{ 30 };
constexpr auto CAR_NUMBER_MAXIMUM_DIGITS_COUNT{ 3 };
constexpr auto INDENT_WIDTH{ 10 };

// таски:
// искать первое найденое вхождение по номеру заявки
// 1 - линейный с барьером (+++)
// 2 - бинарный поиск (рекурсивная реализация) (---)

// передаем имя файла в виде абсолютного пути
// в линейном поиске считаем количество сравнений а не переходов => в результирующей строке номер строки = количеству сравнений
// в линейном поиске добавляем барьер на n+1 позицию, где n - размерность массива

static void readFromTo
(std::ifstream& inputStream, std::vector<AutoDocs>& docsContainer, std::size_t N) 
{
	std::string line{};
	while (N-- && !inputStream.eof()) 
	{
		std::getline(inputStream, line, '\n');
		std::istringstream lineBuffer{ line };

		if (line.empty() || countWords(line) != 5) 
		{
			continue;
		}

		std::string name{};
		std::string surname{};
		std::string stateNumber{};
		std::string brandModel{};
		std::size_t request{};

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
			case 5:
				request = static_cast<std::size_t>(std::stoll(word));
				break;
			default:
				break;
			}
		}

		// if all the line words were succesfully initialized, new AutoDocs instance make sense
		if (!name.empty() && !surname.empty() && !stateNumber.empty() && !brandModel.empty()) 
		{
			if (name.length() + surname.length() <= ::FULLNAME_MAX_LENGTH) 
			{
				docsContainer.push_back(AutoDocs{ FullName{ name, surname }, StateNumber{ stateNumber }, CarSpecs{ brandModel }, request});
			}
		}
	}
}

// command style : filepath, N, integer key.... 
int main(int argc, char* argv[]) 
{	
	std::size_t N{};
	std::size_t key{};
	fs::path    path{ argv[1] };

	try 
	{
		N = static_cast<std::size_t>(std::stoull(argv[2]));
	}
	catch (std::invalid_argument const& err)
	{
		std::cerr << "INVALID N'TH VALUE: " << err.what() << '\n';
		return EXIT_FAILURE;
	}
	assert(N >= 10 && N <= 1000000 && "INVALID N'S RANGE");
	
	try
	{
		key = static_cast<std::size_t>(std::stoull(argv[3]));
	}
	catch (std::invalid_argument const& err)
	{
		std::cerr << "INVALID KEY'S VALUE: " << err.what() << '\n';
		return EXIT_FAILURE;
	}

	if (!fs::exists(path))
    {
        std::cerr << "NO SUCH FILE OF FILE CANNOT BE OPENED" << '\n';
        return EXIT_FAILURE;
	}

	std::vector<AutoDocs> docsContainer{};
	try
	{
		docsContainer.reserve(N);
	}
	catch (std::length_error const& error)
	{
		std::cerr << "MEMORY RESERVATION FAILED: "<< error.what() << '\n';
		return EXIT_FAILURE;
	}

	std::ifstream inputStream{ path.c_str() };
	assert(inputStream.is_open() && "INPUTSTREAM ASSOCIATED FILE IS NOT FOUND OR CANNOT BE OPENED");

	// read "N" lines from filestream and fill docsContainer with their content
	readFromTo(inputStream, docsContainer, N);
	
	std::ofstream outputStream{ "ofiles/out.txt" };
	assert(outputStream.is_open() && "OUTPUTSTREAM ASSOCIATED FILE IS NOT FOUND OR CANNOT BE OPENED"); 
	
/*********************************************************************************************************/
	// std::pair<line_number, steps> search_p1{ barrierSearch(docsContainer, key) };
	// outputStream << "barrier search:: " << search_p1.first << ' ' << search_p1.second << '\n';


	// sorted by request field
	std::sort(std::begin(docsContainer), std::end(docsContainer), [](auto& a, auto& b) { return a < b; });

	std::pair<line_number, steps> search_p2{ binarySearch(docsContainer, key) };
	outputStream << "binary search:: " << search_p2.first << ' ' << search_p2.second << '\n';
/*********************************************************************************************************/

	std::cout << "\n\n\nlen: " << docsContainer.size() << "\n\n\n";

	for (std::size_t i{}; i < docsContainer.size(); ++i)
	{
		std::cout << " " << i;
		std::cout << "     ";
	}
	std::cout << '\n';

	for (auto& doc : docsContainer)
	{
		std::cout << doc.getRequest() << ' ';
	}
	std::cout << "\n\n\n";

	inputStream.close();
	outputStream.close();
	
	return EXIT_SUCCESS;
}	

