#ifndef HANDBOOK_HASHTABLE_H_
#define HANDBOOK_HASHTABLE_H_

#include <iostream>
#include <string>
#include <utility>
#include "autodocs.h"

class HashTable {
 public:
  HashTable(); 
  explicit HashTable(std::size_t); 
  ~HashTable(); 

  void Insert(const std::string&, const AutoDocs&, int); 
  void Erase(const std::string&, const AutoDocs&); 
  std::pair<std::size_t, unsigned> Find(const std::string&) const; 
  std::size_t MaxSize() const; 
  std::size_t Size() const; 
  std::size_t Capacity() const; 
  int operator[] (std::size_t) const; 

  friend std::ostream& operator<<(std::ostream&, const HashTable&);

 private:
  std::size_t GetPreviousIndex(std::size_t); 
  float GetLoadFactor() const; 
  std::size_t GetPrimaryHash(const std::string&, std::size_t) const;
  
  std::size_t GetSecondaryHash(std::pair<std::string, AutoDocs>* const, 
                               std::size_t, 
                               std::size_t, 
                               std::string = "") const;

  unsigned GetStepsFromTo(unsigned, unsigned) const;
  void Expand(); 
  void Expand(std::size_t);
  void Shrink();
  void Rehash(std::size_t);

  std::pair<std::string, AutoDocs>* buckets_;
  bool* status_;
  int* lines_;
  int* primary_hash_values_;
  std::size_t capacity_;
  std::size_t size_;
  const float threshold_upper_;
  const float threshold_lower_;
};

#endif // HANDBOOK_HASHTABLE_H_
