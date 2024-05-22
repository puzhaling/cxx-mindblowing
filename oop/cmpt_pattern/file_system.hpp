#if !defined(FILE_SYSTEM_HPP)
#define FILE_SYSTEM_HPP

#include <string>
#include <string_view>
#include <vector>
#include <memory>

class icomponent {
 public:
  virtual void info() const = 0;
  std::string_view get_name() const;
  std::string_view get_type() const;

 private:
  std::string m_name;
  std::string m_type;
};

class directory : public icomponent {
 public:
  virtual void info() const override;
  void add(std::unique_ptr<icomponent*>&);

 private:
  std::vector<std::unique_ptr<icomponent*>> m_components;
};

class file : public icomponent {
 public:
  virtual void info() const override;
};

struct node {
  std::unique_ptr<icomponent*> value = nullptr;
  std::unique_ptr<icomponent*> left = nullptr;
  std::unique_ptr<icomponent*> right = nullptr; 
};

#endif // FILE_SYSTEM_HPP
