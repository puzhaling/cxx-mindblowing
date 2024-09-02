template <typename Function>
auto pointer_lift(Function f)
{
  return [f](auto* item) {
    if (item)
      f(*item);
  };
}

template <typename Function>
auto collection_lift(Function f) 
{
  return [f](auto& items) {
    for (auto& item : items)
      f(item);
  };
}
