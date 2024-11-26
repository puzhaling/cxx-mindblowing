#include <assert>
#include <memory>

public:
  int type;
};

class init_t {
};

class running_t {
public:
  running_t(const std::string& url)
    : m_web_page(url)
  {
  }

  void count_words(const std::string& web_page)
  {
    m_count = std::distance(
            std::istream_iterator<std::string>(m_web_page),
            std::istream_iterator<std::string>());
  }

  unsigned count() const
  {
    return m_count;
  }

private:
  unsigned m_count = 0;
  std::istream m_web_page;
};

class finished_t {
public:
  unsigned count() const
  {
    return m_count;
  }

private:
  unsigned m_count;
};

class program_t {
public:
  program_t()
    : m_state(init_t())
  {
  }

  // ...

  void counting_finished()
  {
    const auto* state = std::get_if<running_t>(&m_state);

    assert(state != nullptr);

    m_state = finished_t(state->count());
  }
  
private:
  std::variant<init_t, running_t, finished_t> m_state;
};
