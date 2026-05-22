#pragma once

#include <algorithm>

namespace ods {

template <typename T>
struct BinNode {
  using Node = BinNode<T>;

  T data{};
  Node* parent{nullptr};
  Node* lc{nullptr};
  Node* rc{nullptr};
  int height{0};

  BinNode() = default;
  explicit BinNode(const T& e, Node* p = nullptr, Node* l = nullptr, Node* r = nullptr,
                   int h = 0)
      : data(e), parent(p), lc(l), rc(r), height(h) {}

  bool isLChild() const { return parent && parent->lc == this; }
  bool isRChild() const { return parent && parent->rc == this; }
  bool hasLChild() const { return lc != nullptr; }
  bool hasRChild() const { return rc != nullptr; }
  bool hasBothChildren() const { return lc && rc; }
  bool isLeaf() const { return !lc && !rc; }

  static int stature(Node* x) { return x ? x->height : -1; }

  void updateHeight() { height = 1 + std::max(stature(lc), stature(rc)); }

  void updateHeightAbove() {
    for (Node* x = this; x != nullptr; x = x->parent) {
      x->updateHeight();
    }
  }

  Node* succ() {
    Node* s = this;
    if (rc) {
      s = rc;
      while (s->lc) s = s->lc;
      return s;
    }
    while (s->parent && s->isRChild()) s = s->parent;
    return s->parent;
  }

  Node* pred() {
    Node* s = this;
    if (lc) {
      s = lc;
      while (s->rc) s = s->rc;
      return s;
    }
    while (s->parent && s->isLChild()) s = s->parent;
    return s->parent;
  }
};

template <typename T>
using BinNodePosi = BinNode<T>*;

}  // namespace ods
