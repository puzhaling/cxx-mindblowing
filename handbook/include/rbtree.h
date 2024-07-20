#ifndef HANDBOOK_REDBLACKTREE_H_
#define HANDBOOK_REDBLACKTREE_H_

#include <iostream>
#include <string>
#include <vector>
#include <utility> // for std::pair

// RBTreeNode data's components
#include "core/carspec.h"
#include "core/date.h"
#include "core/fullname.h"
#include "core/passport.h"

enum Color {
  kBlack = 0,
  kRed
};

struct RBTreeNode {
  Passport passport;
  CarSpec carspec;
  FullName fullname;
  Date date;
  int line_number;
  RBTreeNode* parent;
  RBTreeNode* left;
  RBTreeNode* right;
  Color color;
};

inline bool operator==(RBTreeNode& lhs, RBTreeNode& rhs) {
  return lhs.passport == rhs.passport && lhs.carspec == rhs.carspec &&
    lhs.fullname == rhs.fullname && lhs.date == rhs.date;
}

inline std::ostream& operator<<(std::ostream& out, const RBTreeNode& node) {
  return out << node.passport << ' ' <<  node.carspec << ' ' << node.fullname << 
    ' ' << node.date << ' ';
}

class RBTree {
 public:
  RBTree();
  ~RBTree();
  
  // populate last vector with pairs of copies of
  // RBTreeNodes and number of steps to find them
  void SearchAll(const Passport&, const CarSpec&, const Date&, 
                 std::vector<std::pair<RBTreeNode, int>>&) const;

  // returns -1 if insert is not
  // taking place and 0 otherwise
  int Insert(const Passport&, const CarSpec&, const FullName&, const Date&, 
             int line_number);

  // returns -1 if the searched node 
  // is not found, 0 if found and deleted
  int DeleteRBTreeNode(const Passport&, const CarSpec&, const FullName&, const Date&); 
  
  void InorderTraversal(std::ostream&) const;
  std::vector<RBTreeNode> GetAllRBTreeNodes() const;

 private:
  // set node to default state and connect node with parent
  void InitNullRBTreeNode(RBTreeNode* node, RBTreeNode* parent) const;

  void SearchAllHelper(RBTreeNode*, const Passport&, const CarSpec&, 
                       const Date&, int steps, 
                       std::vector<std::pair<RBTreeNode, int>>&) const; 

  RBTreeNode* Minimum(RBTreeNode*) const;
  RBTreeNode* Maximum(RBTreeNode*) const;
  RBTreeNode* Successor(RBTreeNode*) const;
  RBTreeNode* Predecessor(RBTreeNode*) const;

  // for balancing the tree after deletion
  void DeleteFix(RBTreeNode*);
  
  void RbTransplant(RBTreeNode*, RBTreeNode*);
  int DeleteRBTreeNodeHelper(RBTreeNode*, const Passport&, const CarSpec&, 
                             const FullName&, const Date&);
  void InsertFix(RBTreeNode*);
  void Deallocate(RBTreeNode*);
  void InorderHelper(std::ostream&, const RBTreeNode*, int indent) const;
  void LeftRotate(RBTreeNode*);
  void RightRotate(RBTreeNode*);

  void InorderCollect(RBTreeNode*, std::vector<RBTreeNode>&) const;

  RBTreeNode* root_;
  RBTreeNode* TNULL_; // terminating node
};

inline void RBTree::SearchAll(
    const Passport& passport, 
    const CarSpec& carspec, 
    const Date& date,
    std::vector<std::pair<RBTreeNode, int>>& collection) const {
  return SearchAllHelper(this->root_, passport, carspec, date, 1, collection);
}

inline int RBTree::DeleteRBTreeNode(const Passport& passport, 
                                    const CarSpec& carspec, 
                                    const FullName& fullname,
                                    const Date& date) { 
  return DeleteRBTreeNodeHelper(this->root_, passport, carspec, fullname, date);
}

inline void RBTree::InitNullRBTreeNode(RBTreeNode* node, 
                                       RBTreeNode* parent) const {
  node->carspec = CarSpec();
  node->fullname = FullName();
  node->parent = parent;
  node->left = nullptr;
  node->right = nullptr;
  node->color = kBlack;
}

#endif // HANDBOOK_REDBLACKTREE_H_
