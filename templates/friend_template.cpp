#include <deque>

template<typename T>
class Stack {
private:
    std::deque<T> elems;

public:
    template<typename T2>
    Stack& operator=(Stack<T2> const&);

    // for private members access of Stack<T2> for any T2 type
    template<typename> friend class Stack; 
};
