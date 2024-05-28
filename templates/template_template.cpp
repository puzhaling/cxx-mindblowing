#include <deque>
#include <vector>

template<typename T,
    template<typename Elem> class Cont = std::deque>
class Stack {
private:
    Cont<T> elems;
public:
    ;
};

int main() {
    Stack<int, std::vector> stack; // instead of Stack<int, std::vector<int>>
}
