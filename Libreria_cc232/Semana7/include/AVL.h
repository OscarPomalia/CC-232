#pragma once

#include <algorithm>

#include "BST.h"

namespace ods {

template <typename T, typename Compare = std::less<T>>
class AVL : public BST<T, Compare> {
 public:
  using typename BST<T, Compare>::Node;
  using typename BST<T, Compare>::NodePosi;

  AVL() = default;

  explicit AVL(const Compare& comp)
      : BST<T, Compare>(comp) {}

  NodePosi insert(const T& e) override {
    NodePosi& x = this->search(e);

    if (x) return x;

    x = new Node(e, this->_hot);
    ++this->_size;

    for (NodePosi g = this->_hot; g; g = g->parent) {
      if (!avlBalanced(g)) {
        this->rotateAt(tallerChild(tallerChild(g)));
        break;
      }

      this->updateHeight(g);
    }

    return x;
  }

  bool remove(const T& e) override {
    NodePosi& x = this->search(e);

    if (!x) return false;

    BST<T, Compare>::removeAt(x, this->_hot);
    --this->_size;

    for (NodePosi g = this->_hot; g;) {
      if (!avlBalanced(g)) {
        NodePosi r = this->rotateAt(tallerChild(tallerChild(g)));
        g = r->parent;
      } else {
        this->updateHeight(g);
        g = g->parent;
      }
    }

    return true;
  }

  bool isAVLValid() const {
    return this->isBSTValid() && isAVL(this->root());
  }

 private:
  static int stature(NodePosi x) {
    return x ? x->height : -1;
  }

  static int balanceFactor(NodePosi x) {
    return stature(x->lc) - stature(x->rc);
  }

  static bool avlBalanced(NodePosi x) {
    return -2 < balanceFactor(x) && balanceFactor(x) < 2;
  }

  static NodePosi tallerChild(NodePosi x) {
    if (stature(x->lc) > stature(x->rc)) {
      return x->lc;
    }

    if (stature(x->lc) < stature(x->rc)) {
      return x->rc;
    }

    if (x->parent && x == x->parent->lc) {
      return x->lc;
    }

    return x->rc;
  }

  bool isAVL(NodePosi x) const {
    if (!x) return true;

    int bf = stature(x->lc) - stature(x->rc);

    if (bf < -1 || bf > 1) return false;

    if (x->height != 1 + std::max(stature(x->lc), stature(x->rc))) {
      return false;
    }

    return isAVL(x->lc) && isAVL(x->rc);
  }
};

}  // namespace ods