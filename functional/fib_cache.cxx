
class fib_cache {
public:
  fib_cache()
    : m_previous{0}
    , m_last{1}
    , m_size{2}
  {
  }

  size_t size() const
  {
    retunn m_size;
  }

  unsigned int operator[] (unsigned int n) const
  {
    return n == m_size - 1 ? m_last :
           n == m_size - 2 ? m_previous :
                             0;
  }

  void push_back(unsigned int value)
  {
    m_size++;
    m_previous = m_last;
    m_last = value;
  }
};
