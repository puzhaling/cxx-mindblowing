
#include "args_parser.hpp"


ArgsParser::ArgsParser(int argc, char* argv[])
{
	for (int idx{ 1 }; idx < argc; ++idx)
	{
		this->tokens.push_back(std::string(argv[idx]));
	}
}

std::size_t ArgsParser::getN() const 
{	
	if (this->tokens.empty())
	{
		return 0;
	}
	
	try
	{
		std::stoll(*std::begin(this->tokens));
	}
	catch (std::invalid_argument&) 
	{
		return 0;
	}
	
	return static_cast<std::size_t>(std::stoll(*std::begin(this->tokens)));
}

std::string ArgsParser::get_pattern1() const
{	
	if (this->tokens.empty() || this->tokens.size() <= 1)
	{
		return "";
	}

	auto it{ std::begin(this->tokens) };
	it = std::next(it);

	return *it;
}

std::string ArgsParser::get_pattern2() const
{	
	if (this->tokens.empty() || this->tokens.size() <= 2)
	{
		return "";
	}

	auto it{ std::begin(this->tokens) };
	std::advance(it, 3);

	return *it;
}

std::uint16_t ArgsParser::get_pattern_count1() const
{
	if (this->tokens.size() <= 2)
	{
		return 1; // default value
	}
	
	auto it{ std::begin(this->tokens) };
	std::advance(it, 2);

	if (std::all_of(std::begin(*it), std::end(*it), [](char ch) -> bool {
		if (std::isalpha(ch))
		{
			return false;
		}
		return true;
	}) && (*it)[0] != '0')
	{
		return static_cast<std::uint16_t>(std::stoll(*it));
	}
	return 1; // default value
}

std::uint16_t ArgsParser::get_pattern_count2() const
{
	if (this->tokens.size() <= 4)
	{
		return 1; // default value
	}
	
	auto it{ std::begin(this->tokens) };
	std::advance(it, 4);

	if (std::all_of(std::begin(*it), std::end(*it), [](char ch) -> bool {
		if (std::isalpha(ch))
		{
			return false;
		}
		return true;
	}) && (*it)[0] != '0')
	{
		return static_cast<std::uint16_t>(std::stoll(*it));
	}
	return 1; // default value
}

std::ostream& operator<<(std::ostream& out, ArgsParser const& args)
{
	out << "fullname pattern: " << args.get_pattern1() << ": count = " << args.get_pattern_count1() << '\n'; 
	out << "brandmodel pattern: " << args.get_pattern2() << ": count = " << args.get_pattern_count2() << '\n'; 
	return out;
}