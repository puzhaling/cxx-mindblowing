#ifndef FS_UNITS_HPP
#define FS_UNITS_HPP

#include <string>
#include <vector>
#include <memory>
#include <concepts>
#include <type_traits>

class Directory;
class File;

class IComponent : public std::enable_shared_from_this<IComponent> {
 public:
  IComponent(std::string&&, std::string&&);
  IComponent(const std::string&, const std::string&);
  virtual ~IComponent() {}

  virtual void info() const = 0;
  
  ///
  std::string& getname() { return name_; }
  std::string& getpath() { return path_; }
  
 protected:
  std::string name_;
  std::string path_;
};

class Directory final : public IComponent {
 public:
  Directory(std::string&&, std::string&&);
  Directory(const std::string&, const std::string&);
  virtual ~Directory() override {} 

  virtual void info() const override;
  void add(std::shared_ptr<IComponent>);
  void set_parent(std::shared_ptr<Directory>& parent);
  std::weak_ptr<Directory> get_parent();
  const std::vector<std::shared_ptr<IComponent>>& get_components() const;

 private:
  std::vector<std::shared_ptr<IComponent>> components_;
  std::weak_ptr<Directory> parent_;
};

class File final : public IComponent {
 public:
  File(std::string&&, std::string&&);
  File(const std::string&, const std::string&);
  virtual ~File() override {}

  virtual void info() const override;
};

#endif // FS_UNITS_HPP

