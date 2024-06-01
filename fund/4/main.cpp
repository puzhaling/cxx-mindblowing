#include <iostream>
#include "graph.hpp"

int main() {
  unsigned n = 0;
  std::cin >> n;
  
  digraph d(n);

  n *= n;
  unsigned from = 0;
  unsigned to = 0;
  unsigned wt = 0;
  while (n--) {
    std::cin >> from >> to >> wt;
    d.add_edge(from, to, wt);
  }
    
  std::cout << '\n' << d;

  std::cout << '\n' << "after adding node:\n";
  d.add_node();
  std::cout << d;

  std::cout << '\n' << "after deleting node 2:\n";
  d.erase_node(2);
  std::cout << d;

  std::cout << '\n' << "after adding node:\n";
  d.add_node();
  std::cout << d;

  
  return 0;
}
