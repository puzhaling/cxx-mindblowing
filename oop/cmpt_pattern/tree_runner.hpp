#if !defined(TREE_RUNNER_HPP)
#define TREE_RUNNER_HPP

#include <type_traits>
#include <concepts>
#include <string>
#include "file_system.hpp"

template<typename T>
concept is_directory = 
   std::is_pointer_v<T> == true &&
   std::is_base_of_v<icomponent, std::remove_pointer_t<T>> &&
   std::is_base_of_v<directory, std::remove_pointer_t<T>>;

class tree_runner {
 public:
  template<typename T>
   requires is_directory<T>
  tree_runner(T address) :
    m_root{static_cast<directory*>(address)}, 
    m_runner{static_cast<directory*>(address)} 
  {} 
  tree_runner(const volatile tree_runner&) = delete;

  void cd(const std::string&);
  void ls() const;
  void pwd() const;
  void mkdir(const std::string&);
  void touch(const std::string&);
  void find(const std::string&) const; 

 private:
  directory* m_root;
  directory* m_runner;
};

#endif // TREE_RUNNER_HPP
