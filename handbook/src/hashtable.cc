#include <utility>
#include <iostream>
#include <string>
#include <limits>
#include "hashtable.h"

HashTable::HashTable() 
    : capacity_(8), 
      size_(0), 
      threshold_upper_(0.8f), 
      threshold_lower_(0.2f) {
  buckets_ = new std::pair<std::string, AutoDocs>[capacity_]();
  status_ = new bool[capacity_]();
  lines_ = new int[capacity_]();
  primary_hash_values_ = new int[capacity_]();
}

HashTable::HashTable(std::size_t N) 
    : capacity_(N), 
      size_(0), 
      threshold_upper_(0.8f), 
      threshold_lower_(0.2f) {
  buckets_ = new std::pair<std::string, AutoDocs>[capacity_]();
  status_ = new bool[capacity_]();
  lines_ = new int[capacity_]();
  primary_hash_values_ = new int[capacity_]();
}

HashTable::~HashTable() {
  delete[] buckets_;
  delete[] status_;
  delete[] lines_;
  delete[] primary_hash_values_;
}

void HashTable::Insert(const std::string& key, const AutoDocs& value, int line) {
  if (Find(key).first != -1) {
    std::cout << "duplicate key. insertion is cancelled\n";
    return;
  }
  if (GetLoadFactor() >= threshold_upper_)
    Expand();

  std::size_t index = GetPrimaryHash(key, capacity_);
  std::size_t temp = index;
   
  if (status_[index]) {
    index = GetSecondaryHash(buckets_, index, capacity_);
    if (index == -1) {
      Expand(capacity_ * 1.5);
      Insert(key, value, line);
      return;
    }
  }

  buckets_[index] = std::make_pair(key, value);
  status_[index] = true;

  // primary hash value must be connected to final insertion position of a new key
  primary_hash_values_[index] = temp;
  lines_[index] = line;
  size_++;
}
    
std::size_t HashTable::GetPreviousIndex(std::size_t index) {
  switch (index) {
  case 0: return capacity_ - 2; break;
  case 1: return capacity_ - 1; break;
  default: return index - 2; break;
  }
}
 

void HashTable::Erase(const std::string& key, const AutoDocs& value) {
  using std::swap;
  std::size_t index = Find(key).first;
  if (index == -1)
    return;
  if (buckets_[index].second != value) 
    return;

  buckets_[index].first = "";
  status_[index] = false;
  lines_[index] = 0;
  primary_hash_values_[index] = -1;
  size_--;

  std::size_t target_hash = GetPrimaryHash(key, capacity_);
  
  std::size_t prev_prev_hash = GetPrimaryHash(buckets_[GetPreviousIndex(index)].first, capacity_);
  std::size_t next_next_hash = GetPrimaryHash(buckets_[GetPreviousIndex(index)].first, capacity_);
  if (prev_prev_hash == next_next_hash) {
    if (GetLoadFactor() <= threshold_lower_)
      Shrink();
    else 
      Rehash(capacity_);
    return;
  }

  index = (index + 2) % capacity_;
  while (status_[index] && GetPrimaryHash(buckets_[index].first, capacity_) == target_hash) {
    swap(buckets_[GetPreviousIndex(index)], buckets_[index]);
    swap(lines_[GetPreviousIndex(index)], lines_[index]);
    swap(status_[GetPreviousIndex(index)], status_[index]);
    swap(primary_hash_values_[GetPreviousIndex(index)], primary_hash_values_[index]);
    index = (index + 2) % capacity_;
  } 

  // since 'index' stops on non empty bucket, 
  // we need to get GetPreviousIndex(index) value to get the right pos
  std::size_t empty_index = GetPreviousIndex(index);
  std::size_t current_index = empty_index;
  target_hash = empty_index;

  for (std::size_t i = 0; i < capacity_; ++i) {
    if (status_[i] && primary_hash_values_[i] == target_hash && i != current_index) {
      while (status_[current_index])
        current_index = (current_index + 2) % capacity_;
      
      swap(buckets_[i], buckets_[current_index]);
      swap(lines_[i], lines_[current_index]);
      swap(status_[i], status_[current_index]);
      swap(primary_hash_values_[i], primary_hash_values_[current_index]);
    }            
  }

  if (GetLoadFactor() <= threshold_lower_)
    Shrink();
}

//        index,     steps 
std::pair<std::size_t, unsigned> HashTable::Find(const std::string& key) const {
  std::size_t index = GetPrimaryHash(key, capacity_);
  if (buckets_[index].first == "")
    return std::make_pair(-1, 1);
  else if (buckets_[index].first == key)
    return std::make_pair(index, 1);

  int start = index;
  index = GetSecondaryHash(buckets_, index, capacity_, key);
  int finish = index;

  if (index == -1)
    return std::make_pair(-1, capacity_);
  else
    return std::make_pair(index, GetStepsFromTo(start, finish));
}

