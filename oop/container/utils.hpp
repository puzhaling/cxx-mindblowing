#ifndef UTILS_HPP
#define UTILS_HPP

bool is_prime(int n) 
{	
	if (n < 0 || n == 0 || n == 1)
	{
		return false;
	}

	for (unsigned int i{ 2 }; i <= n/2; ++i)
	{
		if (n % i == 0) 
		{
			return false;
		}
	}
	return true;
}

#endif // UTILS_HPP