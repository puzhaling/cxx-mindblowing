class error_test_t {
 public:
  error_test_t(bool error = true)
    : error_(error)
  {
  }

  template <typename T>
  bool operator()(T&& value) const
  {
    return error ==
            (bool)std::forward<T>(value).error();
  }

  error_rest_t operator==(bool test) const
  {
    return error_test_t(
            test ? error_ : !error_
         );
  }

  error_test_t operator!=() const
  {
    return error_test_t(!error_);
  }

  private:
   bool m_error;
};

error_test_t error(true);
error_test_t not_error(false);