std::size_t HashTable::MaxSize() const {
  return std::numeric_limits<std::size_t>::max() / sizeof(AutoDocs);
}

std::size_t HashTable::Size() const {
  return size_;
}

std::size_t HashTable::Capacity() const {
  return capacity_;
}

int HashTable::operator[] (std::size_t index) const {
  return lines_[index];
}

std::ostream& operator<<(std::ostream& out, const HashTable& table) {
  for (std::size_t i = 0; i < table.capacity_; ++i) {
    if (table.status_[i]) {
      std::size_t len = table.buckets_[i].first.length();
      out << table.buckets_[i].first;

      while (len++ != 30) 
          out << ' ';

      out << '\t';
      out << '{' << table.buckets_[i].second << '}' << '\t';
      out << "\thash value: {" << table.primary_hash_values_[i] << "}";
      out << " index: " << i << '\n';
    }
  }
  return out;
} 

float HashTable::GetLoadFactor() const {
  return static_cast<float>(size_) / capacity_;
}

std::size_t HashTable::GetPrimaryHash(const std::string& key, 
                                      std::size_t capacity) const {
  std::size_t result = 0;
  std::size_t fullname_sum = 0;
  std::size_t request_sum = 0;

  std::size_t i;
  std::size_t len = key.length();
  for (i = 0; i < len; ++i) {
    if (std::isspace(key[i])) 
        continue;
    if (std::isdigit(key[i])) 
        break;
    fullname_sum += key[i];
  }

  for (;i < len; ++i) 
    request_sum = request_sum * 10 + (key[i] - '0');
  
  std::size_t temp = request_sum + fullname_sum;
  
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

std::size_t HashTable::GetSecondaryHash(
    std::pair<std::string, AutoDocs>* const arr, 
    std::size_t i, 
    std::size_t capacity,
    std::string stopper) const {
  std::size_t steps = 0;
  while (arr[i].first != stopper) {
    if (steps > capacity)
      return -1;
    i = (i + 2) % capacity;
    steps++;
  }
  return i;
}

void HashTable::Expand() {
  std::size_t new_capacity = capacity_ * 2;
  if (new_capacity > this->MaxSize()) 
    throw std::bad_array_new_length();
  Rehash(new_capacity);
}

void HashTable::Expand(std::size_t capacity) {
  if (capacity > this->MaxSize()) 
    throw std::bad_array_new_length();
  Rehash(capacity);
}

void HashTable::Shrink() {
  std::size_t new_capacity = std::max(static_cast<std::size_t>(8), capacity_ / 2);
  Rehash(new_capacity);
}

void HashTable::Rehash(std::size_t new_capacity) {
  std::pair<std::string, AutoDocs>* new_buckets = new std::pair<std::string, AutoDocs>[new_capacity]();
  bool* new_status = new bool[new_capacity]();
  int* new_GetPrimaryHash_values = new int[new_capacity]();
  int* new_lines = new int[new_capacity]();

  for (std::size_t i = 0; i < capacity_; ++i) {
    if (status_[i]) {
      std::size_t index = GetPrimaryHash(buckets_[i].first, new_capacity);
      std::size_t temp = index;
      if (new_buckets[index].first != "") {
        index = GetSecondaryHash(new_buckets, index, new_capacity);
        if (index == -1) {
          delete[] new_buckets;
          delete[] new_status;
          delete[] new_GetPrimaryHash_values;
          delete[] new_lines;

          /* if after a try to Rehash we have no places to insert, we try again, but with the different size.
             a bit larger new cap if Rehash is called from Expand();
             a bit smaller one if Rehash is called from shrink(). */
          if (new_capacity < capacity_) 
            Rehash(new_capacity + new_capacity / 2);
          else 
            Rehash(new_capacity * 1.25);

          return;
        }
      }
      new_buckets[index] = buckets_[i];
      new_status[index] = true;
      // primary hash value must be connected to insertion position of new key
      new_GetPrimaryHash_values[index] = temp;
      new_lines[index] = lines_[i];
    }
  }
  delete[] buckets_;
  delete[] status_;
  delete[] lines_;
  delete[] primary_hash_values_;

  buckets_ = new_buckets;
  status_ = new_status;
  lines_ = new_lines;
  primary_hash_values_ = new_GetPrimaryHash_values;
  capacity_ = new_capacity;
}

unsigned HashTable::GetStepsFromTo(unsigned start, unsigned finish) const {
  int res = 0;
  if (finish < start) {
    res = (capacity_ - start + finish) / 2;
  } else {
    res = (finish - start) / 2;
  }
  return res;
}

