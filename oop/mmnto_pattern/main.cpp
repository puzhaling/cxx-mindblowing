#include <iostream>
#include <string>
#include "fs/tree.hpp"
#include "fs/units.hpp"
#include "git.hpp"

int main() {
  Tree tree("root");
  tree.mkdir("void");
  tree.mkdir("foo");
  tree.mkdir("goo");
  tree.ls();

  std::cout << "\n\n\n";
  tree.pwd();
  tree.cd("foo");
  tree.mkdir("foodir1");
  tree.touch("duplicate.txt");
  tree.touch("footxt.txt");
  tree.touch("footxt1.txt");
  tree.touch("footxt2.txt");
  tree.ls();
  tree.pwd();
  tree.cd("foodir1");
  tree.touch("duplicate.txt");
  std::cout << "curr dir: ";
  tree.pwd();

  tree.cd("");
  std::cout << "curr dir: ";
  tree.pwd();

  tree.cd("..");
  tree.pwd();

  tree.cd("..");
  tree.pwd();
  std::cout << '\n';
  tree.ls();


  std::cout << "\n\nfind test:\n";
  tree.cd("");
  tree.find("duplicate.txt");
  return 0;
};
