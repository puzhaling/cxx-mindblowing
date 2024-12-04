class MyClass {
public:
    MyClass() = default;
    MyClass(const MyClass&) = delete; 
    MyClass(MyClass&&) = default; 
};

template<typename T>
void foo(T obj) {
}

int main() {
    foo(MyClass()); // c++17 feature 
}
