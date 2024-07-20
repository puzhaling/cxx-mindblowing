#include <iostream>
#include <string>
#include <iomanip> // for std::setw()

#include "rbtree.h"

RBTree::RBTree() {
  TNULL_ = new RBTreeNode();
  TNULL_->color = kBlack;
  TNULL_->left = nullptr;
  TNULL_->right = nullptr;
  root_ = TNULL_;
}

RBTree::~RBTree() {
  Deallocate(root_);
}

void RBTree::Deallocate(RBTreeNode* node) {
  if (node) {
    Deallocate(node->left);
    Deallocate(node->right);
    delete node;
  }
};

RBTreeNode* RBTree::Minimum(RBTreeNode* node) const {
  while (node->left != TNULL_)
    node = node->left;
  return node;
}


void RBTree::InorderTraversal(std::ostream& out) const {
  InorderHelper(out, this->root_, 0);
}

void RBTree::InorderHelper(std::ostream& out, const RBTreeNode* node, 
                           int indent) const {
  if (node != TNULL_) {
    if (node->right)
        InorderHelper(out, node->right, indent + 6);
    if (indent) out << std::setw(indent) << ' '; 
    out << *node << ((node->color == kBlack) ? " (B)" : " (R)") << '\n';
    if (node->left)
      InorderHelper(out, node->left, indent + 6);
  }
}

RBTreeNode* RBTree::Maximum(RBTreeNode* node) const {
  while (node->right!= TNULL_)
    node = node->right;
  return node;
}

