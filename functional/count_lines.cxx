#include <vector>
#include <string>
#include <iterator>
#include <fstream>
#include <algorithm>

int count_lines(const std::string &filename)
{
  std::ifstream(filename);

  return std::count(
      std::istreambuf_iterator<char>(in),
      std::istreambuf_iterator<char(),
      '\n'); 
}

int count_lines(std::ifstream& in)
{
  return std::count(
      std::istreambuf_iterator<char>(in),
      std::istreambuf_iterator<char(),
      '\n'); 
}

std::vector<int>
count_lines_in_files(const std::vector<std::string> &files)
{
  std::vector<int> results;

  for (const auto &file : files)
    results.push_back(count_lines(file));

  return results;
}

std::vector<int>
count_lines_in_files(const std::vector<std::string> &files)
{
  std::vector<int> results;

  std::transform(files.cbegin(), files.cend(),
                 results.begin(),
                 count_lines);

  return results;
}

std::vector<int>
count_lines_in_files(const std::vector<std::string> &files)
{
  return files | transform(count_lines);
}
