#include <vector>
#include <numeric>
#include <algorithm>
#include <memory>
#include <exception>
#include <climits>
#include <iostream>
#include "dwgraph.hpp"

graph::graph(unsigned N) :
  nodes_(N) 
{
  std::iota(nodes_.begin(), nodes_.end(), 1);
}

dwgraph::dwgraph(unsigned N) :
  graph(N), adj_(N, std::vector<unsigned>(N, 0)) { } 

void dwgraph::add_node() {
  unsigned n = adj_.size();
  std::vector<unsigned> row(n + 1, 0);
  
  unsigned k = n;
  for (auto it = adj_.begin(); k--; ++it) {
    std::copy(it->begin(), it->end(), row.begin());
    *it = row;
  } 

  unsigned new_pos = 1;
  for (unsigned node_num : nodes_) {
    if (node_num != new_pos) 
      break;
    new_pos++;
  }
  
  std::fill(row.begin(), row.end(), 0);
  if (new_pos == nodes_.back() + 1) {
    nodes_.push_back(new_pos);
    adj_.push_back(std::move(row));
  } else {
    nodes_.insert(nodes_.begin() + new_pos - 1, new_pos);
    adj_.insert(adj_.begin() + new_pos - 1, std::move(row));
  }
}

void dwgraph::add_edge(unsigned from, unsigned to, unsigned wt) {
  unsigned n = adj_.size();
  if (from - 1 >= n || to - 1 >= n)
    return; 
  adj_[from - 1][to - 1] = wt;
}

static unsigned min_distance(const std::vector<unsigned>& dist, const std::vector<bool>& visited, unsigned n) {
  unsigned min_dist = UINT_MAX;
  unsigned min_index = 0;

  for (unsigned v = 0; v < n; ++v) {
    if (!visited[v] && dist[v] <= min_dist) {
      min_dist = dist[v];
      min_index = v;
    }
  }
  return min_index;
}

dijkstra_result dwgraph::dijkstra_traverse(unsigned from, unsigned to) const {
  unsigned n = adj_.size();
  if (from - 1 >= n || to - 1 >= n)
    return {INT_MAX, {}}; 

  from = from - 1; 
  to = to - 1; 

  std::vector<unsigned> dist(n, UINT_MAX);
  std::vector<bool> visited(n, false);
  std::vector<unsigned> prev(n, UINT_MAX);

  dist[from] = 0;
  for (unsigned count = 0; count < n - 1; ++count) {
    unsigned u = min_distance(dist, visited, n);
    visited[u] = true;
   
    for (unsigned v = 0; v < n; ++v) {
      if (!visited[v] && adj_[u][v] && dist[u] != UINT_MAX && dist[u] + adj_[u][v] < dist[v]) {
        dist[v] = dist[u] + adj_[u][v]; 
        prev[v] = u;
      }
    } 
  }

  unsigned curr = to;
  std::vector<unsigned> path;
  while (curr != UINT_MAX) {
    path.insert(path.begin(), curr + 1);
    curr = prev[curr];
  }
  return {dist[to], path};
}

void dwgraph::erase_node(unsigned node_num) {
  unsigned n = adj_.size();
  unsigned node_pos = node_num - 1; 
  if (node_pos >= n)
    return; 
  
  nodes_.erase(nodes_.begin() + node_pos);
  adj_.erase(adj_.begin() + node_pos);

  for (auto it = adj_.begin(); it != adj_.end(); ++it)
    it->erase(it->begin() + node_pos);
}

void dwgraph::erase_edge(unsigned from, unsigned to) {
  unsigned n = adj_.size();
  if (from - 'a' >= n || to - 'a' >= n)
    return; 
  adj_[from - 1][to - 1] = 0;
}

void dwgraph::topologic_sort_util(unsigned v, std::vector<bool>& visited, std::vector<unsigned>& result) const {
  visited[v] = true;
  for (unsigned i = 0; i < adj_[v].size(); ++i) {
    if (!visited[i] && adj_[v][i] != 0)
      topologic_sort_util(i, visited, result);
  }
  result.push_back(v + 1); 
}

std::vector<unsigned> dwgraph::topologic_sort() const {
  unsigned n = adj_.size();
  std::vector<bool> visited(n, false);
  std::vector<unsigned> result;
  
  for (unsigned i = 0; i < n; ++i)
    if (!visited[i])
      topologic_sort_util(i, visited, result);

  std::reverse(result.begin(), result.end());
  return result;
};

std::ostream& operator<<(std::ostream& out, const dwgraph& d) {
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
