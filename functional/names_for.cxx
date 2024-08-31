#include <vector>
#include <string>

template <typename FilterFunction>
std::vector<std::string> names_for(
        const std::vector<person_t> &people,
        FilterFunction filter)
{
  std::vector<std::string> result;

  /* 
     using STL is good, but it doesn't a rule.
     because STL solution requires additional
     dynamic memory allocation, it suits better
     to use a simple loop. btw, it's where 'ranges'
     lib come in handy. it solves STL problem, that
     it's algorithms aren't good suitable for
     function compositions. 
  */
  for (const person_t &person : people)
    if (filter(person))
      result.push_back(name(person));

  return result;
}


/*
  tail-recursion to make function clearer 
  (result push backing is not a sign of pure function)
  also compiler optimizations works here and tail recursion
  will be converted to a simple loop
*/
template <typename FilterFunction, typename Iterator>
std::vector<std::string> names_for_helper(
        Iterator people_begin,
        Iterator people_end,
        FilterFunction filter,
        std::vector<std::string> previously_collected)
{
  if (people_begin == people_end) {
    return previously_collected;
  } else {
    const auto head = *people_begin;

    if (filter(head))
      previously_collected.push_back(name(head));

    return names_for_helper(
        people_begin + 1,
        people_end,
        filter,
        std::move(previously_collected));
  }
}

// function for user needs
template <typename FilterFunction, typename Iterator>
std::vector<std::string> names_for(
        Iterator people_begin,
        Iterator people_end,
        FilterFunction filter)
{
  return names_for_helper(people_begin,
                          people_end,
                          filter,
                          {});
}

