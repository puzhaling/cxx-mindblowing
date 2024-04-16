#ifndef ITERATOR_HPP
#define ITERATOR_HPP

constexpr std::ptrdiff_t distance(auto first, auto last)
{  
    if (first == last)
    {
        return 0;
    } 
    
    std::ptrdiff_t result{};
    if (first < last)
    {
        while (first != last)
        {
            first++;
            result++;
        }
        return result;
    }
    else 
    {
        while (last != first)
        {
            last++;
            result++;
        }
        return -result;
    }
}

#endif // ITERATOR_HPP
