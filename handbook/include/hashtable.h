#ifndef HANDBOOK_HASHTABLE_H_
#define HANDBOOK_HASHTABLE_H_

#include <iostream>      // for std::cout
#include <string>
#include <vector>
#include <unordered_map> // for std::unordered_map
#include <utility>       // for std::pair

// composite key
#include "core/passport.h"
#include "core/date.h"

// value storage
#include "rbtree.h"

class HashTable {
 public:
  struct Key {
    const Passport passport;
    const Date date; 
  };

 public:
  HashTable();

  // returns -1 if insert is not
  // taking place and 0 otherwise
  int Insert(const Passport&, const CarSpec&, const FullName&, 
             const Date&, int line_number); 

  // returns -1 if the searched node 
  // is not found, 0 if found and deleted
  int Erase(const Passport&, const CarSpec&, const FullName&,
            const Date&); 

  // populate last vector with with pairs of copies of
  // RBTreeNodes and number of steps to find them
  void FindAll(const Passport&, const CarSpec&, const Date&,
               std::vector<std::pair<RBTreeNode, int>>&) const; 

  std::vector<RBTreeNode> GetAllNodes() const;
  void PopulateFrom(const std::string& path);
  void PopulateWith(const std::vector<RBTreeNode>&);
  const std::pair<Key, RBTree>* Data() const { return buckets_; }

  static int Size();

//  friend std::ostream& operator<<(std::ostream&, const HashTable&);

 private:
  static int size_;

  int GetPrimaryHash(const Key&) const;

  std::unordered_map<Passport, FullName> passport_to_fullname_;
  std::pair<Key, RBTree>* buckets_;
  bool* status_;
};

#endif // HANDBOOK_HASHTABLE_H_
