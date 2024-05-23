#include <memory>
#include <iostream>

#include "file_system.hpp"
#include "tree_runner.hpp"

using namespace std;

int main() {
  auto root = std::make_unique<directory>("void");
  tree_runner runner(root.get());
  runner.touch("test.txt");
  runner.touch("main.cpp");
  runner.touch("laba.mw");
  runner.mkdir("projects");
  
  // correct cd path syntax: /foo/goo/moo/
  runner.cd("/void/projects/");
  runner.pwd();

  // correct touch/mkdir syntax: name{.extension}
  runner.touch("project1.txt");
  runner.touch("project2.txt");
  runner.touch("project3.txt");
  runner.touch("project4.txt");
  runner.touch("project5.txt");
  runner.mkdir("secret_projects");
  runner.mkdir("NOT_OPEN_THIS_DIR");
  runner.ls();
  std::cout << '\n';

  runner.cd("/void/");
  runner.pwd();
  runner.ls();
  std::cout << '\n';
  return 0;
}
