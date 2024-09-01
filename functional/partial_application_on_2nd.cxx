template<typename Function, typename SecondArgType>
class partial_application_on_2nd {
 public:
  partial_application_on_2nd(Function function,
                             SecondArgType second_arg)
    : function_(function)
    , second_arg_(second_arg)
    {
    }

    // use decltype(auto) for modern compilers
    template<typename FirstArgType>
    auto operator()(FirstArgType &&first_arg) const
      -> decltype(function_(std::forward<FirstArgType>(first_arg),
                            second_arg_))
    {
      return function_(
              std::forward<FirstArgType>(first_arg),
              second_arg_);
    }

 private:
  Function function_;
  SecondArgType second_arg_;
};


// pre c++17 helper function for template argument deduction
// on function call
template <typename Function, typename SecondArgType>
partial_application_on_2nd<Function, SecondArgType>
bind2nd(Function &&function, SecondArgType &&second_arg)
{
  return partial_application_on_2nd<Function, SecondArgType>(
            std::forward<Function>(function),
            std::forward<SecondArgType>(second_arg));
}
