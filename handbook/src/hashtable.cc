#include <algorithm> 
#include <fstream>
#include <sstream> // for std::istringstream

#include "hashtable.h"
#include "rbtree.h" 
#include "utils.h"

HashTable::HashTable()
    : passport_to_fullname_() {
  buckets_ = new std::pair<Key, RBTree>[HashTable::Size()];
  status_ = new bool[HashTable::Size()];
}

int HashTable::Insert(const Passport& passport, const CarSpec& carspec, 
                      const FullName& fullname, const Date& date, 
                      int line_number) { 
  Key key = {passport, date};
  int index = GetPrimaryHash(key);

  auto iter = passport_to_fullname_.find(passport);
  if (iter != passport_to_fullname_.end()) {
    const auto& exist_fullname = iter->second;
    if (exist_fullname != fullname) {
      std::cerr << "HashTable::Insert: two diff people with the same passport\n";
      return -1; 
    }
  } else {
    passport_to_fullname_[passport] = fullname; 
    std::cout << "HashTable::Insert: new passport was added\n";
  }  
  RBTree& tree = buckets_[index].second;
  int res = tree.Insert(passport, carspec, fullname, date, line_number);
  if (res == 0)
    status_[index] = true;
  return res;
}
    

int HashTable::Erase(const Passport& passport, const CarSpec& carspec, 
                     const FullName& fullname, const Date& date) {
  Key key = {passport, date};
  int index = GetPrimaryHash(key);
  if (!status_[index])
    return -1;

  RBTree& tree = buckets_[index].second; 
  return tree.DeleteRBTreeNode(passport, carspec, fullname, date);
}

// returns a pair that includes 
// index of found element as first
// and steps to find it as second
void HashTable::FindAll(
    const Passport& passport,
    const CarSpec& carspec,
    const Date& date,
    std::vector<std::pair<RBTreeNode, int>>& collection) const {
  Key key = {passport, date};
  int index = GetPrimaryHash(key);
  if (!status_[index])
    return;

  RBTree& tree = buckets_[index].second;
  tree.SearchAll(passport, carspec, date, collection); 
  return;
}

int HashTable::GetPrimaryHash(const Key& key) const {
  int result = 0;
  int passport_sum = 0;
  int date_sum = 0;

  const Passport& passport = key.passport;
  for (char ch : passport.series)
    passport_sum += ch;
  for (char ch : passport.number)
    passport_sum += ch;

  const Date& date = key.date;
  for (char ch : date.day)
    date_sum += ch;
  for (char ch : date.month)
    date_sum += ch;
  for (char ch : date.year)
    date_sum += ch;

  int temp = passport_sum + date_sum;
  int last, prelast;
  while (temp > 0) {
    last = temp % 10;
    prelast = (temp % 100) / 10;
    result += (last + prelast);
    result %= HashTable::Size();
    temp /= 100;  
  }
  return result;
}

std::vector<RBTreeNode> HashTable::GetAllNodes() const {
  std::vector<RBTreeNode> all_nodes;
  for (int i = 0; i < HashTable::Size(); ++i) {
    if (status_[i]) {
      std::vector<RBTreeNode> nodes = buckets_[i].second.GetAllRBTreeNodes();
      for (const auto& node : nodes)
        all_nodes.emplace_back(node);
    }
  }
  return all_nodes;
}

void HashTable::PopulateFrom(const std::string& path) {
  if (!PathIsValid(path))
    return;
  
  std::ifstream input_stream(path.c_str());
  std::string line;
  int line_number = 1;
  while (std::getline(input_stream, line)) {
    std::istringstream line_buffer(line);
    
    Passport passport;
    CarSpec carspec;
    FullName fullname;
    Date date;

    std::string word;
    int counter = 1;
    bool invalid_number_of_words = false;
    while (line_buffer >> word) {
      switch (counter) {
      case 1:
        passport.series = word;
        break;
      case 2:
        passport.number = word;
        break;
      case 3:
        carspec.make = word;
        break;
      case 4:
        carspec.model = word;
        break;
      case 5:
        fullname.surname = word;
        break;
      case 6:
        fullname.name = word;
        break;
      case 7:
        fullname.patronymic = word;
        break;
      case 8:
        date.day = word;
        break;
      case 9:
        date.month = word;
        break;
      case 10:
        date.year = word;
        break; 
      default:
        invalid_number_of_words = true;
        break;
      }
      counter++; 
    }
    if (invalid_number_of_words) {
      std::cout << "Error: invalid number of words at line: " << line_number << std::endl;
    } else {
      if (!IsValid(passport) || !IsValid(carspec) || !IsValid(fullname) ||
          !IsValid(date)) {
            std::cout << "Error: invalid line format at line: " << line_number << std::endl; 
      } else {
        this->Insert(passport, carspec, fullname, date, line_number);
      } 
    }
    line_number++;
  }
  input_stream.close();
}

void HashTable::PopulateWith(const std::vector<RBTreeNode>& nodes) {
  for (const auto& node : nodes) 
    this->Insert(node.passport, node.carspec, node.fullname, 
                 node.date, node.line_number);
}

int HashTable::size_ = 5;

int HashTable::Size() {
  return size_;
}
