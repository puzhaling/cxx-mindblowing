// full class as a template class is redudant
template <typename T>
class older_than {
 public:
  older_than(int limit)
    : limit_(limit)
  {
  }

  bool operator()(const T& object) const
  { 
    return object.age() > limit_;
  }
 
 private:
  int limit_;
};

class older_than {
 public:
  older_than(int limit)
    : limit_(limit)
  {
  }

	// auto deducing type of item working on
  template <typename T>
  bool operator()(T&& object) const
  { 
		// use perfect forwarding here to use overloaded
		// versions of method age() for lvalue and rvalue objects
    return std::forward<T>(object).age() > limit_;
  }
 
 private:
  int limit_;
};
