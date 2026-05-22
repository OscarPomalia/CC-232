#pragma once

#include <functional>
#include <utility>

#include "BinTree.h"

namespace ods {

template <typename T, typename Compare = std::less<T>>
class BST : public BinTree<T> {
 public:
  using typename BinTree<T>::Node;
  using typename BinTree<T>::NodePosi;

  BST() = default;
  explicit BST(const Compare& comp) : comp_(comp) {}

  virtual NodePosi& search(const T& e) {
    _hot = nullptr;
    return searchIn(this->_root, e, _hot);
  }

  virtual NodePosi insert(const T& e) {
    NodePosi& x = search(e);
    if (x) return x;
    x = new Node(e, _hot);
    ++this->_size;
    this->updateHeightAbove(x);
    return x;
  }

  virtual bool remove(const T& e) {
    NodePosi& x = search(e);
    if (!x) return false;
    removeAt(x, _hot);
    --this->_size;
    if (_hot) this->updateHeightAbove(_hot);
    return true;
  }

  bool contains(const T& e) const { return findNode(e) != nullptr; }

  bool isBSTValid() const { return isBST(this->_root, nullptr, nullptr); }

 protected:
  NodePosi _hot{nullptr};
  Compare comp_{};

  bool eq(const T& a, const T& b) const {
    return !comp_(a, b) && !comp_(b, a);
  }

  NodePosi findNode(const T& e) const {
    NodePosi x = this->_root;
    while (x) {
      if (comp_(e, x->data)) {
        x = x->lc;
      } else if (comp_(x->data, e)) {
        x = x->rc;
      } else {
        return x;
      }
    }
    return nullptr;
  }

  NodePosi& searchIn(NodePosi& v, const T& e, NodePosi& hot) {
    if (!v || eq(e, v->data)) return v;
    hot = v;
    return searchIn(comp_(e, v->data) ? v->lc : v->rc, e, hot);
  }

  bool isBST(NodePosi x, const T* lo, const T* hi) const {
    if (!x) return true;
    if (lo && !comp_(*lo, x->data)) return false;
    if (hi && !comp_(x->data, *hi)) return false;
    return isBST(x->lc, lo, &x->data) && isBST(x->rc, &x->data, hi);
  }

  NodePosi connect34(NodePosi a, NodePosi b, NodePosi c,
                     NodePosi T0, NodePosi T1, NodePosi T2, NodePosi T3) {
    a->lc = T0;
    if (T0) T0->parent = a;
    a->rc = T1;
    if (T1) T1->parent = a;
    this->updateHeight(a);

    c->lc = T2;
    if (T2) T2->parent = c;
    c->rc = T3;
    if (T3) T3->parent = c;
    this->updateHeight(c);

    b->lc = a;
    a->parent = b;
    b->rc = c;
    c->parent = b;
    this->updateHeight(b);
    return b;
  }

  NodePosi rotateAt(NodePosi v) {
    NodePosi p = v->parent;
    NodePosi g = p->parent;
    NodePosi gg = g ? g->parent : nullptr;
    NodePosi r = nullptr;

    if (p == g->lc) {
      if (v == p->lc) {
        p->parent = gg;
        r = connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
      } else {
        v->parent = gg;
        r = connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
      }
    } else {
      if (v == p->rc) {
        p->parent = gg;
        r = connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
      } else {
        v->parent = gg;
        r = connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
      }
    }

    r->parent = gg;
    if (!gg) {
      this->_root = r;
    } else if (gg->lc == g) {
      gg->lc = r;
    } else {
      gg->rc = r;
    }
    return r;
  }

  static NodePosi removeAt(NodePosi& x, NodePosi& hot) {
    NodePosi w = x;
    NodePosi succ = nullptr;

    if (!x->lc) {
      succ = x = x->rc;
    } else if (!x->rc) {
      succ = x = x->lc;
    } else {
      w = w->succ();
      std::swap(x->data, w->data);
      NodePosi u = w->parent;
      if (u == x) {
        u->rc = succ = w->rc;
      } else {
        u->lc = succ = w->rc;
      }
    }

    hot = w->parent;
    if (succ) succ->parent = hot;
    delete w;
    return succ;
  }
};

}  // namespace ods
