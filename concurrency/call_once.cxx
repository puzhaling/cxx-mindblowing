#include <memory>
#include <mutex>

std::shared_ptr<some_resource> resource_ptr;
std::once_flag resource_flag;

void init_resource()
{
  resource_ptr.reset(new some_resource);
}

void foo()
{
  // call_once() executes callable object exactly once
  // even in concurrent manner, once_flag holds sync
  // data. each once_flag holds info for only one call;
  std::call_once(resource_flag, init_resource);
  resource_ptr->do_something();
}
