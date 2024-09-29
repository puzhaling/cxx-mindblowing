#include <future>
#include <map>

int main() {
  std::promise< std::map< SomeIndexType, SomeDataType, SomeComparator,
      SomeAllocator>::iterator> p;

   // transfers the shared state from *this to shared_future and returns it
  auto sf = p.get_future.share();
}
