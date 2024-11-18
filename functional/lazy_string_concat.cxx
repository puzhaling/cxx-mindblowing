#include <string>
#include <algorithm>

template <typename... Strings>
class lazy_string_concat_helper;

template <typename LastString, typename... Strings>
class lazy_string_concat_helper<LastString, Strings...> 
{
private:
  LastString data;
  lazy_string_concat_helper<Strings...> tail;

public:
  lazy_string_concat_helper(
          LastString data,
          lazy_string_concat_helper<Strings...> tail)
    : data(data)
    , tail(tail)
  {
  }

  int size() const
  {
    return data.size() + tail.size();
  }

  template <typename It>
  void save(It end) const
  {
    const auto begin = end - data.size();
    std::copy(data.cbegin(), data.cend(),
              begin);
    tail.save(begin);
  }

  operator std::string() const 
  {
    std::string result(size(), '\0');
    save(result.end());
    return result;
  }

  lazy_string_concat_helper<std::string,
                            LastString,
                            Strings...>
  operator+(const std::string& other) const
  {
    return lazy_string_concat_helper
        <std::string, LastString, Strings...>(
              other,
              *this
        );
  }
};

template <>
class lazy_string_concat_helper<> 
{
public:
  lazy_string_concat_helper()
  {
  }

  int size() const
  {
    return 0;
  }

  template <typename It>
  void save(It end) const
  {
  }

  operator std::string() const 
  {
  }

  lazy_string_concat_helper<std::string,
                            LastString,
                            Strings...>
  operator+(const std::string& other) const
  {
    return lazy_string_concat_helper
        <std::string, LastString, Strings...>(
              other,
              *this
        );
  }
};
