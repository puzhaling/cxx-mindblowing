#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <iostream>
#include <cassert>
#include <string>
#include <array>
#include <vector>
#include <limits>
#include <algorithm>
#include <fstream>
#include <chrono>

#include "autodocs.hpp"
#include "args_parser.hpp"

constexpr unsigned int ALPHABET_SIZE{ 256 };

extern std::ofstream ge_ofstreamBM;
extern std::ofstream ge_ofstreamRK;
extern std::uint16_t ge_patternCount1;
extern std::uint16_t ge_patternCount2;

namespace sorts
{
	namespace BoyerMoore
	{
		void badCharInit(std::string_view s);
	}
	namespace RabinKarp
	{
		int evalPatternHash(std::string_view s);
	}

	decltype(ge_patternCount1) boyerMoore(const std::string& pattern, std::string_view txt, std::uint16_t badchar_choice);
	decltype(ge_patternCount1) rabinKarp(const std::string& pattern, int patternHsh, const std::string& txt);
}

void boyerMoore(const ArgsParser& args, const std::vector<AutoDocs>& docsContainer);
void rabinKarp(const ArgsParser& args, const std::vector<AutoDocs>& docsContainer);

#endif // SEARCH_HPP
