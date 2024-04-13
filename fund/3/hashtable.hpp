#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <initializer_list>
#include <string>
#include <utility>
#include <limits>
#include <string_view>

class hashtable 
{
public:
    class forward_iterator;

    using key_type    = std::string;
    using mapped_type = int; 
    using value_type  = std::pair<std::string, int>;
    using size_type   = std::size_t; 
    using reference   = value_type&;
    using pointer     = value_type*;
    using iterator    = forward_iterator;

public:
    class forward_iterator
    {
    public:
        forward_iterator(pointer ptr) :
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
            forward_iterator temp{ *this };
            ++(*this);
            return temp;
        }
        
        bool operator==(forward_iterator const& other) const
        {
            return m_ptr == other.m_ptr;
        } 
        bool operator!=(forward_iterator const& other) const 
        {
            return !(m_ptr == other.m_ptr); 
        }
    private:
        pointer m_ptr;
    };

private:
    size_type hash(std::string_view key) const
    {
        size_type result{};

        std::size_t len{ key.length() };
        for (std::size_t i{}; i < len; ++i)
        {
            result = (result + (key[i] % 10) + (key[i] / 10)) % m_capacity;
        }

        return result;
   };

public:
    // constructors and destructor
    hashtable(size_type N) :
        m_base{ new value_type[N]{} }, m_size{}, m_capacity{ N } 
    {}
    hashtable(std::initializer_list<std::pair<std::string, int>> ls) :
        m_base{ new value_type[ls.size()] }, m_size{ ls.size() }, m_capacity{ ls.size() } 
    {
        for (auto& p : ls)
        {
            *(m_base + hash(p.first)) = value_type{ p.first, p.second }; // use insert method instead 
        }
    }
    ~hashtable() 
    {
        delete[] m_base;
    }
    
    //iterators
    iterator begin() noexcept 
    {
        return iterator{ m_base };
    } 
    iterator end() noexcept
    {
        return iterator{ m_base + m_capacity };
    }

    //capacity
    size_type empty() const noexcept
    {
        return !m_size;
    }
    size_type size() const noexcept
    {
        return m_size;
    }
    size_type max_size() const noexcept
    {
        return  std::numeric_limits<std::size_t>::max() / sizeof(value_type);
    }
    
    // modifiers
   // std::pair<forward_iterator, bool> insert(value_type const& value) 
  //  {
//
   // }    

    // lookup
    mapped_type& operator[](key_type const& key) 
    {
        size_type i{ hash(key) };
        pointer   bucket{ m_base + i };
        
        if (bucket->first == key)
        {
            return bucket->second;
        }
        
        *(m_base + i) = value_type{ key, mapped_type{} }; // use insert method instead
        m_size++;
        return (*(m_base + i)).second;
    }
    
private:
    pointer      m_base;
    size_type    m_size;
    size_type    m_capacity;   
};

#endif // HASHTABLE_HPP
