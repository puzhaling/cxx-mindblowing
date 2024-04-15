#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <string>
#include <filesystem>
#include <stdio.h>

#include "autodocs.hpp"
#include "hashtable.hpp"

namespace fs = std::filesystem;

constexpr auto FULLNAME_MAX_LENGTH{ 30 };
constexpr auto CAR_NUMBER_MAXIMUM_DIGITS_COUNT{ 3 };
constexpr auto INDENT_WIDTH{ 10 };

//#define __DEBUG_MODE
#define __RELEASE_MODE

#ifdef __DEBUG_MODE
    #ifdef __HASHTABLE_DEBUG_MODE
int main() 
{
    hashtable a{ 2 };
    
    printf("is empty? %s\n", a.empty() ? "true" : "false");
    a.insert({"Sasha", 1});
    printf("size: %lu  capacity: %lu\n", a.size(), a.capacity());
    std::cout << a << '\n'; 

    std::cout << "----------------------------------\n";
    auto it = a.insert({"Masha", 2});
    std::cout << (it.second ? "true" : "false") << '\n';
    printf("size: %lu  capacity: %lu\n", a.size(), a.capacity());
    std::cout << a << '\n'; 
    std::cout << "----------------------------------\n";
   
    it = a.insert({"Masha", 9999});
    std::cout << (it.second ? "true" : "false") << '\n';
    printf("size: %lu  capacity: %lu\n", a.size(), a.capacity());
    std::cout << a << '\n'; 
    std::cout << "----------------------------------\n";

    a.insert({"Grisha", 3});
    printf("size: %lu  capacity: %lu\n", a.size(), a.capacity());
    std::cout << a << '\n'; 

    a.insert({"Danila", 4});
    printf("size: %lu  capacity: %lu\n", a.size(), a.capacity());
    std::cout << a << '\n'; 

    a.insert({"Katya", 5});
    printf("size: %lu  capacity: %lu\n", a.size(), a.capacity());
    std::cout << a << '\n'; 

    a.insert({"Nikita", 6});
    printf("size: %lu  capacity: %lu\n", a.size(), a.capacity());
    std::cout << a << '\n'; 

    a["Oleg"] = 7;
    printf("size: %lu  capacity: %lu\n", a.size(), a.capacity());
    std::cout << a << '\n'; 

    a.insert({"Egor", 8});
    printf("size: %lu  capacity: %lu\n", a.size(), a.capacity());
    std::cout << a << '\n'; 
    
    a.insert({"Mark", 9});
    printf("size: %lu  capacity: %lu\n", a.size(), a.capacity());
    std::cout << a << '\n'; 

    a.insert({"Ian", 10});
    printf("size: %lu  capacity: %lu\n", a.size(), a.capacity());
    std::cout << a << '\n'; 
    
    printf("size: %lu  capacity: %lu\n", a.size(), a.capacity());
    std::cout << a << '\n';
   

    auto iter{ a.find("Nikita") };
    if (iter != a.end())
    {
        std::cout << "find: {" << iter->first << ", " << iter->second << "}\n";  
    }
    else
    {
        std::cout << "not found, end() iterator is returned\n";
    }
}
    #endif
#endif

#ifdef __RELEASE_MODE
static void readFromTo
(std::ifstream& inputStream, hashtable& table) 
{
	std::string line{};

	while (!inputStream.eof()) 
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
                std::string key{ name + " " + surname };
                auto iter{ table.find(key) };

                if (iter == table.end())
                {
                    table.insert({ key, request });
                } 
	        }
		}
	}
}

// command style : filepath, key, hashmap capacity.
int main(int argc, char* argv[]) 
{	
	fs::path path{ argv[1] };
	std::string key{ argv[2] };
    std::size_t capacity{};

    try
    {
        capacity = static_cast<std::size_t>(std::stoull(argv[3]));
    }
    catch (std::invalid_argument const& err)
    {
        std::cerr << "INVALID SIZE VALUE: " << err.what() << '\n';
    }
	
	if (!fs::exists(path))
    {
        std::cout << "NO SUCH FILE OF FILE CANNOT BE OPENED" << '\n';
        return -1;
	}

    hashtable table{};

	try
	{
		table.reserve(capacity);
	}
	catch (std::length_error const& error)
	{
		std::cerr << "MEMORY RESERVATION FAILED: "<< error.what() << '\n';
		return -1;
	}
	std::ifstream inputStream{ path.c_str() };
	assert(inputStream.is_open() && "INPUTSTREAM ASSOCIATED FILE IS NOT FOUND OR CANNOT BE OPENED");

	// read "N" lines from filestream and fill docsContainer with their content
	readFromTo(inputStream, table);
	
	std::ofstream outputStream{ "out.txt" };
	assert(outputStream.is_open() && "OUTPUTSTREAM ASSOCIATED FILE IS NOT FOUND OR CANNOT BE OPENED"); 
	
	std::cout << "\n\n\nsize: " << table.size() << '\n';
    std::cout << "capacity: " << table.capacity() << "\n\n";
    std::cout << table << '\n';
    
	inputStream.close();
	outputStream.close();
	
	return 0;
}
#endif // __RELEASE_MODE
