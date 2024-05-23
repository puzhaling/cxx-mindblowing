#if !defined(FILE_SYSTEM_HPP)
#define FILE_SYSTEM_HPP

#include <string>
#include <vector>
#include <memory>
#include <concepts>
#include <type_traits>

class tree_runner;

class icomponent {
 public:
  icomponent(std::string&&);
  icomponent(const std::string&);
  virtual ~icomponent() {}

  friend class tree_runner;

  virtual void get_info() const = 0;
  std::string get_name() const { return m_name; }
  std::string get_path() const { return m_path; }
  void set_name(const std::string&);
  void set_path(const std::string&);

 private:
  std::string m_name;
  std::string m_path;
};

template<typename T>
concept is_valid_type = 
   std::is_lvalue_reference_v<T> == false && 
   std::is_base_of_v<icomponent, typename T::element_type> &&
   std::is_same_v<std::unique_ptr<typename T::element_type>, std::decay_t<T>>;

class directory final : public icomponent {
 public:
  directory(std::string&&);
  directory(const std::string&);
  virtual ~directory() override {} 

  friend class tree_runner;

  virtual void get_info() const override;

  template<typename T>
   requires is_valid_type<T>
  void add(T&& component) {
    m_components.push_back(std::forward<T>(component));
  } 

 private:
  std::vector<std::unique_ptr<icomponent>> m_components;
};

class file final : public icomponent {
 public:
  file(std::string&&);
  file(const std::string&);
  virtual ~file() override {}

  friend class tree_runner;
  
  virtual void get_info() const override;
};

#endif // FILE_SYSTEM_HPP
