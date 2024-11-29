#include <memory>
#include <stdexcept>

template <typename T, typename E>
class expected {
public:
  
  template <typename... Args>
  static expected success(Args&&... params)
  {
    expected result;
    result.m_valid = true;
    new (&result.m_value)
      T(std::forward<Args>(params)...);
    return result;
  }

  template <typename... Args>
  static expected error(Args&&... params)
  {
    expected result;
    result.m_valid = false;
    new (&result.m_error)
      T(std::forward<Args>(params)...);
    return result;
  }
  
  expected(const expected& other)
    : m_valid(other.m_valid)
  {
    if (m_valid) {
      new (&m_value) T(other.m_value);
    } else {
      new (&m_error) E(other.m_error);
    }
  }

  expected(expected&& other)
    : m_valid(other.m_valid)
  {
    if (m_valid) {
      new (&m_value) T(std::move(other.m_value));
    } else {
      new (&m_error) E(std::move(other.m_error));
    }
  }

  ~expected {
    if (m_valid) {
      m_value.~T();
    } else {
      m_error.~E();
    }
  }

  T& get()
  {
    if (!m_valid) {
      throw std::logic_error("Missing a value");
    }

    return m_value;
  }

  E& error()
  {
    if (m_valid) {
      throw std::logic_error("There is no error");
    }

    return m_error;
  }

  void swap(expected& other)
  {
    using std::swap;
    if (m_valid) {
      if (other.m_valid) {
        swap(m_value, other.m_value);
      } else {
        auto temp = std::move(other.m_error);
        other_m_error.~E();
        new (&other.m_value) T(std::move(m_value));
        m_value.~T();
        new (&m_error) E(std::move(temp));
        std::swap(m_valid, other.m_valid);
      }
    } else {
      if (other.m_valid) {
        other.swap(*this);
      } else {
        swap(m_error, other.m_error);
      }
    }
  }

  expected& operator=(expected other)
  {
    swap(other);
    return *this;
  }

private:
  union {
    T m_value;
    E m_error;
  };

  bool m_valid;
};


// example of usage
expected<int, std::string> divide(int numerator, int denominator) {
    if (denominator == 0) {
        return expected<int, std::string>::error("Division by zero");
    }
    return expected<int, std::string>::success(numerator / denominator);
} 
