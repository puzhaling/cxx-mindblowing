#ifndef GIT_HPP
#define GIT_HPP

#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include "fs/tree.hpp"

class Snapshot;

class Blob {
 public:
  explicit Blob(const std::string&);

  std::string_view text() const;
  std::string_view hash() const;
  void save();   
  void restore(Snapshot&);
   
 private:
  std::string text_; // text inside doc
  std::string hash_; // SHA-1 hash
};

class Snapshot {
 public:  
  Snapshot(const std::string&, std::unique_ptr<Tree>&); 
   
  std::string_view parent_hash() const;
  std::string_view hash() const; 
  std::string_view message() const;

 private:
  std::string parent_hash_;
  std::string hash_;
  std::string message_;
  std::unique_ptr<Tree> tree_; 
};

class Git {
 public:
  void add(const Blob&);
  void commit(const std::string&);
  void checkout(const std::string&);
  void log() const;

 private:
  std::vector<Snapshot> commits_;
   // m_fs;
};

#endif // GIT_HPP
