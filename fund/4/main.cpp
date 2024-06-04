#include <iostream>
#include "dwgraph.hpp"

int main() {
  unsigned n = 0;
  std::cin >> n;
  
  dwgraph d(n);

  n *= n;
  unsigned from = 0;
  unsigned to = 0;
  unsigned wt = 0;
  while (n--) {
    std::cin >> from >> to >> wt;
    d.add_edge(from, to, wt);
  }
    
  std::cout << '\n' << d;

//  std::cout << '\n' << "after adding node:\n";
//  d.add_node();
//  std::cout << d;

  //std::cout << '\n' << "after deleting node 2:\n";
  //d.erase_node(2);
  //std::cout << d;

//  std::cout << '\n' << "after adding node:\n";
//  d.add_node();
//  std::cout << d;

  auto dijkstra = d.dijkstra_traverse(1, 3);
  for (auto v : dijkstra.path) 
    std::cout << v << ' ';
  std::cout << '\n';
  std::cout << "path weight: " << dijkstra.dist << '\n';
  
  auto sort = d.topologic_sort();
  for (auto v : sort)
    std::cout << v << ' ';
  std::cout << '\n';

  return 0;
}
