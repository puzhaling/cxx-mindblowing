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
    using key_type    = std::string;
    using mapped_type = int; 
    using value_type  = std::pair<std::string, int>;
    using size_type   = std::size_t; 
    using reference   = value_type&;

private:
    size_type hash(std::string_view key) const
    {
        size_type result{};

        std::size_t len{ key.length() };
        for (std::size_t i{}; i < len; ++i)
        {
            result = (result + (key[i] % 10) + (key[i] / 10)) % m_size;
        }
        result -= 32; // space ascii code

        return result;
   };

public:
    hashtable(size_type N) :
        m_base{ new value_type[N]{} }, m_size{ N }, m_maxsize{ N }
    {}
    hashtable(std::initializer_list<std::pair<std::string, int>> ls) :
        m_base{ new value_type[ls.size()] }, m_size{ ls.size() }, m_maxsize{ ls.size() }
    {
        for (auto& p : ls)
        {
            m_base[hash(p.first)] = p.second; 
        }
    }
    ~hashtable() 
    {
        delete[] m_base;
    }

    size_type max_size() const 
    {
        return std::numeric_limits<std::size_t>::max() / sizeof(std::pair<std::string, int>);
    }
    
   reference operator[](key_type& key) 
   {
       size_type i{ hash(key) };
       reference bucket{ m_base[i] };

       if (bucket.first == key)
       {
           return bucket.second;
       }

       *m_base[i] = value_type{ Key, mapped_type{} };
       return m_base[i]->second;
   }
    
private:
    value_type*  m_base;
    size_type    m_size;
    size_type    m_maxsize;   
};

#endif // HASHTABLE_HPP