RBTreeNode* RBTree::Successor(RBTreeNode* x) const {
  if (x->right != TNULL_)
    return Minimum(x->right);

  RBTreeNode* y = x->parent;
  while (y != TNULL_ && x == y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}

RBTreeNode* RBTree::Predecessor(RBTreeNode* x) const {
  if (x->left != TNULL_)
    return Maximum(x->left);

  RBTreeNode* y = x->parent;
  while (y != TNULL_ && x == y->left) {
    x = y;
    y = y->parent;
  }
  return y;
}

void RBTree::LeftRotate(RBTreeNode* x) {
  RBTreeNode* y = x->right;
  x->right = y->left;
  if (y->left != TNULL_) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == nullptr) {
    this->root_ = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

void RBTree::RightRotate(RBTreeNode* x) {
  RBTreeNode* y = x->left;
  x->left = y->right;
  if (y->right != TNULL_) {
    y->right->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == nullptr) {
    this->root_ = y;
  } else if (x == x->parent->right) {
    x->parent->right = y;
  } else {
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
}

int RBTree::Insert(const Passport& passport, const CarSpec& carspec, 
                   const FullName& fullname, const Date& date,
                   int line_number) {
    // initializing a new node with provided values
    RBTreeNode* new_node = new RBTreeNode();
    new_node->passport = passport;
    new_node->carspec = carspec;
    new_node->fullname = fullname;
    new_node->date = date;
    new_node->line_number = line_number;
    new_node->parent = nullptr;
    new_node->left = TNULL_;
    new_node->right = TNULL_;
    new_node->color = kRed;

    RBTreeNode* y = nullptr;
    RBTreeNode* x = this->root_;

    // searching for place to insert
    while (x != TNULL_) {
      y = x;
      if (new_node->passport == x->passport && new_node->date == x->date) {
        std::cerr << "RBTreeInsert: pair {passport, date} collision\n";
        delete new_node;
        return -1; 
      }
      if (new_node->carspec < x->carspec || 
         (new_node->carspec == x->carspec && new_node->passport < x->passport) ||
         (new_node->carspec == x->carspec && new_node->passport == x->passport && new_node->fullname < x->fullname) ||
         (new_node->carspec == x->carspec && new_node->passport == x->passport && new_node->fullname == x->fullname && new_node->date < x->date)) {
         x = x->left;
      } else {
         x = x->right;
      }
    }

    // when we found a place, we decide where to 
    // place a new_node, on left, or right side?
    new_node->parent = y;
    if (y == nullptr) {
      // if tree is empty, we don't have any variants where
      // to place a new_node not as a root
      root_ = new_node;
    } else if (new_node->carspec < y->carspec || 
              (new_node->carspec == y->carspec && new_node->passport < y->passport) ||
              (new_node->carspec == y->carspec && new_node->passport == y->passport && new_node->fullname < y->fullname) ||
              (new_node->carspec == y->carspec && new_node->passport == y->passport && new_node->fullname == y->fullname && new_node->date < y->date)) {
      y->left = new_node;
    } else {
      y->right = new_node;
    }

    // if new_node is the only node in the tree
    // it must be black
    if (new_node->parent == nullptr) {
      new_node->color = kBlack;
      return 0;
    }

    // if new_node is the second node in the tree
    // we are sure, that tree is balanced
    if (new_node->parent->parent == nullptr)
      return 0;

    InsertFix(new_node);
    return 0;
}


void RBTree::SearchAllHelper(
    RBTreeNode* node, 
    const Passport& passport,
    const CarSpec& carspec,
    const Date& date,
    int steps,
    std::vector<std::pair<RBTreeNode, int>>& collection) const { 
  if (node == TNULL_)
    return;

  if (node->carspec == carspec && node->passport == passport && node->date == date)
    collection.push_back(std::make_pair(*node, steps));

  SearchAllHelper(node->left, passport, carspec, date, steps + 1, collection);
  SearchAllHelper(node->right, passport, carspec, date, steps + 1, collection);
}

// for balancing the tree after deletion
void RBTree::DeleteFix(RBTreeNode* x) {
  RBTreeNode* s;
  while (x != root_ && x->color == kBlack) {
    if (x == x->parent->left) {
      s = x->parent->right;
      if (s->color == kRed) {
        s->color = kBlack;
        x->parent->color = kRed;
        LeftRotate(x->parent);
        s = x->parent->right;
      }

      if (s->left->color == kBlack && s->right->color == kBlack) {
        s->color = kRed;
        x = x->parent;
      } else {
        if (s->right->color == kBlack) {
          s->left->color = kBlack;
          s->color = kRed;
          RightRotate(s);
          s = x->parent->right;
        }
        s->color = x->parent->color;
        x->parent->color = kBlack;
        s->right->color = kBlack;
        LeftRotate(x->parent);
        x = root_;
      }
    } else {
      s = x->parent->left;
      if (s->color == kRed) {
        s->color = kBlack;
        x->parent->color = kRed;
        RightRotate(x->parent);
        s = x->parent->left;
      }

      if (s->right->color == kBlack && s->right->color == kBlack) {
        s->color = kRed;
        x = x->parent;
      } else {
        if (s->left->color == kBlack) {
          s->right->color = kBlack;
          s->color = kRed;
          LeftRotate(s);
          s = x->parent->left;
        }
        s->color = x->parent->color;
        x->parent->color = kBlack;
        s->left->color = kBlack;
        RightRotate(x->parent);
        x = root_;
      }
    }
  }
  x->color = kBlack;
}

void RBTree::RbTransplant(RBTreeNode* u, RBTreeNode* v) {
  if (u->parent == nullptr) {
    root_ = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

int RBTree::DeleteRBTreeNodeHelper(RBTreeNode* node,
                                   const Passport& passport, 
                                   const CarSpec& carspec, 
                                   const FullName& fullname,
                                   const Date& date) {
    RBTreeNode* z = TNULL_;
    RBTreeNode* x;
    RBTreeNode* y;

    while (node != TNULL_) {
        if (node->carspec == carspec && node->passport == passport && 
            node->fullname == fullname && node->date == date) {
            z = node;
            break;
        }
        if (carspec < node->carspec || 
            (carspec == node->carspec && passport < node->passport) ||
            (carspec == node->carspec && passport == node->passport && fullname < node->fullname) ||
            (carspec == node->carspec && passport == node->passport && fullname == node->fullname && date < node->date)) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    if (z == TNULL_) {
        std::cerr << "DeleteRBTreeNode: Node is not found\n";
        return -1;
    }

    y = z;
    int y_original_color = y->color;
    if (z->left == TNULL_) {
        x = z->right;
        RbTransplant(z, z->right);
    } else if (z->right == TNULL_) {
        x = z->left;
        RbTransplant(z, z->left);
    } else {
        y = Minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            RbTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RbTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (y_original_color == kBlack) {
        DeleteFix(x);
    }

    return 0;
}

// for balancing the tree after insertion
void RBTree::InsertFix(RBTreeNode* k) {
  RBTreeNode* u;
  while (k->parent->color == kRed) {
    if (k->parent == k->parent->parent->right) {
      u = k->parent->parent->left;
      if (u->color == kRed) {
        u->color = kBlack;
        k->parent->color = kBlack;
        k->parent->parent->color = kRed;
        k = k->parent->parent;
      } else {
        if (k == k->parent->left) {
          k = k->parent;
          RightRotate(k);
        }
        k->parent->color = kBlack;
        k->parent->parent->color = kRed;
        LeftRotate(k->parent->parent);
      }
    } else {
      u = k->parent->parent->right;
      if (u->color == kRed) {
        u->color = kBlack;
        k->parent->color = kBlack;
        k->parent->parent->color = kRed;
        k = k->parent->parent;
      } else {
        if (k == k->parent->right) {
          k = k->parent;
          LeftRotate(k);
        }
        k->parent->color = kBlack;
        k->parent->parent->color = kRed;
        RightRotate(k->parent->parent);
      }
    }
    if (k == root_)
      break;
  }
  root_->color = kBlack;
}

std::vector<RBTreeNode> RBTree::GetAllRBTreeNodes() const {
  if (root_ == TNULL_)
    return {};

  std::vector<RBTreeNode> nodes;
  InorderCollect(root_, nodes);
  return nodes;
}

void RBTree::InorderCollect(RBTreeNode* node, 
                            std::vector<RBTreeNode>& nodes) const {
  if (node == TNULL_) 
    return;
  InorderCollect(node->left, nodes);
  nodes.push_back(*node);
  InorderCollect(node->right, nodes);
}

