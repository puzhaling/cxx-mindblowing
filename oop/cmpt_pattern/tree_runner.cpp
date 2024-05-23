#include <exception>
#include <algorithm>
#include <iostream> 
#include "tree_runner.hpp"
#include "file_system.hpp"

// correct path syntax: /foo/goo/
void tree_runner::cd(const std::string& path) {
  if (path.size() < 3) 
    throw std::length_error("path is too short");

  if (path.front() != '/' || path.back() != '/')
    throw std::runtime_error("invalid path format");

  using std::begin;
  using std::end;
  using std::distance;

  std::vector<std::string> directories;
  
  auto is_slash = [](char c) { return c == '/'; };
  auto left = std::find_if(begin(path), end(path), is_slash);
  auto right = std::find_if(left + 1, end(path), is_slash);
  
  std::string s;
  while (left != end(path)) {
    s = path.substr(distance(begin(path), left + 1), right - left - 1);
    directories.push_back(std::move(s));
    left = right;
    right = std::find_if(left + 1, end(path), is_slash);
  }

  if (directories.front() != m_root->get_name()) {
    std::cout << "no such directory\n";
    return;
  }

  // set m_runner value to this, if dir wasn't found
  auto* runner_reset_value = m_runner;
  // start from top of the file system tree
  m_runner = m_root;

  decltype(directory::m_components)::iterator iter;
  std::size_t directories_idx = 1;
  while (directories_idx < directories.size()) {
    iter = std::find_if(begin(m_runner->m_components), end(m_runner->m_components), 
        [&](const auto& entry) { return entry->get_name() == directories[directories_idx]; });
    if (iter != end(m_runner->m_components) && dynamic_cast<directory*>(iter->get()) != nullptr) {
      m_runner = static_cast<directory*>(iter->get());
      directories_idx++;
    } else {
      break;
    }
  }

  if (directories_idx != directories.size() - 1) {
    std::cout << "no such directory\n";
    m_runner = runner_reset_value;
  }
}

void tree_runner::ls() const {
  std::size_t size = m_runner->m_components.size();
  for (std::size_t i = 0; i < size; ++i) {
    if (dynamic_cast<directory*>(m_runner->m_components[i].get()) != nullptr) 
      std::cout << "d ";
    else if (dynamic_cast<file*>(m_runner->m_components[i].get()) != nullptr) 
      std::cout << "x ";
    std::cout << m_runner->m_components[i]->get_path() << '\n'; 
  }
}

void tree_runner::mkdir(const std::string& name) {
  auto new_dir = std::make_unique<directory>(name);
  new_dir->set_path(m_runner->get_path() + name + "/");
  m_runner->add(std::move(new_dir));
}

void tree_runner::touch(const std::string& name) {
  auto new_file = std::make_unique<file>(name);
  new_file->set_path(m_runner->get_path() + name + "/");
  m_runner->m_components.push_back(std::move(new_file));
}

void tree_runner::find(const std::string& name) const {
  
}

void tree_runner::pwd() const {
  std::cout << m_runner->get_path() << '\n';
}


