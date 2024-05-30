#ifndef FS_TREE_HPP
#define FS_TREE_HPP

#include <iostream>
#include <memory>
#include <string>
#include <stack>
#include "units.hpp"

class Tree {
 public:
  explicit Tree(const std::string&);

  void cd(const std::string&);
  void ls() const;
  void pwd() const;
  void mkdir(const std::string&);
  void touch(const std::string&);  
  void find(const std::string&) const;

 private:
  std::shared_ptr<Directory> root_;
  std::shared_ptr<Directory> cwd_;
};

#endif // FS_TREE_HPP
