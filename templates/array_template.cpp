#include <iostream>

template<typename T, int N, int M>
bool less(T(&a)[N], T(&b)[M]) {
    for (int i = 0; i < N && i < M; ++i) {
        if (a[i] < b[i]) return true;
        if (b[i] < a[i]) return false;
    }
    return N < M;
}

int main() {
    int x[] = {1,2,3};
    int y[] = {1,2,3,4,5};
    std::cout << less(x, y) << '\n';
}
