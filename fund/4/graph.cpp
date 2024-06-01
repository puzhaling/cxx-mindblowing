#include <vector>
#include <numeric>
#include <algorithm>
#include "graph.hpp"

digraph::digraph(unsigned N) :
  adj_(N, std::vector<unsigned>(N, 0)), nodes_(N) 
{
  std::iota(nodes_.begin(), nodes_.end(), 1);
}

void digraph::add_node() {
  unsigned n = adj_.size();
  std::vector<unsigned> row(n + 1, 0);
  
  unsigned k = n;
  for (auto it = adj_.begin(); k; --k, ++it) {
    std::copy(it->begin(), it->end(), row.begin());
    *it = row;
  } 
  std::fill(row.begin(), row.end(), 0);
  adj_.push_back(row);
  nodes_.push_back(nodes_.back() + 1);
}

void digraph::add_edge(unsigned from, unsigned to, unsigned wt) {
  unsigned n = adj_.size();
  if (from - 1 >= n || to - 1 >= n)
    return; 

  adj_[from - 1][to - 1] = wt;
}

void digraph::dijkstra_traverse(unsigned from, unsigned to) const {
  // in progress
  unsigned n = adj_.size();
  if (from - 1 >= n || to - 1 >= n)
    return; 

  from = from - 1; 
  to = to - 1; 
  //std::
  //std::
}

void digraph::erase_node(unsigned node_num) {
  unsigned n = adj_.size();
  unsigned node_pos = node_num - 1; 
  if (node_pos >= n)
    return; 
  
  nodes_.erase(nodes_.begin() + node_pos);
  adj_.erase(adj_.begin() + node_pos);

  for (auto it = adj_.begin(); it != adj_.end(); ++it)
    it->erase(it->begin() + node_pos);
}

void digraph::erase_edge(unsigned from, unsigned to) {
  unsigned n = adj_.size();
  if (from - 'a' >= n || to - 'a' >= n)
    return; 
  
  adj_[from - 1][to - 1] = 0;
}

std::ostream& operator<<(std::ostream& out, const digraph& d) {
  unsigned n = d.adj_.size();
  out << ' ' << ' ';
  for (unsigned c : d.nodes_) 
    std::cout << c << ' ';
  out << '\n';
  
  auto node_iter = std::begin(d.nodes_);
  for (unsigned i = 0; i < n; ++i) {
    out << *node_iter++ << ' ';
    for (unsigned j = 0; j < n; ++j)
      out << d.adj_[i][j] << ' '; 
    out << '\n';
  } 
  return out;
}
