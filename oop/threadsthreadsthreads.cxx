#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <thread>
#include <chrono>
#include <numeric>
#include <utility>
#include <functional>
#include <experimental/random>

#include <cstdlib>

int value = 0;

void a() { value = 1; std::cout << value << '\n'; }
void b() { value = 2; std::cout << value << '\n'; }
void c() { value = 3; std::cout << value << '\n'; }
void d() { value = 4; std::cout << value << '\n'; }

void goo(int* arr, std::size_t size) {
  std::for_each(arr, arr + size,
    [](int& num){ num *= 2; }
  );
}

void fill(int* arr, std::size_t size) {
  std::for_each(arr, arr + size, 
    [](int& num){ num = std::rand(); }
  );
}

void foo() {
  constexpr std::size_t kSize = 1e7;
  int* arr = new int[kSize];

  auto begin = std::chrono::steady_clock::now();
    fill(arr, kSize);
    goo(arr, kSize);
  auto end = std::chrono::steady_clock::now();
  std::cout << "exec before threads: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() 
    << '\n';

  auto part = kSize/4;
  begin = std::chrono::steady_clock::now();
    fill(arr, kSize);
    goo(arr, kSize);
  std::thread t1(goo, arr, part);
  std::thread t2(goo, arr + part, part); 
  std::thread t3(goo, arr + part*2, part);
  std::thread t4(goo, arr + part*3, part);
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  end = std::chrono::steady_clock::now();
  std::cout << "exec after threads: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() 
    << '\n';

  delete[] arr;
}

void sum(const std::array<int, 16>& arr, 
         int start_pos, 
         int end_pos, 
         int& accumulator) {
  for (int i = start_pos; i < end_pos; ++i)
    accumulator += arr[i];
}

void moo() {
  std::array<int, 16> arr;
  std::for_each(arr.begin(), arr.end(), [](int& a){ a = std::experimental::randint(0, 10); });


  for(auto it : arr)
    std::cout << it << " ";
  std::cout << "\n";
  std::pair<int, int> result; 
  std::thread t1(&sum, std::cref(arr), 0, arr.size()/2 + 1, std::ref(result.first));
  std::thread t2(&sum, std::cref(arr), arr.size()/2 + 1, arr.size(), std::ref(result.second));
  t1.join();
  t2.join();

  std::cout << "sum is: " << result.first + result.second << '\n';
}

int main() {
  moo();
  return 0;
}
