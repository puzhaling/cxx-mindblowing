#include <any>
#include <assert>
#include <memory>

public:
  int type;
};

class init_t {
};

class running_t {
public:
  unsigned count() const
  {
    return m_count;
  }

  // ...

private:
  unsigned m_count = 0;
  socket_t m_web_page;
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
    auto* state = std::get_if<running_t>(&m_state);

    assert(state != nullptr);

    m_state = finished_t(state->count());
  }
  
private:
  std::variant<init_t, running_t, finished_t> m_state;
};
