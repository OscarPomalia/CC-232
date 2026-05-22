#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <queue>
#include <vector>

#include "BinNode.h"

namespace ods {

template <typename T>
class BinTree {
 public:
  using Node = BinNode<T>;
  using NodePosi = BinNodePosi<T>;

  BinTree() = default;
  BinTree(const BinTree&) = delete;
  BinTree& operator=(const BinTree&) = delete;

  virtual ~BinTree() { clear(); }

  std::size_t size() const { return _size; }
  bool empty() const { return _size == 0; }
  NodePosi root() const { return _root; }
  int height() const { return stature(_root); }

  void clear() {
    removeSubtree(_root);
    _root = nullptr;
    _size = 0;
  }

  std::vector<T> inorder() const {
    std::vector<T> out;
    inorder(_root, out);
    return out;
  }

  std::vector<T> preorder() const {
    std::vector<T> out;
    preorder(_root, out);
    return out;
  }

  std::vector<T> postorder() const {
    std::vector<T> out;
    postorder(_root, out);
    return out;
  }

  std::vector<T> levelOrder() const {
    std::vector<T> out;
    if (!_root) return out;
    std::queue<NodePosi> q;
    q.push(_root);
    while (!q.empty()) {
      NodePosi x = q.front();
      q.pop();
      out.push_back(x->data);
      if (x->lc) q.push(x->lc);
      if (x->rc) q.push(x->rc);
    }
    return out;
  }

 protected:
  NodePosi _root{nullptr};
  std::size_t _size{0};

  static int stature(NodePosi x) { return x ? x->height : -1; }

  static void inorder(NodePosi x, std::vector<T>& out) {
    if (!x) return;
    inorder(x->lc, out);
    out.push_back(x->data);
    inorder(x->rc, out);
  }

  static void preorder(NodePosi x, std::vector<T>& out) {
    if (!x) return;
    out.push_back(x->data);
    preorder(x->lc, out);
    preorder(x->rc, out);
  }

  static void postorder(NodePosi x, std::vector<T>& out) {
    if (!x) return;
    postorder(x->lc, out);
    postorder(x->rc, out);
    out.push_back(x->data);
  }

  int updateHeight(NodePosi x) {
    if (!x) return -1;
    x->height = 1 + std::max(stature(x->lc), stature(x->rc));
    return x->height;
  }

  void updateHeightAbove(NodePosi x) {
    for (; x != nullptr; x = x->parent) {
      updateHeight(x);
    }
  }

  static int removeSubtree(NodePosi x) {
    if (!x) return 0;
    int n = 1 + removeSubtree(x->lc) + removeSubtree(x->rc);
    delete x;
    return n;
  }
};

}  // namespace ods
