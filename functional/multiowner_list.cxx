#include <memory>

template <typename T>
class list {
public:
   // ... 
  ~node()
  {
    auto next_node = std::move(tail);
    while (next_node) {
      if (!next_node.unique())
        break;
      
      std::shared_ptr<node> tail;
      std::swap(tail, next_node->tail);
      next_node.reset();

      next_node = std::move(tail);
    }
  }
  // ... 
private:
  struct node {
    T value;
    std::shared_ptr<node> tail;
  };

  std::shared_ptr<node> m_head;
}
