#pragma once

#include <functional>
#include <optional>
#include <vector>

#include "BinaryTree.h"

namespace ods {

template <class Node, class T>
class BSTNode : public BTNode<Node> {
 public:
  T x{};
};

template <class Node, class T, class Compare = std::less<T>>
class BinarySearchTree : public BinaryTree<Node> {
 protected:
  using BinaryTree<Node>::r;
  using BinaryTree<Node>::nil;

  int n{0};
  T null_{};
  Compare comp_{};

  bool eq(const T& a, const T& b) const {
    return !comp_(a, b) && !comp_(b, a);
  }

  virtual Node* findLast(const T& x) const {
    Node* w = r;
    Node* prev = nil;
    while (w != nil) {
      prev = w;
      if (comp_(x, w->x)) {
        w = w->left;
      } else if (comp_(w->x, x)) {
        w = w->right;
      } else {
        return w;
      }
    }
    return prev;
  }

  virtual bool addChild(Node* p, Node* u) {
    if (p == nil) {
      r = u;
      u->parent = nil;
    } else if (comp_(u->x, p->x)) {
      p->left = u;
      u->parent = p;
    } else if (comp_(p->x, u->x)) {
      p->right = u;
      u->parent = p;
    } else {
      return false;
    }
    u->left = u->right = nil;
    ++n;
    return true;
  }

  virtual bool add(Node* u) {
    Node* p = findLast(u->x);
    return addChild(p, u);
  }

  virtual void splice(Node* u) {
    Node* s = (u->left != nil) ? u->left : u->right;
    Node* p = u->parent;
    if (u == r) {
      r = s;
      p = nil;
    } else if (p->left == u) {
      p->left = s;
    } else {
      p->right = s;
    }
    if (s != nil) {
      s->parent = p;
    }
    --n;
  }

  virtual void remove(Node* u) {
    if (u->left == nil || u->right == nil) {
      splice(u);
      delete u;
    } else {
      Node* w = u->right;
      while (w->left != nil) w = w->left;
      u->x = w->x;
      splice(w);
      delete w;
    }
  }

  virtual void rotateLeft(Node* u) {
    Node* w = u->right;
    w->parent = u->parent;
    if (w->parent != nil) {
      if (w->parent->left == u) {
        w->parent->left = w;
      } else {
        w->parent->right = w;
      }
    }
    u->right = w->left;
    if (u->right != nil) u->right->parent = u;
    u->parent = w;
    w->left = u;
    if (u == r) {
      r = w;
      r->parent = nil;
    }
  }

  virtual void rotateRight(Node* u) {
    Node* w = u->left;
    w->parent = u->parent;
    if (w->parent != nil) {
      if (w->parent->left == u) {
        w->parent->left = w;
      } else {
        w->parent->right = w;
      }
    }
    u->left = w->right;
    if (u->left != nil) u->left->parent = u;
    u->parent = w;
    w->right = u;
    if (u == r) {
      r = w;
      r->parent = nil;
    }
  }

  void inorder(Node* u, std::vector<T>& out) const {
    if (u == nil) return;
    inorder(u->left, out);
    out.push_back(u->x);
    inorder(u->right, out);
  }

  bool validate(Node* u, const T* lo, const T* hi) const {
    if (u == nil) return true;
    if (lo && !comp_(*lo, u->x)) return false;
    if (hi && !comp_(u->x, *hi)) return false;
    return validate(u->left, lo, &u->x) && validate(u->right, &u->x, hi);
  }

 public:
  BinarySearchTree() = default;
  explicit BinarySearchTree(const T& null_value) : null_(null_value) {}

  virtual ~BinarySearchTree() = default;

  virtual bool add(const T& x) {
    Node* u = new Node();
    u->x = x;
    if (!add(u)) {
      delete u;
      return false;
    }
    return true;
  }

  virtual bool remove(const T& x) {
    Node* u = findLast(x);
    if (u != nil && eq(u->x, x)) {
      remove(u);
      return true;
    }
    return false;
  }

  std::optional<T> findEQ(const T& x) const {
    Node* w = r;
    while (w != nil) {
      if (comp_(x, w->x)) {
        w = w->left;
      } else if (comp_(w->x, x)) {
        w = w->right;
      } else {
        return w->x;
      }
    }
    return std::nullopt;
  }

  std::optional<T> lowerBound(const T& x) const {
    Node* w = r;
    Node* z = nil;
    while (w != nil) {
      if (!comp_(w->x, x)) {
        z = w;
        w = w->left;
      } else {
        w = w->right;
      }
    }
    if (z == nil) return std::nullopt;
    return z->x;
  }

  std::optional<T> upperBound(const T& x) const {
    Node* w = r;
    Node* z = nil;
    while (w != nil) {
      if (comp_(x, w->x)) {
        z = w;
        w = w->left;
      } else {
        w = w->right;
      }
    }
    if (z == nil) return std::nullopt;
    return z->x;
  }

  bool contains(const T& x) const {
    auto v = findEQ(x);
    return v.has_value();
  }

  int size() const { return n; }

  std::vector<T> inorder() const {
    std::vector<T> out;
    inorder(r, out);
    return out;
  }

  bool isBSTValid() const { return validate(r, nullptr, nullptr); }
};

template <class T>
class BSTNode1 : public BSTNode<BSTNode1<T>, T> {};

template <class T, class Compare = std::less<T>>
class BinarySearchTree1 : public BinarySearchTree<BSTNode1<T>, T, Compare> {
 public:
  BinarySearchTree1() = default;
};

}  // namespace ods
