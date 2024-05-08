#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <string>
#include <filesystem>
#include <memory>
#include <stdio.h>

#include "autodocs.hpp"
#include "hashtable.hpp"

namespace fs = std::filesystem;

constexpr auto FULLNAME_MAX_LENGTH{ 30 };
constexpr auto CAR_NUMBER_MAXIMUM_DIGITS_COUNT{ 3 };
constexpr auto INDENT_WIDTH{ 10 };

// number of lines to read
int n{ 6000 };

static void readFromTo
(std::ifstream& inputStream, hashtable& table) 
{
	std::string line{};

	while (!inputStream.eof() && n--) 
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
        
        // line correctness condition
		if (!name.empty() && !surname.empty() && !stateNumber.empty() && !brandModel.empty()) 
		{
			if (name.length() + surname.length() <= FULLNAME_MAX_LENGTH) 
			{
                AutoDocs doc{ std::move(AutoDocs{FullName{ name, surname }, StateNumber{ stateNumber }, CarSpecs{ brandModel }, request}) };
                std::string key{ std::move(name + " " + surname + " " + std::to_string(request)) };
                auto iter{ table.find(key) };
                if (iter == table.end())
                {   
                    table.emplace(std::move(std::pair<std::string, AutoDocs>{key, std::move(doc)}));
                } 
	        }
		}
    } 
}

// command style : filepath, key.
int main(int argc, char* argv[]) 
{	
	fs::path path{ argv[1] };
	std::string key{ argv[2] };

	if (!fs::exists(path))
    {
        std::cout << "NO SUCH FILE OF FILE CANNOT BE OPENED" << '\n';
        return -1;
	}

    hashtable table;

	std::ifstream inputStream{ path.c_str() };
	assert(inputStream.is_open() && "INPUTSTREAM ASSOCIATED FILE IS NOT FOUND OR CANNOT BE OPENED");
    
	// read "N" lines from filestream and fill docsContainer with their content
	readFromTo(inputStream, table);

	std::ofstream outputStream{ "out.txt" };
	assert(outputStream.is_open() && "OUTPUTSTREAM ASSOCIATED FILE IS NOT FOUND OR CANNOT BE OPENED"); 
	
	std::cout << "\n\n\nsize: " << table.size() << '\n';
    std::cout << "capacity: " << table.capacity() << '\n' << '\n';
    std::cout << table << '\n';
    
    // Joseph Davis T204PL ChevroletImpala 7852246  
    auto iter{ table.find(key) };
    if (iter != table.end()) 
    {
        std::cout << "erasion took place\n";
        table.erase(iter);
    }
    else 
    {
        std::cout << "no such a key\n";
    }
	std::cout << "size: " << table.size() << '\n';
    std::cout << "capacity: " << table.capacity() << '\n' << '\n';

    outputStream << table;
	inputStream.close();
	outputStream.close();
	
	return 0;
}
