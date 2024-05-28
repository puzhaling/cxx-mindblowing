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
        capacity_(8), 
        size_(0),
        threshold_upper_(0.8f), 
        threshold_lower_(0.2f) 
    {
        buckets_ = new std::pair<std::string, AutoDocs>[capacity_]();
        status_ = new bool[capacity_]();
        lines_ = new int[capacity_]();
        phashes_ = new int[capacity_]();
    }

    HashTable(size_type N) : 
        capacity_(N), 
        size_(0), 
        threshold_upper_(0.8f), 
        threshold_lower_(0.2f) 
    {
        buckets_ = new std::pair<std::string, AutoDocs>[capacity_]();
        status_ = new bool[capacity_]();
        lines_ = new int[capacity_]();
        phashes_ = new int[capacity_]();
    }

    ~HashTable() {
        delete[] buckets_;
        delete[] status_;
        delete[] lines_;
        delete[] phashes_;
    }

    void insert(const std::string& key, const AutoDocs& value, int line) {
        if (find(key).first != -1) {
            std::cout << "duplicate key. insertion is cancelled\n";
            return;
        }
        if (load_factor() >= threshold_upper_)
            expand();

        size_type index = primary_hash(key, capacity_);
        size_type temp = index;
         
        if (status_[index]) {
            index = secondary_hash(buckets_, index, capacity_);
            if (index == -1) {
                expand(capacity_ * 1.5);
                insert(key, value, line);
                return;
            }
        }

        buckets_[index] = std::make_pair(key, value);
        status_[index] = true;

        // primary hash value must be connected to final insertion position of a new key
        phashes_[index] = temp;
        lines_[index] = line;
        size_++;
    }
    
    size_type previous_index(size_type index) {
        switch (index) {
        case 0: return capacity_ - 2; break;
        case 1: return capacity_ - 1; break;
        default: return index - 2; break;
        }
    } 

    void erase(const std::string& key, const AutoDocs& value) {
        using std::swap;

        size_type index = find(key).first;
        if (index == -1)
            return;
        if (buckets_[index].second != value) 
            return;

        buckets_[index].first = "";
        status_[index] = false;
        lines_[index] = 0;
        phashes_[index] = -1;
        size_--;

        size_type target_hash = primary_hash(key, capacity_);
        
        size_type prev_prev_hash = primary_hash(buckets_[previous_index(index)].first, capacity_);
        size_type next_next_hash = primary_hash(buckets_[previous_index(index)].first, capacity_);
        if (prev_prev_hash == next_next_hash) {
            if (load_factor() <= threshold_lower_)
                shrink();
            else 
                rehash(capacity_);
            return;
        }

        index = (index + 2) % capacity_;
        while (status_[index] && primary_hash(buckets_[index].first, capacity_) == target_hash) {
            swap(buckets_[previous_index(index)], buckets_[index]);
            swap(lines_[previous_index(index)], lines_[index]);
            swap(status_[previous_index(index)], status_[index]);
            swap(phashes_[previous_index(index)], phashes_[index]);
            index = (index + 2) % capacity_;
        } 

        // since 'index' stops on non empty bucket, 
        // we need to get previous_index(index) value to get the right pos
        size_type empty_index = previous_index(index);
        size_type current_index = empty_index;
        target_hash = empty_index;

        for (size_type i = 0; i < capacity_; ++i) {
            if (status_[i] && phashes_[i] == target_hash && i != current_index) {
                while (status_[current_index])
                    current_index = (current_index + 2) % capacity_;
                
                swap(buckets_[i], buckets_[current_index]);
                swap(lines_[i], lines_[current_index]);
                swap(status_[i], status_[current_index]);
                swap(phashes_[i], phashes_[current_index]);
            }            
        }

        if (load_factor() <= threshold_lower_)
            shrink();
    }
    
    //        index,     steps to find 
    std::pair<size_type, unsigned> find(const std::string& key) const {
        size_type index = primary_hash(key, capacity_);
        if (buckets_[index].first == "")
            return std::make_pair(-1, 1);
        else if (buckets_[index].first == key)
            return std::make_pair(index, 1);
      
        int start = index;
        index = secondary_hash(buckets_, index, capacity_, key);
        int finish = index;

        if (index == -1)
            return std::make_pair(-1, capacity_);
        else
            return std::make_pair(index, steps(start, finish));
    }
    
    size_type max_size() const {
        return std::numeric_limits<size_type>::max() / sizeof(AutoDocs);
    }

    size_type size() const {
        return size_;
    }

    size_type capacity() const {
        return capacity_;
    }
    
    int operator[] (size_type index) const {
        return lines_[index];
    }

    friend std::ostream& operator<<(std::ostream& out, HashTable const& table) {
        for (size_type i = 0; i < table.capacity_; ++i) {
            if (table.status_[i]) {
                size_type len = table.buckets_[i].first.length();
                out << table.buckets_[i].first;

                while (len++ != 30) 
                    out << ' ';

                out << '\t';
                out << '{' << table.buckets_[i].second << '}' << '\t';
                out << "\thash value: {" << table.phashes_[i] << "}";
                out << " index: " << i << '\n';
               // out << "line number: " << table.lines_[i] << '\n';
            }
        }
       //out << '[';
       //for (size_type i = 0; i < table.capacity_; ++i)
       //     out << (table.status_[i] ? 1 : 0);
       //out << ']' << '\n';
       return out;
    } 

private:
    float load_factor() const {
        return static_cast<float>(size_) / capacity_;
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
            result %= capacity;
            temp /= 100;
        }
        return result % capacity;
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
        size_type new_capacity = capacity_ * 2;
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
        size_type new_capacity = std::max(static_cast<size_type>(8), capacity_ / 2);
        rehash(new_capacity);
    }

    void rehash(size_type new_capacity) {
        std::pair<std::string, AutoDocs>* new_buckets = new std::pair<std::string, AutoDocs>[new_capacity]();
        bool* new_status = new bool[new_capacity]();
        int* new_primary_hash_values = new int[new_capacity]();
        int* new_lines = new int[new_capacity]();

        for (size_type i = 0; i < capacity_; ++i) {
            if (status_[i]) {
                size_type index = primary_hash(buckets_[i].first, new_capacity);
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
                        if (new_capacity < capacity_) 
                            rehash(new_capacity + new_capacity / 2);
                        else 
                            rehash(new_capacity * 1.25);

                        return;
                    }
                }
                new_buckets[index] = buckets_[i];
                new_status[index] = true;
                // primary hash value must be connected to insertion position of new key
                new_primary_hash_values[index] = temp;
                new_lines[index] = lines_[i];
            }
        }
        delete[] buckets_;
        delete[] status_;
        delete[] lines_;
        delete[] phashes_;

        buckets_ = new_buckets;
        status_ = new_status;
        lines_ = new_lines;
        phashes_ = new_primary_hash_values;
        capacity_ = new_capacity;
    }

    unsigned steps(unsigned start, unsigned finish) const {
        int res = 0;
        if (finish < start) {
            res = (capacity_ - start + finish) / 2;
        } else {
            res = (finish - start) / 2;
        }
        return res;
    }

private:
    std::pair<std::string, AutoDocs>* buckets_;
    bool* status_;
    int* lines_;
    int* phashes_;
    size_type capacity_;
    size_type size_;
    const float threshold_upper_;
    const float threshold_lower_;
};

#endif // HASHTABLE_HPP
