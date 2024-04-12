#ifndef SEARCHES_HPP 
#define SEARCHES_HPP

#include <limits>
#include <utility>
#include "autodocs.hpp"

using line_number   = std::size_t;
using steps         = std::size_t;

std::pair<line_number, steps> barrierSearch(std::vector<AutoDocs>& docs, std::size_t request);
std::pair<line_number, steps> binarySearch(std::vector<AutoDocs>& docs, std::size_t request); 
std::size_t binarySearch(std::vector<AutoDocs>& docs, int left, int right, std::size_t request, steps& step);

#endif // SEARCHES_HPP
