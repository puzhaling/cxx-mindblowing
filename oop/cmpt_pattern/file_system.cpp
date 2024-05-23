#include <iostream>
#include <vector>
#include <exception>
#include <memory>
#include "file_system.hpp"

icomponent::icomponent(std::string&& name) {
  std::string path = "/" + name + "/";
  m_path = std::move(path);
  m_name = std::move(name);
} 

icomponent::icomponent(const std::string& name) :
  m_name{name}
{
  std::string path = "/" + name + "/";
  m_path = std::move(path);
}

void icomponent::set_name(const std::string& name) {
  m_name = name;
}

void icomponent::set_path(const std::string& path) {
  m_path = path;
}

directory::directory(std::string&& name) :
  icomponent(std::move(name))
{} 

directory::directory(const std::string& name) :
  icomponent(name)
{}

void directory::get_info() const {

}

file::file(std::string&& name) :
  icomponent(std::move(name))
{}

file::file(const std::string& name) :
  icomponent(name)
{}

void file::get_info() const {

}

