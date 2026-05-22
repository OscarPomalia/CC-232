#pragma once

#include <algorithm>
#include <queue>
#include <vector>

namespace ods {

template <class N>
class BTNode {
 public:
  N* left{nullptr};
  N* right{nullptr};
  N* parent{nullptr};
};

template <class Node>
class BinaryTree {
 protected:
  Node* r;
  Node* nil;

  void clearSubtree(Node* u) {
    if (u == nil) return;
    clearSubtree(u->left);
    clearSubtree(u->right);
    delete u;
  }

  int size(Node* u) const {
    if (u == nil) return 0;
    return 1 + size(u->left) + size(u->right);
  }

  int height(Node* u) const {
    if (u == nil) return -1;
    return 1 + std::max(height(u->left), height(u->right));
  }

 public:
  BinaryTree() : nil(new Node()), r(nullptr) {
    nil->left = nil->right = nil->parent = nil;
    r = nil;
  }

  virtual ~BinaryTree() {
    clear();
    delete nil;
  }

  void clear() {
    clearSubtree(r);
    r = nil;
  }

  Node* root() const { return r; }
  Node* nilNode() const { return nil; }
  int size() const { return size(r); }
  int height() const { return height(r); }

  int depth(Node* u) const {
    int d = 0;
    while (u != r && u != nil) {
      u = u->parent;
      ++d;
    }
    return d;
  }

  std::vector<Node*> bfsNodes() const {
    std::vector<Node*> out;
    std::queue<Node*> q;
    if (r != nil) q.push(r);
    while (!q.empty()) {
      Node* u = q.front();
      q.pop();
      out.push_back(u);
      if (u->left != nil) q.push(u->left);
      if (u->right != nil) q.push(u->right);
    }
    return out;
  }
};

class BTNode1 : public BTNode<BTNode1> {};

}  // namespace ods
