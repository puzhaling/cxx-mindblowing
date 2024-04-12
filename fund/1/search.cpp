
#include "search.hpp"
#include "autodocs.hpp"
#include "args_parser.hpp"

std::ofstream ge_ofstreamBM{ "ofiles/boyer_moore.txt" };
std::ofstream ge_ofstreamRK{ "ofiles/rabin_karp.txt" };


namespace sorts
{
	// Booyer-Moore algorithm for pattern searching
	std::array<std::size_t, ALPHABET_SIZE> badchar1{};
	std::array<std::size_t, ALPHABET_SIZE> badchar2{};

	namespace BoyerMoore
	{
		void badCharInit(std::string_view s1, std::string_view s2) 
		{  
			for (std::size_t i{}; i < ALPHABET_SIZE; ++i)
			{
				badchar1[i] = -1; 
				badchar2[i] = -1; 
			}

			std::size_t N1{ s1.length() };
			std::size_t N2{ s2.length() };

			for (std::size_t i{}; i < N1; ++i)
			{
				badchar1[static_cast<std::size_t>(s1[i])] = i;
			}

			for (std::size_t i{}; i < N2; ++i)
			{
				badchar2[static_cast<std::size_t>(s2[i])] = i;
			}
		}
	}

	namespace RabinKarp
	{
		int evalPatternHash(std::string_view s)
		{
			std::size_t N{ s.length() };
			int hsh{};

			for (std::size_t i{}; i < N; ++i) 
			{
				hsh += s[i];
			}
			return hsh;
		}
	}

	decltype(ge_patternCount1) boyerMoore(const std::string& pattern, std::string_view txt, std::uint16_t badchar_choice) 
	{   	
		decltype(ge_patternCount1) counter{};
		
		std::size_t m{ pattern.size() }; 
		std::size_t n{ txt.size() };

		std::size_t s{}; 

		if (badchar_choice == 1)
		{
			while (s <= (n - m)) 
			{ 
				int j = m - 1; 

				while (j >= 0 && pattern[j] == txt[s + j])
				{
					--j; 
				}

				if (j < 0) 
				{ 
					counter++;
					s += (s + m < n) ? m - badchar1[txt[s + m]] : 1; 
				} 
				else
				{
					s += std::max(1, j - static_cast<int>(badchar1[txt[s + j]])); 
				}
			}
		}
		else if (badchar_choice == 2)
		{
			while (s <= (n - m)) 
			{ 
				int j = m - 1; 

				while (j >= 0 && pattern[j] == txt[s + j])
				{
					--j; 
				}

				if (j < 0) 
				{ 
					counter++;
					s += (s + m < n) ? m - badchar2[txt[s + m]] : 1; 
				} 
				else
				{
					s += std::max(1, j - static_cast<int>(badchar2[txt[s + j]])); 
				}
			}
		}

		return counter;
	}

	// вынести подсчет хэша шаблона
	// для бойера мура вынести заполнение таблицы сдвигов
	// добавить во входные данные отдельный паттерн для второго поля и отдельное число появлений


	// Rabin-Karp algorithm for pattern searching
	decltype(ge_patternCount1) rabinKarp(const std::string& pattern, int patternHsh, const std::string& txt)
	{	
		decltype(ge_patternCount1) counter{};
		
		std::size_t M{ pattern.length() };
		std::size_t N{ txt.length() };

		if (N < M)
		{
			return counter;
		}

		int slideHsh{};

		for (std::size_t i{}; i < M; ++i)
		{
        	slideHsh += txt[i];
		}

		for (std::size_t i{}; i <= N - M; ++i)
		{
			if (slideHsh == patternHsh)
			{	
				bool match{ true };
				for (std::size_t j{}; j < M; ++j)
				{
					if (txt[i + j] != pattern[j])
					{
						match = false;
						break;
					}
				}

				if (match)
				{   
					counter++;
				}
			}

			if (i < N - M)
			{
				slideHsh = slideHsh - txt[i] + txt[i + M];
			}
		}

		return counter;
	}
}

void boyerMoore(const ArgsParser& args, const std::vector<AutoDocs>& docsContainer)
{	
	using namespace std::chrono;
	
	if (ge_ofstreamBM.is_open())
	{					
		sorts::BoyerMoore::badCharInit(args.get_pattern1(), args.get_pattern2());

		const auto start{ high_resolution_clock::now() };
		
		std::string pattern1{ args.get_pattern1() };
		std::string pattern2{ args.get_pattern2() };

		for (const auto& doc : docsContainer)
		{		
			if (sorts::boyerMoore(pattern1, doc.getFullName().getName()+" "+doc.getFullName().getSurname(), 1) == args.get_pattern_count1()) 
			{
				if (sorts::boyerMoore(pattern2, doc.getCarSpecs().getBrand()+" "+doc.getCarSpecs().getModel(), 2) == args.get_pattern_count2())
				{
					ge_ofstreamBM << doc << '\n';
				}
			}
		}
		
		const auto end{ high_resolution_clock::now() };

		const auto duration{ duration_cast<microseconds>(end - start) };
		ge_ofstreamBM << "\nduration " << duration.count() << "μs (1sec = 1000000μs)";
	}
}

void rabinKarp(const ArgsParser& args, const std::vector<AutoDocs>& docsContainer)
{
	using namespace std::chrono;
	
	if (ge_ofstreamRK.is_open())
	{		
		const auto start{ high_resolution_clock::now() };

		std::string pattern1{ args.get_pattern1() };
		std::string pattern2{ args.get_pattern2() };

		int patternHash1{ sorts::RabinKarp::evalPatternHash(args.get_pattern1()) };
		int patternHash2{ sorts::RabinKarp::evalPatternHash(args.get_pattern2()) }; 

		for (const auto& doc : docsContainer)
		{			
			if (sorts::rabinKarp(pattern1, patternHash1, doc.getFullName().getName()+" "+doc.getFullName().getSurname()) == args.get_pattern_count1()) 
			{
				if (sorts::rabinKarp(pattern2, patternHash2, doc.getCarSpecs().getBrand()+" "+doc.getCarSpecs().getModel()) == args.get_pattern_count2())
				{
					ge_ofstreamRK << doc << '\n';
				}
			}
		}
		
		const auto end{ high_resolution_clock::now() };

		const auto duration{ duration_cast<microseconds>(end - start) };
		ge_ofstreamRK << "\nduration " << duration.count() << "μs (1sec = 1000000μs)";
	}
}
