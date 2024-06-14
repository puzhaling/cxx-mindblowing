#include <iostream>
#include <memory>
#include <concepts>
#include <exception>
#include <utility>
#include <functional>
#include <type_traits>

template<class T>
  requires (std::destructible<T> && 
            !std::is_array_v<T> && 
            !std::is_lvalue_reference_v<T> && 
            !std::is_rvalue_reference_v<T>)  // basic type requirement
class optional {
 public:
  constexpr optional() : has_value_(false) {}; // (1)

  template<class ...Args>
  constexpr explicit optional(std::in_place_t, Args&&... args)
      : has_value_(true) {
    new (&value_) T(std::forward<Args>(args)...); 
  }

  template<class U = T>
  constexpr optional& operator=(U&& value)
    requires (!std::same_as<std::remove_cvref_t<U>, optional> &&
              std::constructible_from<T, U> &&
              std::assignable_from<T&, U>) {
              //(/*!std::is_scalar_v<T> ||*/ !std::same_as<std::decay_t<U>, T>))  
      if (this->has_value()) {
      value_ = std::forward<U>(value); 
    } else {
      this->emplace(std::forward<U>(value)); 
    }
    return *this;
  }

  ~optional() {
    if (has_value_ && !std::is_trivially_destructible_v<T>)
      value_.~T();
  }


  // # observers:
  constexpr const T* operator->() const noexcept { return &value_; }
  constexpr T* operator->() noexcept { return &value_; }
  constexpr const T& operator*() const& noexcept { return value_; }
  constexpr T& operator*() & noexcept { return value_; }
  constexpr explicit operator bool() const noexcept { return has_value_ ? true : false; }
  constexpr bool has_value() const noexcept { return bool(*this); }
 
  constexpr T& value() & {
    if (!has_value_) 
      throw std::bad_exception();
    return value_;
  }

  template<class U>
    requires std::is_copy_constructible_v<T> && std::is_convertible_v<U&&, T> 
  constexpr T value_or(U&& default_value) const& {
    return has_value_ ? **this : static_cast<T>(std::forward<U>(default_value));
  }


  // # monadic operations: 
  template<class F>
  constexpr auto and_then(F&& f) & {
    if (has_value_) {
      return std::invoke(std::forward<F>(f), *this); 
    } else {
      return std::remove_cvref_t<std::invoke_result_t<F, T&>>();
    } 
  }


  // # modifiers:

  // T must be swappable 
  template<class U = T>
    requires std::is_move_constructible_v<T>
  void swap(optional& other) noexcept {
    if (!this->has_value_ && !other.has_value_)
      return;

    if (has_value_ && !other.has_value_) {
      other.emplace(std::move(**this));
      reset();
    } else if (!has_value_ && other.has_value_) {
      emplace(std::move(*other));
      other.reset(); 
    } else {
      using std::swap;
      swap(**this, *other);
    } 
  }

  void reset() noexcept {
    if (has_value_) {
      value.~T();
      has_value_ = false; 
    }
  }

  template<class ...Args>
    requires std::is_constructible_v<T, Args...>
  T& emplace(Args&&... args) {
     if (has_value_) {
       value_.~T();
       has_value_ = false;
     }

     new (&value_) T(std::forward<Args>(args)...);
     has_value_ = true;

     return value_;
  }

 private:
  union {
    T value_;
  };
  bool has_value_;
};

int main() {
  optional<int> opt1(std::in_place, 7); 
  optional<int> opt2(std::in_place, 9);
  opt1.reset();
  
  opt1.swap(opt2);
  std::cout << opt1.value() << ' ' << opt2.value() << '\n';
  return 0;
}
