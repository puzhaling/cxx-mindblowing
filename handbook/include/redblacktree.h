#ifndef HANDBOOK_REDBLACKTREE_H_
#define HANDBOOK_REDBLACKTREE_H_

#include "autodocs.h"

enum Color {
  kBlack = 0,
  kRed
};

struct Node {
  CarSpecs data;
  Node* parent;
  Node* left;
  Node* right;
  Color color;
};

class RedBlackTree {
 public:
  RedBlackTree();
  ~RedBlackTree();
  
  Node* Search(const CarSpecs&) const;
  void Insert(const CarSpecs&);
  void DeleteNode(const CarSpecs&);
  void InorderTraversal() const;

 private:
  void InitializeNULLNode(Node*, Node*) const;
  Node* SearchHelper(Node*, const CarSpecs&) const;
  Node* Minimum(Node*) const;
  Node* Maximum(Node* node) const;
  Node* Successor(Node*) const;
  Node* Predecessor(Node*) const;
  void LeftRotate(Node*);
  void RightRotate(Node*);
  void InorderHelper(Node* node) const;

  // For balancing the tree after deletion
  void DeleteFix(Node*);
  void RbTransplant(Node*, Node*);
  void DeleteNodeHelper(Node*, const CarSpecs&);
  void InsertFix(Node*);

  Node* root_;
  Node* TNULL_;
};

#endif // HANDBOOK_REDBLACKTREE_H_
