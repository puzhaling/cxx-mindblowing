#include <iostream>
#include <vector>
#include <exception>
#include <algorithm>
#include <memory>
#include "units.hpp"

IComponent::IComponent(std::string&& path, std::string&& name) {
  path_ = std::move(path);
  name_ = std::move(name);
}

IComponent::IComponent(const std::string& path, const std::string& name) :
  path_{path}, name_{name}
{}

Directory::Directory(std::string&& path, std::string&& name) :
  IComponent(std::move(path), std::move(name))
{} 

Directory::Directory(const std::string& path, const std::string& name) :
  IComponent(path, name)
{}

void Directory::info() const {
  std::cout << this->name_ << ' ' << this->path_ << '\n';
}

void Directory::add(std::shared_ptr<IComponent> component) {
  component->getpath() = this->path_ + '/' + component->getname();
  if (auto dir_ptr = std::dynamic_pointer_cast<Directory>(component)) 
    dir_ptr->parent_ = std::static_pointer_cast<Directory>(shared_from_this()); 
  components_.push_back(std::move(component));
}

void Directory::set_parent(std::shared_ptr<Directory>& parent) {
  parent_ = parent;
}

std::weak_ptr<Directory> Directory::get_parent() {
  return parent_;
}

const std::vector<std::shared_ptr<IComponent>>& 
Directory::get_components() const {
  return components_;
}

File::File(std::string&& path, std::string&& name) :
  IComponent(std::move(path), std::move(name))
{}

File::File(const std::string& path, const std::string& name) :
  IComponent(path, name)
{}

void File::info() const {
  std::cout << this->name_ << ' ' << this->path_ << '\n';
}

