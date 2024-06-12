#include <iostream>
#include <memory>
#include <concepts>
#include <exception>
#include <type_traits>

template<class T>
  requires std::destructible<T>  // basic type requirement
class optional {
 public:
  constexpr optional() : has_value_(false) {}; // (1)
  
  template<class U = T>
  constexpr optional(U&& value) {
  
  }

  ~optional() {
    if (has_value_ && !std::is_trivially_destructible_v<T>)
      value_.~T();
  }


  // observers:
  constexpr T* operator->() noexcept { return &value_; }
  constexpr T& operator*() & noexcept { return value_; }
  constexpr explicit operator bool() const noexcept { return has_value_ ? true : false; }
  constexpr bool has_value() const noexcept { return bool(*this); }
 
  constexpr T& value() & {
    if (!has_value_) 
      throw std::exception("no value");
    return value_;
  }

  template<class U>
  constexpr T value_or(U&& default_value) const& {
    return bool(*this) ? **this : static_cast<T>(std::forward<U>(default_value));
    //                  ^^^^ (*this), maybe??
  }




  // modifiers:
  
  // T must be swappable 
  void swap(optional& other) noexcept {
    if (!this->has_value_ && !other.has_value())
      return;

    // in progress...
    
  }

  void reset() noexcept {
    if (has_value_) 
      value_.~T();
  }

 private:
  union {
    T value_;
  };
  bool has_value_;
};

int main() {
  int x = 5;
  return 0;
}
