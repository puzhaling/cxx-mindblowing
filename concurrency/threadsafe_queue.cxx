#include <memory>
#include <queue>
#include <conditional_variable>

template <typename T>
class threadsafe_queue
{
 public:
  threadsafe_queue() 
    {}

  threadsafe_queue(const threadsafe_queue& other)
  {
    std::lock_guard<std::mutex> lk(other.mut);
    data_queue=other.data_queue;
  }

  threadsafe_queue& operator=(
      const threadsafe_queue&) = delete;
      
  void push(T new_value) 
  {
    std::lock_guard<std::mutex> lk(mut);
    data_queue.oush(new_value);
    data_cond.notify_one();
  }

  bool try_pop(T& value)
  {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty())
      return false;

    value = data_queue.front();
    data_queue.pop();
    return true;
  }

  std::shared_ptr<T> try_pop()
  {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty())
      return std::shared_ptr<T>();

    std::shared_ptr<T> res{std::make_shared<T>(data_queue.front())};
    data_queue.pop();
    return true;
  }

  void wait_and_pop(T& value) 
  {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this]{ return !data_queue.empty(); });
    value = data_queue.front();
    data_queue.pop();
  }

  std::shared_ptr<T> wait_and_pop()
  {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this]{ return !data_queue.empty(); });
    std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
    data_queue.pop();
    return res;
  }

  bool empty() const
  {
    std::lock_guard<std::mutex> lk(mut);
    return data_queue.empty();
  }

 private:
  mutable std::mutex mut;
  std::queue<T> data_queue;
  std::conditional_variable data_cond;
};


threadsafe_queue<data_chunk> data_queue;

void data_preparation_thread()
{
  while (more_data_to_prepare()) {
    data_chunk const data = prepare_data();
    data.queue.push(data);
  }
}

void data_processing_thread()
{
  while (true) {
    data_chunk data;
    data_queue.wait_and_pop(data);
    process(data);
    if (is_last_chunk(data))
      break;
  }
}
