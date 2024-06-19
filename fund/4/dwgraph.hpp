#if !defined(DWGRAPH_HPP)
#define DWGRAPH_HPP

#include <vector>
#include <iostream>

class graph {
 public:
  explicit graph(unsigned); 
  virtual ~graph() = default;

  virtual void add_node() = 0;
  virtual void add_edge(unsigned, unsigned, unsigned) = 0;
  virtual void erase_node(unsigned) = 0;
  virtual void erase_edge(unsigned, unsigned) = 0;

 protected:
  std::vector<unsigned> nodes_;
};

struct dijkstra_result {
  unsigned dist;
  std::vector<unsigned> path;
};

class dwgraph final : public graph {
 public:
  explicit dwgraph(unsigned);
  virtual ~dwgraph() = default;

  virtual void add_node();
  virtual void add_edge(unsigned, unsigned, unsigned);
  virtual void erase_node(unsigned);
  virtual void erase_edge(unsigned, unsigned);

  dijkstra_result dijkstra_traverse(unsigned, unsigned) const;
  std::vector<unsigned> topologic_sort() const;

  friend std::ostream& operator<<(std::ostream&, const dwgraph&); 

 private:
  void topologic_sort_util(unsigned v, std::vector<bool>& visited, std::vector<unsigned>& result) const;
  bool dfs(unsigned, std::vector<bool>&, std::vector<bool>&) const; // dfs spec to detect cycles
  bool has_cycles() const; 
  std::vector<std::vector<unsigned>> adj_;
};

#endif // DWGRAPH_HPP
