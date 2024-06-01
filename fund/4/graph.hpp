#if !defined(GRAPH_HPP)
#define GRAPH_HPP

#include <vector>
#include <iostream>

class digraph {
 public:
  explicit digraph(unsigned);

  void add_node();
  void add_edge(unsigned, unsigned, unsigned);
  void dijkstra_traverse(unsigned, unsigned) const;
  void erase_node(unsigned);
  void erase_edge(unsigned, unsigned);

  friend std::ostream& operator<<(std::ostream&, const digraph&); 

 private:
  std::vector<std::vector<unsigned>> adj_;
  std::vector<unsigned> nodes_;
};

#endif // GRAPH_HPP
