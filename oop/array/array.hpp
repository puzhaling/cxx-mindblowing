    
#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <cstddef>
#include <initializer_list>
#include <cassert>
#include <stdexcept>
#include <concepts>
#include <algorithm>
#include <limits>

template<typename T, std::size_t N=0>
requires std::default_initializable<T>
class array {
public:
    class random_access_iterator;
    class const_random_access_iterator;

public:
	using value_type      = T;
	using size_type       = std::size_t;
	using difference_type = std::ptrdiff_t;
	using reference       = value_type&;
	using const_reference = const reference;
	using pointer         = value_type*;
	using const_pointer   = const pointer;
	using iterator        = random_access_iterator;
	using const_iterator  = const iterator;

public:
    class const_random_access_iterator
    {
    public:
        const_random_access_iterator(const_pointer ptr) :
            m_ptr{ ptr } 
        {}

        const_reference operator*() const { return *m_ptr; }
        const_pointer operator->() const  { return m_ptr; }
        const_iterator& operator++() 
        {
            ++m_ptr;
            return *this;
        }
        const_iterator operator++(int)
        {
            const_iterator temp{ *this };
            ++(*this);
            return temp;
        }
        const_iterator& operator+=(difference_type n)
        {
        	difference_type m{ n };

        	if (m >= 0) while (m--) ++m_ptr;
        	else while (m++) --m_ptr;
        	return *this;
        }
        friend const_iterator operator+(difference_type lhs, const_iterator rhs)
        {
        	rhs += lhs;
        	return rhs;
        }
        friend const_iterator operator+(const_iterator lhs, difference_type rhs)
        {
        	return operator+(rhs, lhs);
        }
        const_iterator operator--()
        {
            --m_ptr;
            return *this;
        }
        const_iterator operator--(int)
        {
            const_iterator temp{ *this };
            --(*this);
            return temp;
        }
        const_iterator& operator-=(difference_type n)
        {
        	return operator+=(-n);
        }
        friend const_iterator operator-(difference_type lhs, const_iterator rhs)
        {
        	rhs -= lhs;
        	return rhs;
        }
        friend const_iterator operator-(const_iterator lhs, difference_type rhs)
        {
        	return operator-(rhs, lhs);
        }
        friend difference_type operator-(const_iterator lhs, const_iterator rhs)
        {
        	difference_type n{};

        	if (lhs > rhs) while (rhs++ != lhs) n++;
        	else while (lhs++ != rhs) n++;
        	return n;
        }
        // must be convertible to reference
        const_iterator operator[](difference_type i) const
        {
        	return { m_ptr + i };
        }

        friend bool operator<(const_reference lhs, const_iterator rhs)
        {
            return rhs.m_ptr - lhs.m_ptr > 0;
        }
        friend bool operator<=(const_reference lhs, const_iterator rhs)
        {
            return !(lhs > rhs);
        }
        friend bool operator>(const_iterator lhs, const_iterator rhs)
        {
            return lhs.m_ptr - rhs.m_ptr < 0;
        }
        friend bool operator>=(const_reference lhs, const_iterator rhs)
        {
            return !(lhs < rhs);
        }
        friend bool operator==(const_iterator lhs, const_iterator rhs)
        {
            return lhs.m_ptr == rhs.m_ptr;
        } 
        friend bool operator!=(const_iterator lhs, const_iterator rhs)
        {
            return !(lhs == rhs); 
        }

    private:
        const_pointer m_ptr;
    };

    class random_access_iterator
    {
    public:
        random_access_iterator(pointer ptr) :
            m_ptr{ ptr } 
        {}

