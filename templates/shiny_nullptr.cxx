#include <memory>
#include <mutex>

int f1(std::shared_ptr<int> spw)
{
  return 0;
}

double f2(std::unique_ptr<int> upw)
{
  return 0.0;
}

bool f3(int *pi)
{
  return true;
}

template <typename FuncType,
          typename MuxType,
          typename PtrType>
auto lockAndCall(FuncType func,
                 MuxType& mutex,
                 PtrType ptr) -> decltype(func(ptr))
{
  using MuxGuard =
      std::lock_guard<MuxType>;
  
  MuxGuard g(mutex);
  return func(ptr);
}

int main() {
  std::mutex f1m, f2m, f3m;

  using MuxGuard =
      std::lock_guard<std::mutex>;

  {
    MuxGuard g(f1m);
    auto result = f1(0);
  }

  {
    MuxGuard g(f2m);
    auto result = f2(NULL);
  }

  {
    MuxGuard g(f3m);
    auto result = f3(nullptr);
  }


  auto result1 = lockAndCall(f1, f1m, 0);
  auto result2 = lockAndCall(f2, f2m, NULL);
  auto result3 = lockAndCall(f3, f3m, nullptr);
}
