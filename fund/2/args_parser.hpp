#ifndef ARGS_PARSER_HPP
#define ARGS_PARSER_HPP

#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>
#include <stdexcept>
#include <iostream>

// command style : N, pattern1, pattern_count1, pattern2, pattern_count2 ...
class ArgsParser
{
public:
	ArgsParser(int argc, char* argv[]);
	
	std::size_t    getN()               const;
	std::string    get_pattern1()       const;
	std::string    get_pattern2()       const;
	std::uint16_t  get_pattern_count1() const;
	std::uint16_t  get_pattern_count2() const;

private:
	std::vector<std::string> tokens;
};

std::ostream& operator<<(std::ostream& out, ArgsParser const& args);

#endif // ARGS_PARSER_HPP