        reference operator*()
        {
            return *m_ptr;
        }
        pointer operator->()
        {
            return m_ptr;
        }
        iterator& operator++() 
        {
            ++m_ptr;
            return *this;
        }
        iterator operator++(int)
        {
            const_iterator temp{ *this };
            ++(*this);
            return temp;
        }
        iterator& operator+=(difference_type n)
        {
        	difference_type m{ n };

        	if (m >= 0) while (m--) ++m_ptr;
        	else while (m++) --m_ptr;
        	return *this;
        }
        friend iterator operator+(difference_type lhs, iterator rhs)
        {
        	rhs += lhs;
        	return rhs;
        }
        friend const_iterator operator+(iterator lhs, difference_type rhs)
        {
        	return operator+(rhs, lhs);
        }
        iterator operator--()
        {
            --m_ptr;
            return *this;
        }
        iterator operator--(int)
        {
            const_iterator temp{ *this };
            --(*this);
            return temp;
        }
        iterator& operator-=(difference_type n)
        {
        	return operator+=(-n);
        }
        friend iterator operator-(difference_type lhs, iterator rhs)
        {
        	rhs -= lhs;
        	return rhs;
        }
        friend iterator operator-(iterator lhs, difference_type rhs)
        {
        	return operator-(rhs, lhs);
        }
        friend difference_type operator-(iterator lhs, iterator rhs)
        {
        	difference_type n{};

        	if (lhs > rhs) while (rhs++ != lhs) n++;
        	else while (lhs++ != rhs) n--;
        	return n;
        }
        // must be convertible to reference
        iterator operator[](difference_type i)
        {
        	return { m_ptr + i };
        }

        friend bool operator<(iterator lhs, iterator rhs)
        {
            return lhs.m_ptr - rhs.m_ptr < 0;
        }
        friend bool operator<=(iterator lhs, iterator rhs)
        {
            return !(lhs > rhs);
        }
        friend bool operator>(iterator lhs, iterator rhs)
        {
            return lhs.m_ptr - rhs.m_ptr > 0;
        }
        friend bool operator>=(iterator lhs, iterator rhs)
        {
            return !(lhs < rhs);
        }
        friend bool operator==(iterator lhs, iterator rhs)
        {
            return lhs.m_ptr == rhs.m_ptr;
        } 
        friend bool operator!=(iterator lhs, iterator rhs)
        {
            return !(lhs == rhs); 
        }

    private:
        pointer m_ptr;
    };

public:
    // constructors and destructors
    array(std::initializer_list<T> ls) :
        m_base{}
    {
        size_type lsize{ ls.size() };
        if (lsize > this->size())
        {
            throw std::length_error("too many initializers for ‘std::array’");
        }

        auto from{ ls.begin() };
        auto to{ this->begin() };

        while (from != ls.end())
        {
            *(to++) = *(from++);
        }
    }

    array& operator=(array<T, N> const& other)
    {
    	for (size_type i{}; i < N; ++i)
    	{
    		m_base[i] = other[i];
    	}
    	return *this;
    }

    template <size_type M>
    friend bool operator==(array<T, N> const& a, array<T, M> const& b)
    {
    	return a.size() == b.size() &&
    	std::equal(a.begin(), a.end(), b.begin());
    }
    friend bool operator!=(array<T, N> const& a, array<T, N> const& b)
    {
    	return !(a == b);
    }

    // element access
    reference at(size_type pos) 
	{ 
        if (pos >= N) 
        {
            throw std::out_of_range("pos is out of range");
        }
        return m_base[pos];
	}
    reference      back()                  { return m_base[N - 1]; }
	reference      front()                 { return m_base[0];     }
	reference      operator[](size_type i) { return m_base[i];     } 
    const_pointer  data()                  { return m_base; 	   }

    // iterators
    iterator 	   begin() 	      { return const_iterator{ m_base     }; }
    iterator 	   end()   	      { return const_iterator{ m_base + N }; }
    const_iterator begin()  const { return const_iterator{ const_cast<T*>(m_base)     }; }
    const_iterator end()    const { return const_iterator{ const_cast<T*>(m_base + N) }; }
    const_iterator cbegin() const { return const_iterator{ const_cast<T*>(m_base)     }; }
    const_iterator cend()   const { return const_iterator{ const_cast<T*>(m_base + N) }; }    

	// capacity
	constexpr bool      empty()    const { return !N; }
	constexpr size_type size()     const { return N;  }
    constexpr size_type max_size() const { return N;  } 

    // operations
	void fill(const_reference val)
	{
		for (size_type i{}; i < N; ++i)
		{	
			m_base[i] = val;
		}
	}
	void swap(array<T, N> const& other)
	{
		for (size_type i{}; i < N; ++i)
		{	
			value_type temp{ m_base[i] };
			m_base[i] = other[i];
			other[i] = temp;
		}
	}
	friend void swap(array<T, N> const& a, array<T, N> const& b)
	{
		a.swap(b);
	}

private:
	T m_base[N];
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

