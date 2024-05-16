#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <cmath>
#include <limits>

#include "autodocs.hpp"

class HashTable {
public:
    using size_type = std::size_t;

public:
    HashTable() : 
        m_capacity(8), 
        m_size(0),
        m_threshold_upper(0.8f), 
        m_threshold_lower(0.2f) 
    {
        m_buckets = new std::pair<std::string, AutoDocs>[m_capacity]();
        m_status = new bool[m_capacity]();
        m_lines = new int[m_capacity]();
        m_primary_hash_values = new int[m_capacity]();
    }

    HashTable(size_type N) : 
        m_capacity(N), 
        m_size(0), 
        m_threshold_upper(0.8f), 
        m_threshold_lower(0.2f) 
    {
        m_buckets = new std::pair<std::string, AutoDocs>[m_capacity]();
        m_status = new bool[m_capacity]();
        m_lines = new int[m_capacity]();
        m_primary_hash_values = new int[m_capacity]();
    }

    ~HashTable() {
        delete[] m_buckets;
        delete[] m_status;
        delete[] m_lines;
        delete[] m_primary_hash_values;
    }

    void insert(const std::string& key, const AutoDocs& value, int line) {
        if (find(key).first != -1) {
            std::cout << "duplicate key. insertion is cancelled\n";
            return;
        }
        if (load_factor() >= m_threshold_upper)
            expand();

        size_type index = primary_hash(key, m_capacity);
        size_type temp = index;
         
        if (m_status[index]) {
            index = secondary_hash(m_buckets, index, m_capacity);
            if (index == -1) {
                expand(m_capacity * 1.5);
                insert(key, value, line);
                return;
            }
        }

        m_buckets[index] = std::make_pair(key, value);
        m_status[index] = true;
        // primary hash value must be connected to final insertion position of a new key
        m_primary_hash_values[index] = temp;
        m_lines[index] = line;
        m_size++;
    }
    
    size_type previous_index(size_type index) {
        switch (index) {
        case 0: return this->capacity() - 2; break;
        case 1: return this->capacity() - 1; break;
        default: return index - 2; break;
        }
    } 

    void erase(const std::string& key, const AutoDocs& value) {
        size_type index = find(key).first;
        if (index != -1 && m_buckets[index].second == value) {
            m_buckets[index].first = "";
            m_status[index] = false;
            m_lines[index] = 0;
            m_primary_hash_values[index] = 0;
            m_size--;

             
            int target_hash = primary_hash(key, m_capacity);
            index = (index + 2) % m_capacity;
            while (primary_hash(m_buckets[index].first, m_capacity) == target_hash) {
                std::swap(m_buckets[previous_index(index)], m_buckets[index]);
                std::swap(m_lines[previous_index(index)], m_lines[index]);
                std::swap(m_status[previous_index(index)], m_status[index]);
                std::swap(m_primary_hash_values[previous_index(index)], m_primary_hash_values[index]);
                index = (index + 2) % m_capacity;
            } 


            if (load_factor() <= m_threshold_lower)
                shrink();
        }
    }
    
    //        index,     steps to find 
    std::pair<size_type, unsigned> find(const std::string& key) const {
        size_type index = primary_hash(key, m_capacity);
        int start = index;
        if (m_buckets[index].first == "")
            return std::make_pair(-1, 1);
        else if (m_buckets[index].first == key)
            return std::make_pair(index, 1);
      
        index = secondary_hash(m_buckets, index, m_capacity, key);
        int finish = index;

        if (index == -1)
            return std::make_pair(-1, m_capacity);
        else
            return std::make_pair(index, steps(start, finish));
    }
    
    size_type max_size() const {
        return std::numeric_limits<size_type>::max() / sizeof(AutoDocs);
    }

    size_type size() const {
        return m_size;
    }

    size_type capacity() const {
        return m_capacity;
    }
    
    int operator[] (size_type index) const {
        return m_lines[index];
    }

