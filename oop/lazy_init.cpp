#include <iostream>
#include <optional>
#include <string>
#include <type_traits>
#include <concepts>

template<typename T>
class Lazy {
public:
	explicit Lazy(const std::string& path);

	T& get();
	void load_resource();

private:
	std::string path_;
	std::optional<T> resource_;
};

template<typename T>
Lazy<T>::Lazy(const std::string& path) :
	path_(path) { }

template<typename T>
T& Lazy<T>::get() {
	if (!resource_)
		load_resource();
	return resource_.value();
}

template<typename T>
void Lazy<T>::load_resource() {
	resource_ = T();
}

namespace mystd {

template<typename T>
concept Item = std::is_destructible_v<T> && !std::is_array_v<T> && !std::is_pointer_v<T>;

template<Item T>
class optional {
 using value_type = T;
public:
	optional(T value);
	~optional();

	constexpr T& operator->();
	constexpr T& operator*();
	constexpr operator bool() const;
	constexpr T& value();

	template<typename U>
	constexpr T value_or(U&&);

private:
	std::unique_ptr<T> value_;
};

}


template<mystd::Item T>
mystd::optional<T>::optional(T value) {

}

template<mystd::Item T>
mystd::optional<T>::~optional() {
	delete value_;
}


int main() {
	Lazy<long long> lazy_init("C:/Users/puzhalin.gp/Documents/resource.txt");
	auto& resource_val = lazy_init.get();
	std::cout << resource_val << '\n';
	return 0;
}
