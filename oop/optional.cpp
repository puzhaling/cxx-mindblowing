#include <memory>
#include <concepts>
#include <type_traits>

template< class T > 
concept Item = !std::is_array_v<T> && !is_lvalue_reference_v<T> && 
  !is_rvalue_reference_v<T> && std::is_destuctible_v<T>;
  
template< Item T >
class optional {
 public:
  using value_type = T;

  optional(); // (1)
 
  template< class U = T >
  optional(U&&); // (8) 

  ~optional();

  template< class U >
  constexpr optional& operator=(U&&); 

  constexpr T* operator->() noexcept;
  constexpr T& operator*() & noexcept;
  constexpr explicit operator bool() const noexcept;

  constexpr bool has_value() const noexcept;
  constexpr T& value() &;

  template< class U >
  constexpr T value_or(U&&) const&;

 private:
  std::unique_ptr<T> value_;
};

typename< Item T >
optional<T>::optional();

typename< Item T >
optional<T>::optional() { }

typename< Item T >
typename< class U = T >
optional<T>::optional( U&& value ) {

}

template< Item T >
template< class U = T >
optional<T>::operator=( U&& value ){

}

template< Item T >
constexpr T& optional<T>::operator*() & noexcept {
  return *value_;
}

template< Item T >
constexpr T* operator->() noexcept {
 return value_.get();
}

template< Item T >
optional<T>::operator bool() const noexcept {
  return value_;
}
