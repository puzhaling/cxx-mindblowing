#include <iostream>
#include <string>
#include "redblacktree.h"

RedBlackTree::RedBlackTree() {
  TNULL_ = new Node();
  TNULL_->color = kBlack;
  TNULL_->left = nullptr;
  TNULL_->right = nullptr;
  root_ = TNULL_;
}

RedBlackTree::~RedBlackTree() {

}

Node* RedBlackTree::Minimum(Node* node) const {
  while (node->left != TNULL_)
    node = node->left;
  return node;
}

void RedBlackTree::InorderTraversal() const {
  InorderHelper(this->root_); 
}

void RedBlackTree::InorderHelper(Node* node) const {
  if (node == TNULL_)
    return;

  InorderHelper(node->left);
  std::cout << node->data << '\n';
  InorderHelper(node->right);
}

Node* RedBlackTree::Maximum(Node* node) const {
  while (node->right!= TNULL_)
    node = node->right;
  return node;
}

Node* RedBlackTree::Successor(Node* x) const {
  if (x->right != TNULL_)
    return Minimum(x->right);

  Node* y = x->parent;
  while (y != TNULL_ && x == y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}

Node* RedBlackTree::Predecessor(Node* x) const {
  if (x->left != TNULL_)
    return Maximum(x->left);

  Node* y = x->parent;
  while (y != TNULL_ && x == y->left) {
    x = y;
    y = y->parent;
  }
  return y;
}

void RedBlackTree::LeftRotate(Node* x) {
  Node* y = x->right;
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

void RedBlackTree::RightRotate(Node* x) {
  Node* y = x->left;
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

void RedBlackTree::Insert(const CarSpecs& data) {
  Node* node = new Node();
  node->parent = nullptr;
  node->data = data;
  node->left = TNULL_;
  node->right = TNULL_;
  node->color = kRed;

  Node* y = nullptr;
  Node* x = this->root_;

  while (x != TNULL_) {
    y = x;
    if (node->data < x->data) {
      x = x->left;
    } else {
      x = x->right;
    }
  }

  node->parent = y;
  if (y == nullptr) {
    root_ = node;
  } else if (node->data < y->data) {
    y->left = node;
  } else {
    y->right = node;
  }

  if (node->parent == nullptr) {
    node->color = kBlack;
    return;
  }

  if (node->parent->parent == nullptr) 
    return;
  InsertFix(node);
}

void RedBlackTree::DeleteNode(const CarSpecs& data) {
  DeleteNodeHelper(this->root_, data);
}

Node* RedBlackTree::Search(const CarSpecs& data) const {
  return SearchHelper(this->root_, data);
}

void RedBlackTree::InitializeNULLNode(Node* node, Node* parent) const {
  node->data = CarSpecs();
  node->parent = parent;
  node->left = nullptr;
  node->right = nullptr;
  node->color = kBlack;
}

Node* RedBlackTree::SearchHelper(Node* node, const CarSpecs& data) const {
  if (node == TNULL_ || data == node->data)
    return node;

  if (data < node->data)
    return SearchHelper(node->left, data);
  return SearchHelper(node->right, data);
}

// For balancing the tree after deletion
void RedBlackTree::DeleteFix(Node* x) {
  Node* s;
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

void RedBlackTree::RbTransplant(Node* u, Node* v) {
  if (u->parent == nullptr) {
    root_ = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

void RedBlackTree::DeleteNodeHelper(Node* node, const CarSpecs& data) {
  Node* z = TNULL_;
  Node* x;
  Node* y;
  while (node != TNULL_) {
    if (node->data == data)
      z = node;

    if ((node->data < data) || (node->data == data)) {
      node = node->right;
    } else {
      node = node->left;
    }
  }

  if (z == TNULL_) {
    std::cout << "Key not found in the tree" << '\n';
    return;
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
  if (y_original_color == kBlack)
    DeleteFix(x);
}

// For balancing the tree after insertion
void RedBlackTree::InsertFix(Node* k) {
  Node* u;
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
