
#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <cstddef>
#include <initializer_list>
#include <cassert>
#include <stdexcept>
#include <concepts>

template<typename T, std::size_t N=10>
requires std::default_initializable<T>
class array {
public:
	using value_type    = T;
	using reference     = value_type&;
	using pointer       = value_type*;
	using size_type     = std::size_t;
    using const_pointer = const value_type*;

public:
    array() : m_base{ new T[N]{} }, m_sz{}, m_maxsz{ N } {}
	array(std::initializer_list<T> ls) :
        m_maxsz{ N }, m_base{ new T[N]{} }
	{	
        size_type lsz{ ls.size() };
        size_type i{};

        auto it{ ls.begin() };
        if (lsz >= m_maxsz)
        {
            for (;i < m_maxsz; std::advance(it, 1), ++i)
            {
                m_base[i] = *it;
            }
            m_sz = m_maxsz;
        }
        else 
        {
            for (;i < lsz; std::advance(it, 1), ++i)
            {
                m_base[i] = *it;
            }
            m_sz = lsz;
        }
	}
    ~array() 
    {
        delete[] m_base; 
    }

	void swap(T* f, T* s) 
	{ 
		T temp{ *f }; 
		*f = *s; 
		*s = temp; 
	}

	bool      empty()                 const { return m_sz; }
	size_type size()                  const { return m_sz; }
    size_type max_size()              const { return m_maxsz; }

	reference at(size_type pos) 
	{ 
        if (pos >= m_sz) 
        {
            throw std::out_of_range("pos is out of range");
        }
        return m_base[pos];
	}
	reference     back()                    { return m_base[m_sz - 1]; }
	reference     front()                   { return m_base[0];        }
	reference     operator[](size_type i)   { return m_base[i];        } 
    const_pointer data()                    { return m_base; } 

	void fill (value_type const& val)
	{
		for (size_type i{}; i < m_sz; ++i)
		{
			m_base[i] = val;
		}
	}


private:
	pointer    m_base;
    size_type  m_maxsz;
    size_type  m_sz;
};

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& out, array<T, N>& arr) 
{	
	typename array<T, N>::size_type sz{ arr.size() }; 
	for (std::size_t i{}; i < sz; ++i) 
	{ 
		out << arr[i] << ' '; 
	} 
	return out;
}

#endif // ARRAY_HPP

