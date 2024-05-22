#include "file_system.hpp"
#include <iostream>

std::string_view icomponent::get_name() const {
  return m_name;
}

std::string_view icomponent::get_type() const {
  return m_type;
}

void directory::info() const {
  std::cout << "type: " << this->get_type() << '\n';
  std::cout << "name: " << this->get_name() << '\n';
}

void directory::add(std::unique_ptr<icomponent*>& component) {
  m_components.push_back(std::move(component));
}

void file::info() const {
  std::cout << "type: " << this->get_type() << '\n';
  std::cout << "name: " << this->get_name() << '\n';
}
