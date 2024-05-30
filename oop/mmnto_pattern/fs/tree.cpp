#include <typeinfo>
#include <memory>
#include <string>
#include <sstream>
#include <vector>
#include <functional>
#include "tree.hpp"
#include "units.hpp"

static std::vector<std::string> split(const std::string& str) {
  std::istringstream sstream(str);
  std::string part;
  std::vector<std::string> parts;
  while (std::getline(sstream, part, '/')) {
    if (!part.empty())
      parts.push_back(std::move(part));
  }
  return parts;
}

Tree::Tree(const std::string& name) {
  root_ = std::make_shared<Directory>(name, name);
  cwd_ = root_;
}

void Tree::cd(const std::string& path) {
  if (path.empty()) {
    cwd_ = root_;
    return;
  }

  std::vector<std::string> parts = split(path);
  std::shared_ptr<Directory> newCwd = cwd_;
  if (parts[0] == "") {
    newCwd = root_;
    parts.erase(parts.begin());
  }
  
  for (const auto& part : parts) {
    if (part == "..") {
      if (auto parent = newCwd->get_parent().lock())
        newCwd = parent;     
      else 
        return;
    } else {
      bool found = false;
      for (const auto& component : newCwd->get_components()) {
        if (component->getname() == part && std::dynamic_pointer_cast<Directory>(component)) {
          found = true;
          newCwd = std::static_pointer_cast<Directory>(component);
          break;
        }
      }
      if (!found)
        return;
    }
  }
  cwd_ = std::static_pointer_cast<Directory>(newCwd);
}

void Tree::ls() const {
  for (const auto& component : cwd_->get_components()) 
    std::cout << component->getpath() << '\n';
}

void Tree::pwd() const {
  std::cout << cwd_->getpath() << '\n';
}

void Tree::mkdir(const std::string& name) {
  auto dir = std::make_shared<Directory>(cwd_->getpath() + '/' + name, name);
  dir->set_parent(cwd_);
  cwd_->add(dir); 
}

void Tree::touch(const std::string& name) {
  auto file = std::make_shared<File>(cwd_->getpath() + '/' + name, name);
  cwd_->add(std::move(file));
}

void Tree::find(const std::string& name) const {
  if (name.empty())
    return;

  std::function<void(const std::shared_ptr<Directory>&)> finder =
    [&](const std::shared_ptr<Directory>& dir) {
      for (const auto& component : dir->get_components()) {
        if (component->getname() == name)
          std::cout << component->getpath() << '\n';
        if (auto sub_dir = std::dynamic_pointer_cast<Directory>(component))
          finder(sub_dir);
      }
    };
  finder(root_);
}