    friend std::ostream& operator<<(std::ostream& out, HashTable const& table) {
        for (size_type i = 0; i < table.m_capacity; ++i) {
            if (table.m_status[i]) {
                size_type len = table.m_buckets[i].first.length();
                out << table.m_buckets[i].first;

                while (len++ != 30) 
                    out << ' ';

                out << '\t';
                out << '{' << table.m_buckets[i].second << '}' << '\t';
                out << "\thash value: {" << table.m_primary_hash_values[i] << "}";
                out << " index: " << i << '\n';
               // out << "line number: " << table.m_lines[i] << '\n';
            }
        }
       //out << '[';
       //for (size_type i = 0; i < table.m_capacity; ++i)
       //     out << (table.m_status[i] ? 1 : 0);
       //out << ']' << '\n';
       return out;
    } 

private:
    float load_factor() const {
        return static_cast<float>(m_size) / m_capacity;
    }

    size_type primary_hash(const std::string& key, size_type capacity) const {
    	size_type result = 0;
        size_type fullname_sum = 0;
        size_type request_sum = 0;

        size_type i;
    	size_type len = key.length();
        for (i = 0; i < len; ++i) {
            if (std::isspace(key[i])) 
                continue;
            if (std::isdigit(key[i])) 
                break;
            fullname_sum += key[i];
        }

        for (;i < len; ++i) 
            request_sum = request_sum * 10 + (key[i] - '0');
        
        size_type temp = request_sum + fullname_sum;
        
        int last, prelast; 
        while (temp > 0) {
            last = temp % 10;
            prelast = (temp % 100) / 10;
            result = result + (last + prelast);
            result = result % m_capacity;
            temp /= 100;
        }
        return result;
    }
    size_type secondary_hash(std::pair<std::string, AutoDocs>* const arr, 
                             size_type i, 
                             size_type capacity,
                             std::string stopper = "") const 
    {
        size_type steps = 0;
        while (arr[i].first != stopper) {
            if (steps > capacity)
                return -1;
            i = (i + 2) % capacity;
            steps++;
        }
        return i;
    }

    void expand() {
        size_type new_capacity = m_capacity * 2;
        if (new_capacity > this->max_size()) 
            throw std::bad_array_new_length();
        rehash(new_capacity);
    }

    void expand(size_type capacity) {
        if (capacity > this->max_size()) 
            throw std::bad_array_new_length();
        rehash(capacity);
    }

    void shrink() {
        size_type new_capacity = std::max(static_cast<size_type>(8), m_capacity / 2);
        rehash(new_capacity);
    }

    void rehash(size_type new_capacity) {
        std::pair<std::string, AutoDocs>* new_buckets = new std::pair<std::string, AutoDocs>[new_capacity]();
        bool* new_status = new bool[new_capacity]();
        int* new_primary_hash_values = new int[new_capacity]();
        int* new_lines = new int[new_capacity]();

        for (size_type i = 0; i < m_capacity; ++i) {
            if (m_status[i]) {
                size_type index = primary_hash(m_buckets[i].first, new_capacity);
                size_type temp = index;
                if (new_buckets[index].first != "") {
                    index = secondary_hash(new_buckets, index, new_capacity);
                    if (index == -1) {
                        delete[] new_buckets;
                        delete[] new_status;
                        delete[] new_primary_hash_values;
                        delete[] new_lines;

                        /* if after a try to rehash we have no places to insert, we try again, but with the different size.
                           a bit larger new cap if rehash is called from expand();
                           a bit smaller one if rehash is called from shrink(). */
                        if (new_capacity < m_capacity) 
                            rehash(new_capacity + new_capacity / 2);
                        else 
                            rehash(new_capacity * 1.25);

                        return;
                    }
                }
                new_buckets[index] = m_buckets[i];
                new_status[index] = true;
                // primary hash value must be connected to insertion position of new key
                new_primary_hash_values[index] = temp;
                new_lines[index] = m_lines[i];
            }
        }
        delete[] m_buckets;
        delete[] m_status;
        delete[] m_lines;
        delete[] m_primary_hash_values;

        m_buckets = new_buckets;
        m_status = new_status;
        m_lines = new_lines;
        m_primary_hash_values = new_primary_hash_values;
        m_capacity = new_capacity;
    }

    unsigned steps(unsigned start, unsigned finish) const {
        int res = 0;
        if (finish < start) {
            res = (m_capacity - start + finish) / 2;
        } else {
            res = (finish - start) / 2;
        }
        return res;
    }

private:
    std::pair<std::string, AutoDocs>* m_buckets;
    bool* m_status;
    int* m_lines;
    int* m_primary_hash_values;
    size_type m_capacity;
    size_type m_size;
    const float m_threshold_upper;
    const float m_threshold_lower;
};

#endif // HASHTABLE_HPP
